// Complete all-prefix macro FFT and its own ordinary binary transpose.
// K<=5, b<=1024, E54. Weighted-Pascal radix maps are compared to literal
// division; ordinary Pascal cores do not time the imported fast H2.
#define FASTMUL_PERIODIC_FIXTURE_ONLY
#include "bounded_periodic_boundary_filter.cpp"
#include "bounded_binary_karatsuba.hpp"
using PrefixVec=std::array<U,1024>;
struct PrefixFFT {
  using Rows=std::array<std::array<U,128>,16>;
  Fixture f{2};
  U eta;
  mutable unsigned phase_checks=0;
  PrefixFFT():eta(f.power(2,f.m)) { check(f.m==27&&f.D==54,"fixed ambient E54"); }
  U native_root(U x,unsigned e,bool transpose=false) const {
    U out=0;
    for(unsigned bit=0;bit<f.D;++bit) {
      unsigned r=(bit+e)%f.period;
      U col=r<f.D?U(1)<<r:(U(1)<<(r-f.D))^(U(1)<<(r-f.m));
      if(transpose) out|=U(parity(col&x))<<bit;
      else if((x>>bit)&1) out^=col;
    }
    return out;
  }
  unsigned width(unsigned k) const { check(k<=5,"fixed prefix height"); return 1u<<(2*k); }
  U point(unsigned k,unsigned address) const {
    unsigned A=1,digits=0; while(A<k) { A*=3; ++digits; }
    check(f.m%A==0,"grid subfield native embedding");
    U out=0; const std::array<U,4> digit{0,1,eta,eta^1};
    for(unsigned i=0;i<k;++i) {
      unsigned t=i,rev=0;
      for(unsigned j=0;j<digits;++j) { rev=3*rev+t%3; t/=3; }
      U direction=f.power(2,(f.m/A)*rev);
      out^=f.mul(digit[(address>>(2*i))&3],direction);
    }
    return out;
  }
  static U small_mul(U x,U y,unsigned d,unsigned s) {
    check(d==2*s,"native child modulus width");
    return bounded_karatsuba_field(x,y,d);
  }
  static U small_pow(U x,U n,unsigned d,unsigned s) {
    U out=1;
    while(n) { if(n&1) out=small_mul(out,x,d,s); n>>=1; if(n) x=small_mul(x,x,d,s); }
    return out;
  }
  static U reverse(U x,unsigned d) {
    U out=0; for(unsigned i=0;i<d;++i) out|=((x>>i)&1)<<(d-1-i); return out;
  }
  static U gram(U x,unsigned d,unsigned s,bool inverse=false) {
    auto shear=[s](U y) { return y^((y>>s)&((U(1)<<s)-1)); };
    return inverse?shear(reverse(x,d)):reverse(shear(x),d);
  }
  U extract(U c,unsigned s) const {
    unsigned d=2*s,h=f.m/s; U out=0;
    for(unsigned i=0;i<f.D;++i) if((c>>i)&1) {
      check(i%h==0,"public Taylor scalar belongs to claimed local subfield");
      out|=U(1)<<(i/h);
    }
    check((out>>d)==0,"local scalar width"); return out;
  }
  U embed(U c,unsigned s) const {
    unsigned d=2*s,h=f.m/s; U out=0;
    for(unsigned j=0;j<d;++j) out|=((c>>j)&1)<<(h*j);
    return out;
  }
  U phase(U x,U c,unsigned s,bool transpose=false) const {
    check(s==3||s==9,"bounded local scalar fields");
    unsigned d=2*s,h=f.m/s; U out=0;
    for(unsigned i=0;i<h;++i) {
      U component=0;
      for(unsigned j=0;j<d;++j) component|=((x>>(i+h*j))&1)<<j;
      if(transpose) component=gram(small_mul(c,gram(component,d,s,true),d,s),d,s);
      else component=small_mul(c,component,d,s);
      for(unsigned j=0;j<d;++j) out|=((component>>j)&1)<<(i+h*j);
    }
    U full=embed(c,s);
    check(out==(transpose?f.scalar_T(full,x):f.mul(full,x)),"local module action and Gram transpose equal full ambient-field scalar maps");
    ++phase_checks; return out;
  }
  static void pascal_core(PrefixVec& x,unsigned n,bool transpose=false) {
    unsigned bits=0; while((1u<<bits)<n) ++bits;
    for(unsigned pass=0;pass<bits;++pass) {
      unsigned bit=transpose?bits-1-pass:pass,stride=1u<<bit;
      for(unsigned i=0;i<n;++i) if(!(i&stride)) {
        if(!transpose) x[i]^=x[i+stride]; else x[i+stride]^=x[i];
      }
    }
  }
  PrefixVec translate(const PrefixVec& x,unsigned n,U delta,unsigned s,bool transpose=false) const {
    if(!delta) return x; // Explicit zero-v bypass, not inverse of zero.
    unsigned d=2*s; U base=extract(delta,s),inverse=small_pow(base,(U(1)<<d)-2,d,s);
    check(small_mul(base,inverse,d,s)==1,"nonzero sibling translation inverse");
    std::array<U,1024> positive{},negative{}; positive[0]=negative[0]=1;
    for(unsigned i=1;i<n;++i) {
      positive[i]=small_mul(positive[i-1],base,d,s);
      negative[i]=small_mul(negative[i-1],inverse,d,s);
    }
    PrefixVec out{};
    for(unsigned i=0;i<n;++i) out[i]=phase(x[i],transpose?negative[i]:positive[i],s,transpose);
    pascal_core(out,n,transpose);
    for(unsigned i=0;i<n;++i) out[i]=phase(out[i],transpose?positive[i]:negative[i],s,transpose);
    return out;
  }
  struct Macro { unsigned a,m,r,M,ell,l,u_exp,c_exp; };
  Macro parameters(unsigned k) const {
    check(k>=2&&k<=5,"bounded nonbase macro");
    unsigned a=1; while(3*a<k) a*=3;
    unsigned l=k<=2*a?1:2,m=l*a,r=k-m;
    unsigned u_exp=f.m/(3*a),c_exp=l*u_exp+(l==1?2:1)*f.m;
    return {a,m,r,width(m),width(r),l,u_exp,c_exp%f.period};
  }
  PrefixVec radix_oracle(const PrefixVec& x,const Macro& p,bool transpose=false) const {
    // Literal sparse monic divisions and their own reverse circuit.
    // The separately proved fast row-radix map is NOT timed here.
    unsigned n=p.M*p.ell,Q=width(p.a);
    std::array<unsigned,2> degree{1,Q},exponent{p.l==1?0:f.m,2*f.m};
    unsigned terms=p.l==1?1:2;
    PrefixVec out{},work=x;
    if(!transpose) {
      for(unsigned s=0;s<p.ell;++s) {
        PrefixVec quotient{}; unsigned length=n-s*p.M;
        for(unsigned t=length;t>p.M;--t) {
          unsigned high=t-1; U lead=work[high]; work[high]=0;
          quotient[high-p.M]=lead;
          for(unsigned j=0;j<terms;++j) work[high-p.M+degree[j]]^=native_root(lead,exponent[j]);
        }
        for(unsigned i=0;i<p.M;++i) out[s*p.M+i]=work[i];
        work=quotient;
      }
      return out;
    }
    PrefixVec future{};
    for(unsigned pass=0;pass<p.ell;++pass) {
      unsigned s=p.ell-1-pass,length=n-s*p.M; PrefixVec cov{};
      for(unsigned i=0;i<p.M;++i) cov[i]=x[s*p.M+i];
      for(unsigned high=p.M;high<length;++high) {
        U lead=future[high-p.M];
        for(unsigned j=0;j<terms;++j) lead^=native_root(cov[high-p.M+degree[j]],exponent[j],true);
        cov[high]=lead;
      }
      future=cov;
    }
    return future;
  }
  Rows row_monomial(const Rows& x,const Macro& p,unsigned degree,unsigned exponent,bool transpose=false) const {
    check(2*p.M<=128&&p.ell<=16,"fixed raw row bounds");
    Rows work{},out{}; unsigned length=2*p.M;
    if(!transpose) {
      for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i+degree*t<length;++i)
        work[t][i+degree*t]=native_root(x[t][i],exponent*t);
    } else {
      for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i+degree*t<length;++i)
        work[t][i+degree*t]=native_root(x[t][i],(f.period-(exponent*t)%f.period)%f.period,true);
    }
    unsigned bits=2*p.r;
    for(unsigned pass=0;pass<bits;++pass) {
      unsigned bit=transpose?bits-1-pass:pass,stride=1u<<bit;
      for(unsigned t=0;t<p.ell;++t) if(!(t&stride)) for(unsigned i=0;i<length;++i) {
        if(!transpose) work[t][i]^=work[t+stride][i];
        else work[t+stride][i]^=work[t][i];
      }
    }
    for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i+degree*t<length;++i)
      out[t][i]=native_root(work[t][i+degree*t],transpose?exponent*t:(f.period-(exponent*t)%f.period)%f.period,transpose);
    return out;
  }
  PrefixVec radix_fast(const PrefixVec& x,const Macro& p,bool transpose=false,bool inverse=false) const {
    unsigned Q=width(p.a),terms=p.l==1?1:2;
    std::array<unsigned,2> degree{1,Q},exponent{p.l==1?0:f.m,2*f.m};
    Rows rows{}; PrefixVec out{};
    if(!transpose) {
      for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i<p.M;++i) rows[t][i]=x[t*p.M+i];
      for(unsigned term=0;term<terms;++term) rows=row_monomial(rows,p,degree[term],exponent[term]);
      for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i<p.M;++i) {
        out[t*p.M+i]^=rows[t][i];
        U high=rows[t][p.M+i];
        if(!inverse) for(unsigned term=0;term<terms;++term) if(i+degree[term]<p.M)
          out[t*p.M+i+degree[term]]^=native_root(high,exponent[term]);
        if(t+1<p.ell) out[(t+1)*p.M+i]^=high;
      }
      return out;
    }
    for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i<p.M;++i) {
      rows[t][i]=x[t*p.M+i];
      U high=t+1<p.ell?x[(t+1)*p.M+i]:0;
      if(!inverse) for(unsigned term=0;term<terms;++term) if(i+degree[term]<p.M)
        high^=native_root(x[t*p.M+i+degree[term]],exponent[term],true);
      rows[t][p.M+i]=high;
    }
    for(unsigned pass=0;pass<terms;++pass) {
      unsigned term=terms-1-pass; rows=row_monomial(rows,p,degree[term],exponent[term],true);
    }
    for(unsigned t=0;t<p.ell;++t) for(unsigned i=0;i<p.M;++i) out[t*p.M+i]=rows[t][i];
    return out;
  }
  PrefixVec radix(const PrefixVec& x,const Macro& p,bool transpose=false) const {
    PrefixVec candidate=radix_fast(x,p,transpose),oracle=radix_oracle(x,p,transpose);
    for(unsigned i=0;i<p.M*p.ell;++i)
      check(candidate[i]==oracle[i],"weighted-Pascal monic radix and own transpose equal independent sparse division circuit");
    return candidate;
  }
  PrefixVec fft(const PrefixVec& x,unsigned k,bool transpose=false) const {
    unsigned n=width(k); PrefixVec out{};
    if(k<=1) {
      for(unsigned v=0;v<n;++v) {
        U c=point(k,v),power=1;
        for(unsigned i=0;i<n;++i) {
          if(!transpose) out[v]^=f.mul(power,x[i]);
          else out[i]^=f.scalar_T(power,x[v]);
          power=f.mul(power,c);
        }
      }
      return out;
    }
    Macro p=parameters(k);
    if(!transpose) {
      PrefixVec rows=radix(x,p),values{};
      for(unsigned i=0;i<p.M;++i) {
        PrefixVec line{};
        for(unsigned t=0;t<p.ell;++t) line[t]=native_root(rows[t*p.M+i],p.c_exp*t);
        line=fft(line,p.r);
        for(unsigned v=0;v<p.ell;++v) values[v*p.M+i]=line[v];
      }
      for(unsigned v=0;v<p.ell;++v) {
        PrefixVec line{}; for(unsigned i=0;i<p.M;++i) line[i]=values[v*p.M+i];
        U delta=f.mul(f.power(2,p.l*p.u_exp),point(p.r,v));
        line=translate(line,p.M,delta,3*p.a);
        line=fft(line,p.m);
        for(unsigned i=0;i<p.M;++i) out[v*p.M+i]=line[i];
      }
      return out;
    }
    PrefixVec values{},rows{};
    for(unsigned v=0;v<p.ell;++v) {
      PrefixVec line{}; for(unsigned i=0;i<p.M;++i) line[i]=x[v*p.M+i];
      line=fft(line,p.m,true);
      U delta=f.mul(f.power(2,p.l*p.u_exp),point(p.r,v));
      line=translate(line,p.M,delta,3*p.a,true);
      for(unsigned i=0;i<p.M;++i) values[v*p.M+i]=line[i];
    }
    for(unsigned i=0;i<p.M;++i) {
      PrefixVec line{}; for(unsigned v=0;v<p.ell;++v) line[v]=values[v*p.M+i];
      line=fft(line,p.r,true);
      for(unsigned t=0;t<p.ell;++t) rows[t*p.M+i]=native_root(line[t],p.c_exp*t,true);
    }
    return radix(rows,p,true);
  }
  PrefixVec reference(const PrefixVec& x,unsigned k,bool transpose=false) const {
    unsigned n=width(k); PrefixVec out{};
    for(unsigned v=0;v<n;++v) {
      U c=point(k,v);
      if(!transpose) for(unsigned t=n;t>0;--t) out[v]=f.mul(out[v],c)^x[t-1];
      else {
        U power=1;
        for(unsigned i=0;i<n;++i) { out[i]^=f.scalar_T(power,x[v]); power=f.mul(power,c); }
      }
    }
    return out;
  }
  void test(unsigned k) const {
    unsigned n=width(k);
    for(unsigned trial=0;trial<3;++trial) {
      PrefixVec x{},z{}; for(unsigned i=0;i<n;++i) { x[i]=random_word(f.D); z[i]=random_word(f.D); }
      PrefixVec y=fft(x,k),adj=fft(z,k,true),ref=reference(x,k),refT=reference(z,k,true);
      for(unsigned i=0;i<n;++i) {
        check(y[i]==ref[i],"complete prefix macro FFT equals independent Horner evaluations on exact native flag");
        check(adj[i]==refT[i],"own macro ordinary transpose equals literal Vandermonde binary columns");
      }
      U left=0,right=0; for(unsigned i=0;i<n;++i) { left^=y[i]&z[i]; right^=x[i]&adj[i]; }
      check(parity(left)==parity(right),"complete unrestricted binary adjoint pairing");
      if(k>=2) {
        Macro p=parameters(k);
        PrefixVec rx=radix_fast(x,p),back=radix_fast(rx,p,false,true);
        PrefixVec ix=radix_fast(x,p,false,true),forth=radix_fast(ix,p);
        PrefixVec invT=radix_fast(z,p,true,true); U li=0,ri=0;
        for(unsigned i=0;i<n;++i) {
          check(back[i]==x[i]&&forth[i]==x[i],"explicit sparse radix inverse both roundtrips");
          li^=ix[i]&z[i]; ri^=x[i]&invT[i];
        }
        check(parity(li)==parity(ri),"explicit radix inverse own ordinary transpose pairing");
      }
    }
  }
};
#ifndef FASTMUL_PREFIX_FFT_FIXTURE_ONLY
int main() {
  if(!limits()) { std::fprintf(stderr,"Could not install 64 MiB / 10 CPU-second limits.\n"); return 2; }
  PrefixFFT p;
  std::printf("{\"status\":\"PASS\",\"memory_limit_MiB\":64,\"CPU_limit_seconds\":10,\"cases\":[");
  for(unsigned k=1;k<=5;++k) {
    p.test(k);
    std::printf("%s{\"K\":%u,\"b\":%u,\"ambient_D\":%u}",k==1?"":",",k,p.width(k),p.f.D);
  }
  std::printf("],\"local_phase_full_field_comparisons\":%u,\"assertions\":%u,\"scope\":\"complete all-prefix FFT and own binary transpose, local subfield phases, weighted-Pascal radix/inverse and zero-sibling bypass; ordinary finite Pascal cores, not fast-H2 timing or global multiplication\"}\n",p.phase_checks,assertions);
}
#endif
