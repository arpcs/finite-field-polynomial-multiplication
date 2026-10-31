// Fixed K<=4, b<=256, D<=54. Tests both periodic maps even below the
// asymptotic crossover; this is finite algebra evidence, not timing evidence.
#include <windows.h>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
using U=std::uint64_t;
using Vec=std::array<U,256>;
using Bundle=std::array<Vec,4>;
using Kernel=std::array<U,65>;
using Period=std::array<U,81>;
static unsigned assertions=0;
static void check(bool ok,const char* why) {
  ++assertions; if(!ok) { std::fprintf(stderr,"FAIL: %s\n",why); std::exit(1); }
}
static bool limits() {
  HANDLE job=CreateJobObjectW(nullptr,nullptr);
  if(!job) return false;
  JOBOBJECT_EXTENDED_LIMIT_INFORMATION x{};
  x.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY|JOB_OBJECT_LIMIT_PROCESS_TIME;
  x.ProcessMemoryLimit=64u*1024u*1024u;
  x.BasicLimitInformation.PerProcessUserTimeLimit.QuadPart=10ll*10000000ll;
  return SetInformationJobObject(job,JobObjectExtendedLimitInformation,&x,sizeof(x))
      &&AssignProcessToJobObject(job,GetCurrentProcess());
}
static unsigned parity(U a) {
  a^=a>>32; a^=a>>16; a^=a>>8; a^=a>>4;
  return unsigned((0x6996u>>(a&15))&1);
}
static U rng=0x85b1e9d71ull;
static U random_word(unsigned width) {
  rng^=rng<<13; rng^=rng>>7; rng^=rng<<17;
  return rng&((U(1)<<width)-1);
}
struct Edge { unsigned row,col; U scalar; };
struct Fixture {
  unsigned K,b,m,D,period,edge_count=0,selected_count=0;
  U mod;
  std::array<U,4> y{};
  std::array<Kernel,4> T{};
  Bundle twiddle{};
  std::array<std::array<U,5>,4> p{};
  std::array<Period,4> h{};
  std::array<std::array<Edge,256>,4> edges{};
  std::array<unsigned,4> nnz{};
  explicit Fixture(unsigned k):K(k),b(1u<<(2*k)),m(9),D(0),period(0),mod(0) {
    check(1<=K&&K<=4,"fixed instance cap");
    while(m<4*(K+1)) m*=3;
    D=2*m; period=3*m;
    check(b<=256&&D<=54&&period<=81,"fixed capacities");
    mod=(U(1)<<D)^(U(1)<<m)^1;
    U eta=power(2,m);
    const std::array<U,4> digit{0,1,eta,eta^1};
    T[0][1]=1;
    for(unsigned j=0;j<K;++j) {
      y[j]=power(2,U(1)<<(2*j));
      check(power(y[j],period)==1,"native period for each root");
      for(unsigned i=0;i<j;++i) check(y[i]!=y[j],"distinct filter roots");
      if(j+1<K) {
        U bracket=power(2,U(1)<<(2*(j+1)))^2;
        U inv=power(bracket,(U(1)<<D)-2);
        check(mul(bracket,inv)==1,"normalized flag denominator");
        for(unsigned s=0;s<=(1u<<(2*j));++s) {
          T[j+1][4*s]^=mul(power(T[j][s],4),inv);
          T[j+1][s]^=mul(T[j][s],inv);
        }
      }
      p[j][0]=1;
      for(unsigned i=0;i<=j;++i)
        for(int s=int(i)+1;s>0;--s) p[j][unsigned(s)]^=mul(y[i],p[j][unsigned(s)-1]);
      // Root-by-root formal series product, independent of the p recurrence.
      h[j][0]=1;
      for(unsigned i=0;i<=j;++i)
        for(unsigned s=1;s<period;++s) h[j][s]^=mul(y[i],h[j][s-1]);
      std::array<U,166> oracle{}; oracle[0]=1;
      for(unsigned s=1;s<2*period+j+1;++s)
        for(unsigned a=1;a<=j+1&&a<=s;++a) oracle[s]^=mul(p[j][a],oracle[s-a]);
      for(unsigned s=0;s<2*period+j+1;++s)
        check(oracle[s]==h[j][s%period],"kernel repeats over two complete native periods");
      for(unsigned s=period-(j+1)+1;s<period;++s)
        check(h[j][s]==0,"Q_d degree is period-d");
      for(unsigned n=0;n<b;++n) {
        U alpha=3;
        for(unsigned l=j+1;l<K;++l) alpha^=mul(digit[(n>>(2*l))&3],power(2,l));
        twiddle[j][n]=evaluate(T[j],1u<<(2*j),alpha);
        if(selected(j,n)) ++selected_count;
      }
      unsigned L=1u<<(2*(j+1));
      for(unsigned n=0;n<b;++n) for(unsigned s=1;s<=j+1&&n+s<b;++s) {
        U c=mul(twiddle[j][n]^twiddle[j][n+s],p[j][s]);
        if(c) {
          check(n/L!=(n+s)/L&&selected(j,n+s),"residual input belongs to selected boundary set");
          check(nnz[j]<256,"fixed residual edge cap");
          edges[j][nnz[j]++]={n,n+s,c};
        }
      }
      check(nnz[j]<=(b/L-1)*(j+1)*(j+2)/2,"internal-boundary edge bound");
      edge_count+=nnz[j];
    }
    check(9*selected_count<=4*b,"aggregate selected support bound");
    check(27*edge_count<=16*b,"aggregate sparse edge bound");
  }
  U mul(U a,U c) const {
    U out=0;
    for(unsigned i=0;i<D;++i) { if(c&1) out^=a; c>>=1; a<<=1;
      if(a&(U(1)<<D)) a^=mod; }
    return out;
  }
  U power(U a,U n) const {
    U out=1; while(n) { if(n&1) out=mul(out,a); n>>=1; if(n) a=mul(a,a); } return out;
  }
  U scalar_T(U c,U a) const {
    U out=0,column=c;
    for(unsigned i=0;i<D;++i) {
      out|=U(parity(column&a))<<i;
      column<<=1; if(column&(U(1)<<D)) column^=mod;
    }
    return out;
  }
  U evaluate(const Kernel& a,unsigned degree,U x) const {
    U out=0; for(int i=int(degree);i>=0;--i) out=mul(out,x)^a[unsigned(i)]; return out;
  }
  unsigned dot(const Vec& a,const Vec& c) const {
    U z=0; for(unsigned n=0;n<b;++n) z^=a[n]&c[n]; return parity(z);
  }
  Vec add(Vec a,const Vec& c) const { for(unsigned n=0;n<b;++n) a[n]^=c[n]; return a; }
  bool selected(unsigned j,unsigned n) const {
    unsigned L=1u<<(2*(j+1));
    return n>=L&&n%L<j+1;
  }
  Vec mask(unsigned j,Vec a) const {
    for(unsigned n=0;n<b;++n) if(!selected(j,n)) a[n]=0;
    return a;
  }
  Vec S(unsigned i,Vec a,bool transpose=false) const {
    if(!transpose) for(int n=int(b)-2;n>=0;--n) a[unsigned(n)]^=mul(y[i],a[unsigned(n)+1]);
    else for(unsigned n=0;n+1<b;++n) a[n+1]^=scalar_T(y[i],a[n]);
    return a;
  }
  Vec B(unsigned j,Vec a,bool transpose=false) const {
    for(unsigned i=0;i<=j;++i) a=S(i,a,transpose);
    return a;
  }
  Vec A(unsigned j,Vec a,bool transpose=false) const {
    for(unsigned n=0;n<b;++n)
      a[n]=transpose?scalar_T(twiddle[j][n],a[n]):mul(twiddle[j][n],a[n]);
    return a;
  }
  Vec R(unsigned j,const Vec& a,bool transpose=false) const {
    Vec out{};
    for(unsigned e=0;e<nnz[j];++e) {
      const Edge& edge=edges[j][e];
      if(!transpose) out[edge.row]^=mul(edge.scalar,a[edge.col]);
      else out[edge.col]^=scalar_T(edge.scalar,a[edge.row]);
    }
    return out;
  }
  Vec periodic_selected(unsigned j,const Vec& a) const {
    Period buckets{}; Vec out{};
    for(int n=int(b)-1;n>=0;--n) {
      unsigned k=unsigned(n),phase=k%period; buckets[phase]^=a[k];
      if(selected(j,k)) for(unsigned v=0;v<period;++v)
        out[k]^=mul(h[j][(v+period-phase)%period],buckets[v]);
    }
    return out;
  }
  Vec periodic_selected_T(unsigned j,const Vec& a) const {
    Period phases{}; Vec out{};
    for(unsigned n=0;n<b;++n) {
      unsigned phase=n%period;
      if(selected(j,n)) for(unsigned v=0;v<period;++v)
        phases[v]^=scalar_T(h[j][(v+period-phase)%period],a[n]);
      out[n]=phases[phase];
    }
    return out;
  }
  Vec direct_single(unsigned j,const Vec& a,bool transpose=false) const {
    return add(A(j,B(j,a,transpose),transpose),B(j,A(j,a,transpose),transpose));
  }
  Vec multi(const Bundle& a) const {
    Vec out{};
    for(int j=int(K)-1;j>=0;--j) {
      unsigned level=unsigned(j);
      out=S(level,add(out,R(level,periodic_selected(level,a[level]))));
    }
    return out;
  }
  Bundle multi_T(const Vec& z) const {
    Bundle out{}; Vec v=z;
    for(unsigned j=0;j<K;++j) {
      v=S(j,v,true);
      out[j]=periodic_selected_T(j,R(j,v,true));
    }
    return out;
  }
  void same(const Vec& a,const Vec& c,const char* why) const {
    for(unsigned n=0;n<b;++n) check(a[n]==c[n],why);
  }
  void test() const {
    for(unsigned trial=0;trial<5;++trial) {
      Bundle x{}; Vec z{};
      for(unsigned n=0;n<b;++n) {
        z[n]=random_word(D);
        for(unsigned j=0;j<K;++j) x[j][n]=random_word(D);
      }
      Vec direct{}; unsigned rhs=0;
      Bundle adj=multi_T(z);
      for(unsigned j=0;j<K;++j) {
        Vec picked=periodic_selected(j,x[j]);
        same(picked,mask(j,B(j,x[j])),"periodic selected output equals root-filter chain");
        same(periodic_selected_T(j,z),B(j,mask(j,z),true),"periodic selected ordinary transpose equals chain transpose");
        check(dot(picked,z)==dot(x[j],periodic_selected_T(j,z)),"periodic selected binary pairing");
        same(adj[j],direct_single(j,z,true),"independent-input commutator transpose block");
        direct=add(direct,direct_single(j,x[j])); rhs^=dot(x[j],adj[j]);
      }
      Vec out=multi(x);
      same(out,direct,"independent-input aggregate equals actual direct commutators");
      check(dot(out,z)==rhs,"independent-input aggregate ordinary transpose pairing");
    }
    // Exercise wrap periods without a stored dense matrix: every input bit
    // in K<=2, selected deterministic bit columns at the larger instances.
    Vec z{}; for(unsigned n=0;n<b;++n) z[n]=random_word(D);
    for(unsigned j=0;j<K;++j) {
      Vec adj=periodic_selected_T(j,z);
      unsigned count=K<=2?b*D:12;
      for(unsigned t=0;t<count;++t) {
        unsigned bit=K<=2?t:(t*997u+53u)%(b*D);
        Vec basis{}; basis[bit/D]=U(1)<<(bit%D);
        check(dot(mask(j,B(j,basis)),z)==unsigned((adj[bit/D]>>(bit%D))&1),"selected ordinary transpose literal input-bit oracle");
      }
    }
  }
};
#ifndef FASTMUL_PERIODIC_FIXTURE_ONLY
int main() {
  if(!limits()) { std::fprintf(stderr,"Could not install 64 MiB / 10 CPU-second limits.\n"); return 2; }
  std::printf("{\"status\":\"PASS\",\"memory_limit_MiB\":64,\"CPU_limit_seconds\":10,\"cases\":[");
  for(unsigned K=1;K<=4;++K) {
    Fixture f(K); f.test();
    std::printf("%s{\"K\":%u,\"b\":%u,\"D\":%u,\"native_period\":%u,\"residual_edges\":%u,\"selected_words\":%u}",
      K==1?"":",",K,f.b,f.D,f.period,f.edge_count,f.selected_count);
  }
  std::printf("],\"assertions\":%u,\"scope\":\"periodic selected filters and independent-input commutator sum; not a complete FFT\"}\n",assertions);
}
#endif
