// End-to-end finite parent product, raw binary product and own adjoints.
// K<=4, E54/B18, parent<=4608 bits; no fast-H2 timing claim.
#define FASTMUL_PREFIX_FFT_FIXTURE_ONLY
#include "bounded_prefix_macro_fft.cpp"
using RawBits=std::array<unsigned char,9216>;
struct MacroParent {
  PrefixFFT fft;
  unsigned K,b,N;
  static constexpr unsigned w=18;
  PrefixVec omega{};
  explicit MacroParent(unsigned k):K(k),b(fft.width(k)),N(w*b) {
    check(1<=K&&K<=4&&N<=4608,"fixed complete-parent caps");
    std::array<U,257> L{},next{}; L[1]=1;
    auto evaluate=[&](U x) {
      U out=0; for(unsigned t=b+1;t>0;--t) out=fft.f.mul(out,x)^L[t-1]; return out;
    };
    for(unsigned j=0;j<K;++j) {
      unsigned degree=1u<<(2*j); U direction=fft.point(K,degree),d=evaluate(direction);
      check(d!=0,"nonzero monic flag direction"); U cube=fft.f.power(d,3); next={};
      for(unsigned t=0;t<=degree;++t) {
        next[4*t]^=fft.f.power(L[t],4); next[t]^=fft.f.mul(cube,L[t]);
      }
      L=next;
    }
    check(L[b]==1&&L[1]!=0,"actual new-flag vanishing polynomial monic and separable");
    U u=evaluate(2),ell=L[1],u2=fft.f.mul(u,u),den=fft.f.mul(ell,u2);
    check(u!=0&&den!=0,"outside-B affine direction and decoder denominator");
    U inv=fft.f.power(den,(U(1)<<fft.f.D)-2),xi=fft.f.power(2,3),s0=fft.f.power(2,b);
    U omega0=fft.f.mul(fft.f.mul(s0,s0)^fft.f.mul(u,s0)^u2^fft.f.mul(xi,u),inv);
    std::array<U,8> differences{};
    for(unsigned j=0;j<K;++j) {
      U z=fft.f.power(fft.point(K,1u<<(2*j)),b);
      differences[2*j]=fft.f.mul(fft.f.mul(z,z)^fft.f.mul(u,z),inv);
      z=fft.f.mul(z,fft.eta);
      differences[2*j+1]=fft.f.mul(fft.f.mul(z,z)^fft.f.mul(u,z),inv);
    }
    U current=omega0;
    for(unsigned n=0;n<b;++n) {
      omega[n]=current;
      U s=fft.f.power(2^fft.point(K,n),b);
      check(current==fft.f.mul(fft.f.mul(s,s)^fft.f.mul(u,s)^u2^fft.f.mul(xi,u),inv),"affine odometer weights equal direct residue formula");
      if(n+1<b) {
        unsigned changed=n^(n+1),bit=0;
        while(changed) { if(changed&1) current^=differences[bit]; changed>>=1; ++bit; }
      }
    }
  }
  static U bar(U x,unsigned s) {
    unsigned d=2*s,L=3*s; U out=0;
    for(unsigned i=0;i<d;++i) if((x>>i)&1) {
      unsigned r=(L-i)%L;
      out^=r<d?U(1)<<r:(U(1)<<(r-d))^(U(1)<<(r-s));
    }
    return out;
  }
  static U trace_gram(U x,unsigned s,bool inverse=false) {
    auto swap=[s](U y) { return (y>>s)|((y&((U(1)<<s)-1))<<s); };
    return inverse?bar(swap(x),s):swap(bar(x,s));
  }
  static U embed_B(U x) {
    U out=0; for(unsigned j=0;j<w;++j) out|=((x>>j)&1)<<(3*j); return out;
  }
  static U select_B(U x) {
    U out=0; for(unsigned j=0;j<w;++j) out|=((x>>(3*j))&1)<<j; return out;
  }
  PrefixVec affine(const PrefixVec& x,bool transpose=false) const {
    PrefixVec out{};
    for(unsigned i=0;i<b;++i) out[i]=fft.native_root(x[i],transpose?(fft.f.period-i%fft.f.period)%fft.f.period:i,transpose);
    PrefixFFT::pascal_core(out,b,transpose);
    for(unsigned i=0;i<b;++i) out[i]=fft.native_root(out[i],transpose?i:(fft.f.period-i%fft.f.period)%fft.f.period,transpose);
    return out;
  }
  PrefixVec evaluate_B(const PrefixVec& x,bool transpose=false) const {
    PrefixVec out=x;
    if(!transpose) {
      for(unsigned i=0;i<b;++i) out[i]=embed_B(x[i]);
      return fft.fft(affine(out),K);
    }
    out=affine(fft.fft(x,K,true),true);
    for(unsigned i=0;i<b;++i) out[i]=select_B(out[i]);
    return out;
  }
  U scalar_T(U c,U x) const {
    U out=PrefixFFT::gram(bounded_karatsuba_field(c,PrefixFFT::gram(x,54,27,true),54),54,27);
    check(out==fft.f.scalar_T(c,x),"ambient coefficient-Gram scalar adjoint equals literal binary columns");
    return out;
  }
  PrefixVec decoder(const PrefixVec& x,bool transpose=false) const {
    PrefixVec work{},out{};
    if(!transpose) {
      for(unsigned i=0;i<b;++i) work[i]=trace_gram(bounded_karatsuba_field(omega[i],x[i],54),27);
      work=evaluate_B(work,true);
      for(unsigned i=0;i<b;++i) out[i]=trace_gram(work[b-1-i],9,true);
    } else {
      for(unsigned i=0;i<b;++i) work[i]=trace_gram(x[b-1-i],9,true);
      work=evaluate_B(work);
      for(unsigned i=0;i<b;++i) out[i]=scalar_T(omega[i],trace_gram(work[i],27));
    }
    return out;
  }
  PrefixVec multiply(const PrefixVec& x,const PrefixVec& y) const {
    PrefixVec xx=evaluate_B(x),yy=evaluate_B(y),product{};
    for(unsigned i=0;i<b;++i) product[i]=bounded_karatsuba_field(xx[i],yy[i],54);
    return decoder(product);
  }
  RawBits pack(const PrefixVec& x) const {
    RawBits out{};
    for(unsigned i=0;i<b;++i) for(unsigned j=0;j<w;++j) out[i+b*j]=static_cast<unsigned char>((x[i]>>j)&1);
    return out;
  }
  RawBits oracle(const PrefixVec& x,const PrefixVec& y) const {
    RawBits xx=pack(x),yy=pack(y),out{};
    for(unsigned i=0;i<N;++i) if(xx[i]) for(unsigned j=0;j<N;++j) if(yy[j]) out[i+j]^=1;
    for(unsigned t=2*N-1;t>N;--t) if(out[t-1]) {
      unsigned d=t-1; out[d]=0; out[d-N]^=1; out[d-N+N/2]^=1;
    }
    return out;
  }
  static unsigned dot(const PrefixVec& x,const PrefixVec& y,unsigned length) {
    U z=0; for(unsigned i=0;i<length;++i) z^=x[i]&y[i]; return parity(z);
  }
  void test() const {
    for(unsigned trial=0;trial<2;++trial) {
      PrefixVec x{},y{},cov{},arbitrary{};
      for(unsigned i=0;i<b;++i) {
        x[i]=random_word(w); y[i]=random_word(w); cov[i]=random_word(w); arbitrary[i]=random_word(54);
      }
      if(trial) for(unsigned i=0;i<b;++i) for(unsigned j=0;j<w;++j) if(i+b*j>=N/2) {
        x[i]&=~(U(1)<<j); y[i]&=~(U(1)<<j);
      }
      PrefixVec result=multiply(x,y); RawBits actual=pack(result),expected=oracle(x,y);
      for(unsigned i=0;i<N;++i) check(actual[i]==expected[i],"complete new-grid product equals independent raw carryless product and parent reduction");
      PrefixVec d=decoder(arbitrary),dt=decoder(cov,true);
      check(dot(d,cov,b)==dot(arbitrary,dt,b),"weighted decoder own ordinary transpose on unrestricted E covectors");
      PrefixVec ev=evaluate_B(x),adj=evaluate_B(arbitrary,true);
      check(dot(ev,arbitrary,b)==dot(x,adj,b),"restricted B forward evaluation owns the correct binary transpose");
      PrefixVec ey=evaluate_B(y);
      for(unsigned i=0;i<b;++i) dt[i]=scalar_T(ey[i],dt[i]);
      adj=evaluate_B(dt,true);
      check(dot(result,cov,b)==dot(x,adj,b),"complete fixed-operand multiplication ordinary binary adjoint pairing");
    }
  }
};
int main() {
  if(!limits()) { std::fprintf(stderr,"Could not install 64 MiB / 10 CPU-second limits.\n"); return 2; }
  std::printf("{\"status\":\"PASS\",\"memory_limit_MiB\":64,\"CPU_limit_seconds\":10,\"cases\":[");
  for(unsigned k=1;k<=4;++k) {
    MacroParent p(k); p.test();
    std::printf("%s{\"K\":%u,\"b\":%u,\"parent_bits\":%u,\"raw_input_bits\":%u,\"E_bits\":54,\"B_bits\":18}",
      k==1?"":",",k,p.b,p.N,p.N/2);
  }
  std::printf("],\"assertions\":%u,\"scope\":\"complete prefix-macro/affine/residue-decoder parent and raw multiplication with own binary adjoints; finite Pascal/radix primitives, not certification of fast-H2 machine theorem\"}\n",assertions);
}
