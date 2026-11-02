// Actual nine-bit native lowering certificate. No dense 512x512 matrix.
// Signed Pauli generators + one exact reference vector determine each Clifford.
// Fixed caps: 1200 frames, 5000 pairs, 512 Gaussian dyadic amplitudes, 40 C gates.
#define main unused_prior_parameter_main
#include "../retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <set>

namespace nativecert {
constexpr unsigned m=9,n=512,mask=511;
using Cols=std::array<unsigned,18>;
unsigned parity(unsigned x){return unsigned(__builtin_popcount(x))&1u;}
unsigned act(const Cols& a,unsigned x){unsigned y=0;while(x){const auto b=unsigned(__builtin_ctz(x));y^=a[b];x&=x-1;}return y;}
Cols inverse(const Cols& a,unsigned w){
    need(w==9||w==18,"binary inverse dimension cap");std::array<std::uint64_t,18> row{};
    for(unsigned i=0;i<w;++i){row[i]=std::uint64_t(1)<<(w+i);
        for(unsigned j=0;j<w;++j)row[i]|=std::uint64_t((a[j]>>i)&1u)<<j;}
    for(unsigned j=0;j<w;++j){unsigned p=j;while(p<w&&!(row[p]&(std::uint64_t(1)<<j)))++p;
        need(p<w,"invertible binary matrix");std::swap(row[p],row[j]);
        for(unsigned i=0;i<w;++i)if(i!=j&&(row[i]&(std::uint64_t(1)<<j)))row[i]^=row[j];}
    Cols b{};for(unsigned j=0;j<w;++j)for(unsigned i=0;i<w;++i)b[j]|=unsigned((row[i]>>(w+j))&1u)<<i;return b;
}
Cols transpose(const Cols& a){Cols b{};for(unsigned i=0;i<m;++i)for(unsigned j=0;j<m;++j)b[i]|=((a[j]>>i)&1u)<<j;return b;}
unsigned rank(const std::vector<unsigned>& a,unsigned w){Cols piv{};unsigned r=0;for(unsigned v:a){
    need(v<(1u<<w),"binary rank vector bound");while(v){const auto k=31u-unsigned(__builtin_clz(v));
        if(piv[k])v^=piv[k];else{piv[k]=v;++r;break;}}}return r;}
Cols complete(std::vector<unsigned> a){need(rank(a,m)==a.size(),"independent prefix");
    for(unsigned j=0;j<m;++j){auto b=a;b.push_back(1u<<j);if(rank(b,m)>a.size())a=std::move(b);}
    need(a.size()==m,"completed coordinate basis");Cols c{};std::copy(a.begin(),a.end(),c.begin());return c;
}
struct Pauli{unsigned label=0,phase=0;friend bool operator==(Pauli a,Pauli b){return a.label==b.label&&a.phase==b.phase;}};
struct Tab{std::array<Pauli,18> p{};friend bool operator==(const Tab& a,const Tab& b){return a.p==b.p;}};
Pauli product(Pauli a,Pauli b){return {a.label^b.label,(a.phase+b.phase+2*parity((a.label>>m)&(b.label&mask)))%4};}
Pauli apply(const Tab& t,Pauli a){Pauli b{0,a.phase};unsigned x=a.label;
    while(x){const auto j=unsigned(__builtin_ctz(x));b=product(b,t.p[j]);x&=x-1;}return b;}
Tab id(){Tab t;for(unsigned j=0;j<18;++j)t.p[j]={1u<<j,0};return t;}
Tab compose(const Tab& a,const Tab& b){Tab t;for(unsigned j=0;j<18;++j)t.p[j]=apply(a,b.p[j]);return t;}
Tab invtab(const Tab& t){Cols c{};for(unsigned j=0;j<18;++j)c[j]=t.p[j].label;const auto ci=inverse(c,18);Tab ti;
    for(unsigned j=0;j<18;++j){const auto p=apply(t,{ci[j],0});need(p.label==(1u<<j),"signed inverse label");ti.p[j]={ci[j],(4-p.phase)%4};}return ti;
}
Pauli capply(Pauli p,unsigned q,bool back){if(parity((p.label>>m)&q)){p.label^=q;p.phase=(p.phase+(back?1:3))%4;}return p;}
Tab ctab(Tab t,unsigned q,bool back){for(auto& p:t.p)p=capply(p,q,back);return t;}
struct Mono {
    Cols g{};unsigned shift=0,c=0;std::array<unsigned,9> alpha{},quad{};
    std::array<std::uint16_t,n> address{};std::array<std::uint8_t,n> phase{};Tab tab;
    void build(){
        address[0]=std::uint16_t(shift);phase[0]=std::uint8_t(c);
        for(unsigned x=1;x<n;++x){const auto j=unsigned(__builtin_ctz(x)),rest=x&(x-1);
            address[x]=std::uint16_t(address[rest]^g[j]);
            phase[x]=std::uint8_t((phase[rest]+alpha[j]+2*parity(quad[j]&rest))%4);}
        const auto git=transpose(inverse(g,m));
        for(unsigned j=0;j<m;++j){unsigned s=(alpha[j]&1u)<<j;
            for(unsigned k=0;k<m;++k)if(k!=j&&((k<j?(quad[k]>>j):(quad[j]>>k))&1u))s|=1u<<k;
            const unsigned z=act(git,s),z0=git[j];
            tab.p[j]={g[j]|(z<<m),(alpha[j]+2*parity(z&shift))%4};
            tab.p[m+j]={z0<<m,2*parity(z0&shift)};
        }
    }
};
using MP=std::shared_ptr<Mono>;
MP rawmono(const std::array<std::uint16_t,n>& address,const std::array<std::uint8_t,n>& phase){
    auto a=std::make_shared<Mono>();a->shift=address[0];a->c=phase[0];
    for(unsigned j=0;j<m;++j){a->g[j]=address[1u<<j]^address[0];a->alpha[j]=(phase[1u<<j]+4-phase[0])%4;
        for(unsigned k=j+1;k<m;++k){const unsigned z=(phase[(1u<<j)|(1u<<k)]+8-phase[1u<<j]-phase[1u<<k]+phase[0])%4;
            need(z%2==0,"quadratic cross coefficient even");if(z)a->quad[j]|=1u<<k;}}
    a->build();need(a->address==address&&a->phase==phase,"complete affine/quadratic monomial table");return a;
}
MP imono(){auto a=std::make_shared<Mono>();for(unsigned j=0;j<m;++j)a->g[j]=1u<<j;a->build();return a;}
MP minverse(const MP& a){std::array<std::uint16_t,n> addr{};std::array<std::uint8_t,n> phase{};
    for(unsigned x=0;x<n;++x){addr[a->address[x]]=std::uint16_t(x);phase[a->address[x]]=std::uint8_t((4-a->phase[x])%4);}return rawmono(addr,phase);
}
MP mcompose(const MP& a,const MP& b){std::array<std::uint16_t,n> addr{};std::array<std::uint8_t,n> phase{};
    for(unsigned x=0;x<n;++x){addr[x]=a->address[b->address[x]];phase[x]=std::uint8_t((b->phase[x]+a->phase[b->address[x]])%4);}return rawmono(addr,phase);
}
MP permutation(const Cols& g){auto a=std::make_shared<Mono>();a->g=g;a->build();return a;}
MP diagonal(const Cols& s){need(s==transpose(s),"symmetric lower shear");auto a=imono();
    for(unsigned j=0;j<m;++j){a->alpha[j]=(s[j]>>j)&1u;for(unsigned k=j+1;k<m;++k)if((s[k]>>j)&1u)a->quad[j]|=1u<<k;}a->build();return a;
}
MP sblock(unsigned r,bool back){auto a=imono();for(unsigned j=0;j<r;++j)a->alpha[j]=back?3:1;a->build();return a;}
struct Gate{unsigned q=0;bool back=false;MP mono,mi;};
using Circuit=std::vector<Gate>;
Gate cg(unsigned q,bool back=false){return {q,back,nullptr,nullptr};}
Gate mg(const MP& a){return {0,false,a,minverse(a)};}
Circuit adjoint(Circuit a){std::reverse(a.begin(),a.end());for(auto& g:a){if(g.mono)std::swap(g.mono,g.mi);else g.back=!g.back;}return a;}
Tab tableau(const Circuit& a){Tab t=id();for(const auto& g:a){if(g.mono)t=compose(g.mono->tab,t);else t=ctab(t,g.q,g.back);}return t;}
struct Gaussian{std::int64_t re=0,im=0;friend bool operator==(Gaussian a,Gaussian b){return a.re==b.re&&a.im==b.im;}};
Gaussian iphase(Gaussian a,unsigned p){switch(p%4){case 0:return a;case 1:return {-a.im,a.re};case 2:return {-a.re,-a.im};default:return {a.im,-a.re};}}
struct State{std::array<Gaussian,n> value{};unsigned depth=0;};
State seed(){State a;a.value[0].re=1;return a;}
void step(State& a,const Gate& g){std::array<Gaussian,n> b{};
    if(g.mono){for(unsigned x=0;x<n;++x)b[g.mono->address[x]]=iphase(a.value[x],g.mono->phase[x]);}
    else{
        need(g.q>0&&g.q<n&&a.depth<40,"C gate/reference depth cap");
        for(unsigned x=0;x<n;++x){const auto u=a.value[x],v=a.value[x^g.q];
            if(!g.back)b[x]={u.re-u.im+v.re+v.im,u.re+u.im-v.re+v.im};
            else b[x]={u.re+u.im+v.re-v.im,-u.re+u.im+v.re+v.im};}
        ++a.depth;
    }
    a.value=b;
}
State state(const Circuit& a){auto x=seed();for(const auto& g:a)step(x,g);return x;}
bool equal(const State& a,const State& b){const unsigned d=std::max(a.depth,b.depth);need(d<=40,"reference denominator cap");
    const auto sa=std::int64_t(1)<<(d-a.depth),sb=std::int64_t(1)<<(d-b.depth);
    for(unsigned x=0;x<n;++x){
        if(a.value[x].re*sa!=b.value[x].re*sb||a.value[x].im*sa!=b.value[x].im*sb)return false;
    }
    return true;
}
unsigned absolute_phase(const State& s,unsigned address){const auto unit=std::int64_t(1)<<s.depth;
    for(unsigned x=0;x<n;++x)if(x!=address)need(s.value[x]==Gaussian{},"monomial remainder has one reference amplitude");
    for(unsigned p=0;p<4;++p)if(s.value[address]==iphase({unit,0},p))return p;
    throw std::runtime_error("monomial remainder absolute phase is not a fourth root");
}
MP recover(const Tab& t,const State& reference){auto a=std::make_shared<Mono>();unsigned b=0;
    for(unsigned j=0;j<m;++j){need((t.p[m+j].label&mask)==0&&t.p[m+j].phase%2==0,"remainder stabilizes diagonal Paulis");
        a->g[j]=t.p[j].label&mask;b|=((t.p[m+j].phase/2)&1u)<<j;}
    a->shift=act(a->g,b);const auto gt=transpose(a->g);Cols s{};
    for(unsigned j=0;j<m;++j){const unsigned z=t.p[j].label>>m;s[j]=act(gt,z);
        a->alpha[j]=(t.p[j].phase+4-2*parity(z&a->shift))%4;
        need((a->alpha[j]&1u)==((s[j]>>j)&1u),"remainder diagonal quadratic parity");}
    need(s==transpose(s),"remainder quadratic symmetry");
    for(unsigned j=0;j<m;++j)for(unsigned k=j+1;k<m;++k)if((s[k]>>j)&1u)a->quad[j]|=1u<<k;
    a->c=absolute_phase(reference,a->shift);a->build();need(a->tab==t,"all signed Pauli images of recovered monomial");return a;
}
std::vector<unsigned> independent(std::vector<unsigned> values){std::sort(values.begin(),values.end());std::vector<unsigned> b;
    for(unsigned x:values){auto t=b;t.push_back(x);if(rank(t,m)>b.size())b.push_back(x);}return b;
}
struct Frame{std::vector<unsigned> basis,perp;Circuit gates;Tab tab,ti;};
Frame frame(std::vector<unsigned> basis){Frame f;need(basis.size()<=9&&rank(basis,m)==basis.size(),"source frame basis independent");
    std::vector<unsigned> span{0};for(unsigned v:basis){const auto old=span;for(unsigned x:old)span.push_back(x^v);}f.basis=independent(span);
    std::vector<unsigned> orth;for(unsigned x=1;x<n;++x){bool good=true;for(unsigned v:f.basis)if(parity(x&v))good=false;if(good)orth.push_back(x);}f.perp=independent(orth);
    need(f.basis.size()+f.perp.size()==9,"complementary annihilator dimension");const unsigned r=unsigned(f.basis.size());
    if(r==0){}
    else if(r==9){for(unsigned j=0;j<m;++j)f.gates.push_back(cg(1u<<j));}
    else if(r==1&&parity(f.basis[0]))f.gates.push_back(cg(f.basis[0]));
    else if(r==8&&parity(f.perp[0])){f.gates.push_back(cg(f.perp[0],true));for(unsigned j=0;j<m;++j)f.gates.push_back(cg(1u<<j));}
    else{
        const auto g=complete(f.basis),gi=inverse(g,m),git=transpose(gi);Cols shear{};
        for(unsigned j=0;j<m;++j)shear[j]=(1u<<j)^act(git,gi[j]);
        const auto k=mcompose(diagonal(shear),permutation(g)),ki=minverse(k);
        f.gates.push_back(mg(ki));for(unsigned j=0;j<r;++j)f.gates.push_back(cg(1u<<j));f.gates.push_back(mg(k));
    }
    f.tab=tableau(f.gates);f.ti=invtab(f.tab);std::vector<unsigned> actual,expected;
    for(unsigned j=0;j<m;++j)actual.push_back(f.ti.p[m+j].label);
    for(unsigned u:f.basis)expected.push_back(u|(u<<m));
    for(unsigned v:f.perp)expected.push_back(v<<m);
    need(rank(expected,18)==9,"L_U has full Lagrangian dimension");expected.insert(expected.end(),actual.begin(),actual.end());
    need(rank(expected,18)==9,"actual replacement frame has exactly the L_U preimage");return f;
}
void printmono(std::ostream& out,const Mono& a){out<<a.shift<<','<<a.c;for(unsigned j=0;j<m;++j)out<<','<<a.g[j];
    for(unsigned j=0;j<m;++j)out<<','<<a.alpha[j];
    for(unsigned j=0;j<m;++j)out<<','<<a.quad[j];}
unsigned recipes=0,maxdepth=0,phase_controls=0,rank_controls=0;
void factor(unsigned u,unsigned v,const std::vector<Frame>& frames,std::ostream& out){
    const auto& a=frames.at(u);const auto& b=frames.at(v);const auto w=compose(b.tab,a.ti);std::vector<unsigned> projection;
    for(unsigned j=0;j<m;++j){auto t=projection;t.push_back(w.p[m+j].label&mask);if(rank(t,m)>projection.size())projection=std::move(t);}
    const unsigned r=unsigned(projection.size());auto both=a.basis;both.insert(both.end(),b.basis.begin(),b.basis.end());
    need(r==2*rank(both,m)-a.basis.size()-b.basis.size()&&r>0,"exact native transition rank");
    const auto ga=inverse(complete(projection),m),gat=transpose(inverse(ga,m));std::array<unsigned,9> z{};
    for(unsigned j=0;j<m;++j)z[j]=act(ga,w.p[m+j].label&mask)|(act(gat,w.p[m+j].label>>m)<<m);
    // Solve for each horizontal basis vector by elimination on only nine generators.
    std::array<unsigned,9> pivot{},witness{};
    for(unsigned j=0;j<m;++j){unsigned x=z[j]&mask,coeff=1u<<j;
        while(x){const auto k=31u-unsigned(__builtin_clz(x));if(pivot[k]){x^=pivot[k];coeff^=witness[k];}
            else{pivot[k]=x;witness[k]=coeff;break;}}}
    Cols shear{};for(unsigned j=0;j<r;++j){unsigned x=1u<<j,coeff=0;
        while(x){const auto k=31u-unsigned(__builtin_clz(x));need(pivot[k]!=0,"horizontal basis solvable");x^=pivot[k];coeff^=witness[k];}
        unsigned label=0;for(unsigned k=0;k<m;++k)if(coeff&(1u<<k))label^=z[k];shear[j]=(label>>m)&((1u<<r)-1);}
    const auto p=permutation(ga),d=diagonal(shear),s=sblock(r,false),si=sblock(r,true);
    Circuit wc=adjoint(a.gates);wc.insert(wc.end(),b.gates.begin(),b.gates.end());
    Circuit rc=wc;rc.push_back(mg(p));rc.push_back(mg(d));rc.push_back(mg(si));
    for(unsigned j=0;j<r;++j)rc.push_back(cg(1u<<j,true));
    rc.push_back(mg(si));
    const auto rr=state(rc);maxdepth=std::max(maxdepth,rr.depth);const auto remainder=recover(tableau(rc),rr);
    const auto left=mcompose(mcompose(minverse(p),minverse(d)),s),right=mcompose(s,remainder);
    auto ft=right->tab;for(unsigned j=0;j<r;++j)ft=ctab(ft,1u<<j,false);ft=compose(left->tab,ft);
    need(ft==w,"factor has every exact signed Pauli image");
    Circuit fc{mg(right)};for(unsigned j=0;j<r;++j)fc.push_back(cg(1u<<j));fc.push_back(mg(left));
    const auto fs=state(fc),ws=state(wc);need(equal(fs,ws),"factor has exact reference amplitudes and absolute phase");
    auto wrong=fs;for(auto& g:wrong.value)g=iphase(g,1);need(!equal(wrong,ws),"wrong global phase rejected");++phase_controls;
    auto wrongrank=right->tab;for(unsigned j=0;j<r-1;++j)wrongrank=ctab(wrongrank,1u<<j,false);
    need(!(compose(left->tab,wrongrank)==w),"wrong paid rank rejected");++rank_controls;
    out<<u<<'\t'<<v<<'\t'<<r<<'\t';printmono(out,*left);out<<'\t';printmono(out,*right);out<<'\n';
    need(bool(out),"native recipe stream write");++recipes;
}
void run(const char* input,const char* output){const recordjson::Json j(input,2097152,220000);std::vector<Frame> f;f.reserve(1200);
    for(unsigned t:j.children(j.key(0,"frames"))){std::vector<unsigned> b;for(unsigned x:j.children(t))b.push_back(j.natural(x));f.push_back(frame(b));need(f.size()<=1200,"frame count cap");}
    need(f.size()==1093,"actual1093 frame definitions");std::set<std::pair<unsigned,unsigned>> pairs;unsigned moves=0;
    for(unsigned t:j.children(j.key(0,"program"))){const auto e=j.children(t);if(j.str(e[0])=="MOVE"){need(e.size()==5,"MOVE arity");
        const auto u=j.natural(e[2]),v=j.natural(e[3]);need(u<f.size()&&v<f.size(),"MOVE frame IDs");pairs.emplace(u,v);++moves;}}
    std::set<unsigned> main;for(unsigned t:j.children(j.key(0,"live"))){const auto r=j.natural(t);main.insert(r);main.insert(r+112);}
    const auto start=j.children(j.key(0,"initial")),end=j.children(j.key(0,"final"));need(start.size()==770&&end.size()==770&&main.size()==208,"public main/helper inventory");
    unsigned helpers=0;for(unsigned r=0;r<770;++r)if(!main.count(r)){pairs.emplace(j.natural(start[r]),j.natural(end[r]));++helpers;}
    need(moves==3453&&helpers==562&&pairs.size()<=5000,"complete actual transition/normalizer inventory");
    std::ofstream out(output);need(bool(out),"recipe output open");out<<"# from\tto\trank\tleft(shift,constant,Gcols,linear,upper-quadratic)\tright(same)\n";
    for(const auto& p:pairs)factor(p.first,p.second,f,out);
    std::cout<<"PASS:"<<f.size()<<" exact nine-bit frames; "<<moves<<" paid contacts +"<<helpers<<" helper endpoints\n"
             <<"unique exact A C_r B recipes="<<recipes<<"; signed Pauli maps and absolute reference phases agree\n"
             <<"wrong-phase controls="<<phase_controls<<"; wrong-rank controls="<<rank_controls<<"\n"
             <<"caps:512 amplitudes; no dense matrix; max reference denominator exponent="<<maxdepth<<"/40\n"
             <<checks<<" assertions; compact monomial recipes emitted; all-column lifting remains the mathematical proof.\n";
}
}
int main(int argc,char** argv){if(!guard()){std::cerr<<"REFUSED:self-only64 MiB/10 CPU-second limits unavailable\n";return 2;}
    try{need(argc==3,"native input and recipe output paths");nativecert::run(argv[1],argv[2]);}
    catch(const std::exception& e){std::cerr<<"FAIL:"<<e.what()<<"\n";return 1;}}
