// Restricted exact bank-word discovery, capped at 210^3 triples and 2 MiB hash.
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <psapi.h>
#include <array>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <algorithm>
#include <string>
namespace {
std::uint64_t checks=0,triples=0;std::array<std::array<unsigned,256>,4> scale{};
void check(bool x,const char* s){++checks;if(!x)throw std::runtime_error(s);}
bool guard(){HANDLE j=CreateJobObjectW(nullptr,nullptr);if(!j)return false;JOBOBJECT_EXTENDED_LIMIT_INFORMATION x{};x.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY|JOB_OBJECT_LIMIT_PROCESS_TIME;x.ProcessMemoryLimit=64u*1024u*1024u;x.BasicLimitInformation.PerProcessUserTimeLimit.QuadPart=100000000ll;return SetInformationJobObject(j,JobObjectExtendedLimitInformation,&x,sizeof(x))&&AssignProcessToJobObject(j,GetCurrentProcess());}
unsigned mul(unsigned a,unsigned b){unsigned z=0;for(unsigned i=0;i<2;++i){if(b&1)z^=a;b>>=1;a<<=1;if(a&4)a^=7;}return z&3;}
struct G {unsigned u,phi,lambda;std::uint32_t spread;};
constexpr std::uint32_t I=0x40100401u,target=0xc0300802u;
std::uint32_t left(std::uint32_t m,const G& g){unsigned row=0;for(unsigned j=0;j<4;++j)if((g.phi>>j)&1)row^=(m>>(8*j))&255;return m^(g.spread*scale[g.lambda][row]);}
std::uint32_t matrix_multiply(std::uint32_t a,std::uint32_t b){std::uint32_t y=0;for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j){unsigned z=0;for(unsigned k=0;k<4;++k)z^=mul((a>>(8*i+2*k))&3,(b>>(8*k+2*j))&3);y|=z<<(8*i+2*j);}return y;}
struct Entry {std::uint32_t key=0,word=0;};
constexpr unsigned cap=1u<<18;
unsigned hash(std::uint32_t x){return unsigned((x*2654435761u)>>(32-18));}
void run(){for(unsigned a=0;a<4;++a)for(unsigned b=0;b<256;++b)for(unsigned j=0;j<4;++j)scale[a][b]|=mul(a,(b>>(2*j))&3)<<(2*j);
 std::vector<G> g;for(unsigned u=1;u<16;++u)for(unsigned p=1;p<16;++p)if(!__builtin_parity(u&p)){std::uint32_t spread=0;for(unsigned j=0;j<4;++j)if((u>>j)&1)spread|=1u<<(8*j);for(unsigned lambda:{2u,3u})g.push_back({u,p,lambda,spread});}
 check(g.size()==210,"all 105 binary nilpotents, with both permitted scalar functions");
 for(const auto& x:g){const auto m=left(I,x);check(left(m,x)==I,"every allowed generator is a genuine transvection involution");check(left(target,x)==matrix_multiply(m,target),"fast rank-one multiplication agrees with independent F4 multiplication");}
 std::vector<Entry> table(cap);unsigned states=0;for(unsigned a=0;a<g.size();++a)for(unsigned b=0;b<g.size();++b){const auto m=left(left(I,g[a]),g[b]);unsigned k=hash(m);while(table[k].key&&table[k].key!=m)k=(k+1)&(cap-1);if(!table[k].key){table[k]={m,a|(b<<8)};++states;}}
 auto find=[&](std::uint32_t m){unsigned k=hash(m);while(table[k].key&&table[k].key!=m)k=(k+1)&(cap-1);return table[k].key?table[k].word:0xffffffffu;};
 check(find(I)!=0xffffffffu,"identity two-word control is admitted");
 auto verify=[&](const std::vector<unsigned>& w){for(unsigned a:{1u,2u,3u}){auto actual=I;for(auto j:w){auto x=g[j];x.lambda=x.lambda==3?(a^1u):(mul(a,a)^1u);actual=left(actual,x);}const unsigned ai=mul(a,a);const std::uint32_t expected=a|(a<<10)|(ai<<20)|(ai<<30);check(actual==expected,"candidate is correct at all three phase eigenvalues");}std::cout<<"FOUND length="<<w.size()<<"\n";for(auto j:w)std::cout<<"G index="<<j<<" u="<<g[j].u<<" phi="<<g[j].phi<<" coefficient="<<(g[j].lambda==3?"a+1":"a^2+1")<<"\n";};
 // A four-word search is an exact negative control for the proposed saving.
 bool shorter=false;for(unsigned a=0;a<g.size();++a)for(unsigned b=0;b<g.size();++b){const auto w=find(left(left(target,g[a]),g[b]));if(w!=0xffffffffu){verify({w&255,w>>8,b,a});shorter=true;break;}}
 std::cout<<"SEARCH generators="<<g.size()<<" two_word_states="<<states<<" found_length4="<<shorter<<"\n";
 for(unsigned a=0;a<g.size();++a)for(unsigned b=0;b<g.size();++b){const auto prefix=left(left(target,g[a]),g[b]);for(unsigned c=0;c<g.size();++c){++triples;const auto w=find(left(prefix,g[c]));if(w!=0xffffffffu){verify({w&255,w>>8,c,b,a});return;}}}
 std::cout<<"NO_LENGTH5 in the stated restricted binary-direction menu; no unrestricted lower bound\n";
}
using U=unsigned __int128;
U ceildiv(U x,U y){return (x+y-1)/y;}
std::string dec(U x){std::string s;do{s.push_back(char('0'+x%10));x/=10;}while(x);std::reverse(s.begin(),s.end());return s;}
constexpr U Q=U(1)<<32;
U lnsmall(unsigned a,unsigned b,bool upper){auto div=[&](U x,U y){return upper?ceildiv(x,y):x/y;};const U z=div(U(a-b)*Q,a+b),z2=div(z*z,Q);U term=z,sum=0;for(unsigned k=0;k<32;++k){sum+=div(2*term,2*k+1);term=div(term*z2,Q);}if(upper)sum+=ceildiv(2*term*Q,65*(Q-z2));return sum;}
U lnratio(unsigned a,unsigned b,bool upper){unsigned k=0;while(2*b<=a){b*=2;++k;}return k*lnsmall(2,1,upper)+lnsmall(a,b,upper);}
void profile(){const std::array<std::array<unsigned,2>,5> paid={{{1,37800},{2,75600},{12,37800},{14,2400},{16,45}}};const std::array<std::array<unsigned,2>,2> targetprofile={{{17,37800},{72,480}}};unsigned pm=0,tm=0;for(auto x:paid)pm+=x[0]*x[1];for(auto x:targetprofile)tm+=x[0]*x[1];check(tm-pm==240,"all inactive-bank phases and owned centers are paid in the doubled E8 profile");
 auto bound=[&](const auto& profile,unsigned den,bool upper){U total=0;for(auto x:profile){const auto L=lnratio(72,x[0],upper);if(upper)total+=ceildiv(U(x[0])*x[1]*den*Q*Q,72*(U(den)*Q-L));else total+=U(x[0])*x[1]*(U(den)*Q+L)/(72*U(den));}return total;};
 const auto pu=bound(paid,2800,true),tl=bound(targetprofile,2800,false);check(tl>pu,"five-stage phase moment contracts at sigma=1-1/2800");std::cout<<"MOMENT saving=1/2800 paid_upper="<<dec(pu)<<" target_lower="<<dec(tl)<<" gap="<<dec(tl-pu)<<" Q=2^32 surplus=240\n";
 const auto pl=bound(paid,2600,false),tu=bound(targetprofile,2600,true);check(pl>tu,"the same unmodified profile fails at saving 1/2600");std::cout<<"REJECTION saving=1/2600 paid_lower="<<dec(pl)<<" target_upper="<<dec(tu)<<" gap="<<dec(pl-tu)<<"\n";
}
using Lane=std::array<unsigned char,81>;using Banks=std::array<Lane,4>;
struct Step {unsigned u,phi;bool inverse;};
constexpr std::array<Step,5> word={{{12,3,false},{14,11,true},{6,9,false},{5,5,true},{1,4,false}}};
unsigned rankbin(std::array<unsigned,4> a){unsigned r=0;for(unsigned c=0;c<4&&r<4;++c){unsigned i=r;while(i<4&&!((a[i]>>c)&1))++i;if(i==4)continue;std::swap(a[i],a[r]);for(i=r+1;i<4;++i)if((a[i]>>c)&1)a[i]^=a[r];++r;}return r;}
struct Basis {std::array<unsigned,4> rows,inverse;};
Basis basis(const Step& s){std::array<unsigned,4> col{};for(unsigned v=1;v<16;++v)if(__builtin_parity(v&s.phi)){col[0]=v;break;}col[1]=s.u;unsigned used=2;for(unsigned v=1;v<16&&used<4;++v)if(!__builtin_parity(v&s.phi)){auto trial=col;trial[used]=v;if(rankbin(trial)==used+1)col[used++]=v;}check(used==4,"every raw two-bank call has an explicit binary basis extension");Basis b{};for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)if((col[j]>>i)&1)b.rows[i]|=1u<<j;for(unsigned i=0;i<4;++i)for(unsigned v=1;v<16;++v){unsigned out=0;for(unsigned j=0;j<4;++j)if(__builtin_parity(v&col[j]))out|=1u<<j;if(out==(1u<<i)){b.inverse[i]=v;break;}}return b;}
void change(Banks& a,const std::array<unsigned,4>& m,unsigned n){auto out=a;for(unsigned i=0;i<4;++i)for(unsigned j=0;j<n;++j){out[i][j]=0;for(unsigned k=0;k<4;++k)if((m[i]>>k)&1)out[i][j]^=a[k][j];}a=out;}
unsigned power3(unsigned n){unsigned p=1;while(n--)p*=3;return p;}
unsigned reflection(unsigned k,unsigned f){unsigned dest=0,p=1;for(unsigned j=0;j<2*f;++j){unsigned d=k%3;k/=3;if(j<f)d=(3-d)%3;dest+=d*p;p*=3;}return dest;}
unsigned phase_exponent(unsigned k,unsigned f){std::array<unsigned,4>d{};for(unsigned i=0;i<2*f;++i){d[i]=k%3;k/=3;}unsigned q=0;for(unsigned i=0;i<f;++i)q+=d[i]*d[f+i];return q%3;}
void reflect(Banks& a,unsigned f,unsigned banks=4){const auto old=a;const auto n=power3(2*f);for(unsigned i=0;i<banks;++i)for(unsigned j=0;j<n;++j)a[i][j]=old[i][reflection(j,f)];}
unsigned ep(int x){x=(x%3+3)%3;return x==0?1u:(x==1?2u:3u);}
void local_fixtures(){std::array<Basis,5> bases{};for(unsigned i=0;i<5;++i)bases[i]=basis(word[i]);std::uint64_t fixtures=0;
 for(unsigned f=1;f<=2;++f){const unsigned n=power3(2*f),samples=f==1?243:32;for(unsigned sample=0;sample<samples;++sample){std::array<unsigned,5>d{};unsigned value=sample;for(auto& x:d){x=value%3;value/=3;}const unsigned count=f==1?4*n+4:4;
  for(unsigned trial=0;trial<count;++trial){Banks a{};if(f==1&&trial<4*n)a[trial/n][trial%n]=1;else for(unsigned b=0;b<4;++b)for(unsigned j=0;j<n;++j)a[b][j]=static_cast<unsigned char>((j*17+b*11+trial*7+sample*13)%4);const auto original=a;reflect(a,f,2);
   for(unsigned i=0;i<5;++i){change(a,bases[i].inverse,n);if(word[i].inverse)reflect(a,f);for(unsigned j=0;j<n;++j)a[1][j]^=a[0][j]; // free baseline a+1
    for(unsigned j=0;j<n;++j){a[1][j]^=static_cast<unsigned char>(mul(ep(-int(phase_exponent(j,f))),a[0][j]));for(unsigned b=0;b<2;++b)a[b][j]=static_cast<unsigned char>(mul(ep(int(d[i])),a[b][j]));for(unsigned b=2;b<4;++b)a[b][j]=static_cast<unsigned char>(mul(ep(int(d[i])),a[b][j]));} // two paid inactive-bank phases
    if(word[i].inverse)reflect(a,f);
    change(a,bases[i].rows,n);
   }
   reflect(a,f,2);unsigned total=0;for(auto x:d)total+=x;for(unsigned b=0;b<4;++b)for(unsigned j=0;j<n;++j)check(a[b][j]==mul(ep(int(total+phase_exponent(j,f))),original[b][j]),"complete five-stage main word, both direct inactive-bank calls and all monomials produce the exact full phase");++fixtures;
  }
 }}std::cout<<"LOCAL complete_main_fixtures="<<fixtures<<" max_common_records=81 inactive_phase_calls_per_stage=2\n";
}
}
#ifndef FOUR_BANK_WORD_LIBRARY_ONLY
int main(){if(!guard()){std::cerr<<"REFUSED: SELF-only guard unavailable\n";return 2;}try{run();profile();local_fixtures();PROCESS_MEMORY_COUNTERS pm{};pm.cb=sizeof(pm);GetProcessMemoryInfo(GetCurrentProcess(),&pm,sizeof(pm));std::cout<<"PASS checks="<<checks<<" examined_triples="<<triples<<" peak_bytes="<<pm.PeakWorkingSetSize<<"\n";std::cout<<"limits=64MiB/10CPUSeconds;matrix=4x4_F4;generators=210;hash_entries=262144;triples<=9261000;common_records<=81;single thread\n";}catch(const std::exception& e){std::cerr<<"FAIL "<<e.what()<<"\n";return 1;}}
#endif
