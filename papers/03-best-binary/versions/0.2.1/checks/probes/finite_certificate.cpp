// Independent finite certificate. No growing tensor or asymptotic timing test.
// All algebra begins after a fail-closed 64 MiB / 10 CPU-second Windows job.
#include "../bounded_chirp_process_limits.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
using U = unsigned __int128;
static constexpr U Q = U(1) << 48;
static unsigned checks = 0;
static void need(bool b) { ++checks; if (!b) throw std::runtime_error("certificate failure"); }
static std::string dec(U x) {
  std::array<char,48> s{}; unsigned n=0;
  do { s[n++]=char('0'+x%10); x/=10; } while(x);
  std::string out; while(n) out+=s[--n]; return out;
}
static U up(U a,U b) { return a/b + U(a%b!=0); }
struct I { U lo,hi; };
// For 1 <= n/d <= 2, log(n/d)=2 atanh((n-d)/(n+d)).
// Positive terms with directed dyadic products; 48 terms and a proved tail.
static I log_small(unsigned n,unsigned d) {
  need(d>0 && n>=d && n<=2*d);
  if(n==d) return {0,0};
  I x{Q*(n-d)/(n+d),up(Q*(n-d),n+d)}, p=x;
  I xx{x.lo*x.lo/Q,up(x.hi*x.hi,Q)};
  I s{0,0};
  for(unsigned j=0;j<48;++j) {
    s.lo+=2*p.lo/(2*j+1); s.hi+=up(2*p.hi,2*j+1);
    p={p.lo*xx.lo/Q,up(p.hi*xx.hi,Q)};
  }
  // Here p contains x^97. Since x<=1/3, remainder <=18*x^97/(8*97).
  s.hi+=up(18*p.hi,8*97);
  return s;
}
static I log_ratio(unsigned n,unsigned d) {
  unsigned k=0; while(2*d<=n) {d*=2;++k;}
  I a=log_small(n,d), b=log_small(2,1);
  return {a.lo+k*b.lo,a.hi+k*b.hi};
}
static I exp_small(I x) {
  need(x.lo<=x.hi && x.hi<Q);
  // 1+x+x^2/2 <= exp(x) <=1+x+x^2/[2(1-x/3)], 0<=x<3.
  return {Q+x.lo+x.lo*x.lo/(2*Q),
          Q+x.hi+up(3*x.hi*x.hi,2*(3*Q-x.hi))};
}
static void moment() {
  constexpr std::array<unsigned,37> paid={0,27445,10400,2200,4340,7760,8120,765};
  std::array<unsigned,37> target{};target[8]=18910;target[22]=240;target[36]=240;
  U bill=0,credit=0; unsigned pm=0,tm=0;
  std::cout<<"\"moment_rows\":["; bool comma=false;
  for(unsigned r=1;r<=36;++r) if(paid[r]||target[r]) {
    I l=log_ratio(36,r),x{l.lo/1300,up(l.hi,1300)},e=exp_small(x);
    bill+=U(paid[r])*r*e.hi;credit+=U(target[r])*r*e.lo;
    pm+=paid[r]*r;tm+=target[r]*r;
    if(comma)std::cout<<',';
    comma=true;
    std::cout<<"{\"r\":"<<r<<",\"log_lo\":\""<<dec(l.lo)
      <<"\",\"log_hi\":\""<<dec(l.hi)<<"\",\"exp_lo\":\""<<dec(e.lo)
      <<"\",\"exp_hi\":\""<<dec(e.hi)<<"\"}";
  }
  need(pm==165080 && tm==165200 && credit>bill);
  std::cout<<"],\"paid_upper_num\":\""<<dec(bill)
    <<"\",\"target_lower_num\":\""<<dec(credit)
    <<"\",\"moment_den\":\""<<dec(36*Q)
    <<"\",\"strict_gap_num\":\""<<dec(credit-bill)<<"\"";
}
using V8=std::array<int,8>;
static int dot(const V8&a,const V8&b){int s=0;for(unsigned i=0;i<8;++i)s+=a[i]*b[i];return s;}
static unsigned parity(unsigned x){unsigned p=0;while(x){p^=x&1;x>>=1;}return p;}
static void geometry() {
  std::array<V8,120> roots{};unsigned n=0;
  for(unsigned i=0;i<8;++i) for(unsigned j=i+1;j<8;++j)
    for(int sign:{1,-1}){roots[n][i]=2;roots[n][j]=2*sign;++n;}
  for(unsigned mask=0;mask<128;++mask) if(!parity(mask)) {
    roots[n][0]=1;for(unsigned j=1;j<8;++j)roots[n][j]=(mask>>(j-1)&1)?-1:1;++n;
  }
  need(n==120);
  const std::array<V8,8> beta={{{1,-1,-1,-1,-1,-1,-1,1},
    {2,2,0,0,0,0,0,0},{-2,2,0,0,0,0,0,0},
    {0,-2,2,0,0,0,0,0},{0,0,-2,2,0,0,0,0},
    {0,0,0,-2,2,0,0,0},{0,0,0,0,-2,2,0,0},{0,0,0,0,0,-2,2,0}}};
  std::array<unsigned,8> aug{};
  for(unsigned i=0;i<8;++i){
    aug[i]=1u<<(8+i);
    for(unsigned j=0;j<8;++j){int d=dot(beta[i],beta[j]);need(d%4==0);aug[i]|=unsigned((d/4)&1)<<j;}
  }
  for(unsigned j=0;j<8;++j){unsigned p=j;while(p<8 && !(aug[p]>>j&1))++p;need(p<8);
    unsigned t=aug[p];aug[p]=aug[j];aug[j]=t;
    for(unsigned i=0;i<8;++i)if(i!=j && (aug[i]>>j&1))aug[i]^=aug[j];}
  std::array<unsigned,120> coords{},dual{};
  for(unsigned t=0;t<120;++t){need(dot(roots[t],roots[t])==8);
    for(unsigned j=0;j<8;++j){int d=dot(roots[t],beta[j]);need(d%4==0);coords[t]|=unsigned((d/4)&1)<<j;}
    for(unsigned j=0;j<8;++j)dual[t]|=parity((aug[j]>>8)&coords[t])<<j;
  }
  for(unsigned s=0;s<120;++s){unsigned degree=0;
    for(unsigned t=0;t<120;++t){int d=dot(roots[s],roots[t]);
      if(s!=t){need(d==0||d==4||d==-4);degree+=unsigned(d==0);}
      bool want=s==t||d==0;
      need((1u^parity(coords[s]&dual[t]))==unsigned(want));
    }need(degree==63);
  }
  std::cout<<",\"E8_roots\":120,\"orthogonal_degree\":63,\"binary_factor_width\":9";
}
using Poly=std::array<long long,3>;
using Mat=std::array<std::array<Poly,4>,4>;
static Mat identity(){Mat a{};for(unsigned i=0;i<4;++i)a[i][i][0]=1;return a;}
static Mat product(const Mat&a,const Mat&b){Mat c{};
  for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)for(unsigned k=0;k<4;++k)
    for(unsigned u=0;u<3;++u)for(unsigned v=0;v<3;++v)c[i][j][(u+v)%3]+=a[i][k][u]*b[k][j][v];
  for(const auto&r:c)for(const auto&p:r)for(long long x:p)need(x>=-1000000 && x<=1000000);
  return c;
}
static void bank_word(){
  const int us[5][4]={{0,0,1,1},{0,1,-1,-1},{0,1,-1,0},{1,0,-1,0},{1,0,0,0}};
  const int ph[5][4]={{1,1,0,0},{-1,-1,0,-1},{-1,0,0,-1},{-1,0,-1,0},{0,0,-1,0}};
  const unsigned pow[5]={1,2,1,2,1};Mat a=identity();
  std::cout<<",\"bank_intermediate_coefficients\":[";
  for(unsigned s=0;s<5;++s){int pairing=0;for(unsigned j=0;j<4;++j)pairing+=us[s][j]*ph[s][j];need(pairing==0);
    Mat b=identity();for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j){
      const int n=us[s][i]*ph[s][j];b[i][j][0]-=n;b[i][j][pow[s]]+=n;}
    a=product(b,a);if(s)std::cout<<',';std::cout<<'[';bool comma=false;
    for(const auto&r:a)for(const auto&p:r)for(long long x:p){if(comma)std::cout<<',';comma=true;std::cout<<x;}
    std::cout<<']';
  }
  Mat want{};want[0][0][1]=want[1][1][1]=want[2][2][2]=want[3][3][2]=1;need(a==want);
  std::cout<<"],\"universal_bank_identity\":true";
}
int main(){
  if(!install_chirp_process_limits()){std::cerr<<"REFUSED: required job unavailable\n";return 2;}
  try {std::cout<<"{\"limits\":\"64MiB/10CPUSeconds;single-thread;finite-only\",";
    moment();geometry();bank_word();std::cout<<",\"checks\":"<<checks<<",\"pass\":true}\n";return 0;
  } catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
