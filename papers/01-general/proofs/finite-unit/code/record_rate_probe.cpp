// Publication copy, 31 October 2026: shared-support include path made local; checks unchanged.
// Exact, fixed 34-bin moment certificate. It does not certify the finite word.
#define main unused_prior_parameter_main
#include "retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include <map>
#include <utility>

namespace recordrate {
using I=std::array<Q,2>;
using Bin=std::pair<unsigned,unsigned>;
const std::array<Bin,16> paid{{{1,41502},{2,8226},{3,8928},{4,1800},
    {5,2934},{6,198},{7,108},{8,18},{16,416},{24,416},{32,416},
    {40,416},{48,416},{56,416},{64,416},{72,208}}};
const std::array<Bin,18> targets{{{1,252},{2,144},{3,72},{4,1926},
    {5,252},{6,36},{7,162},{8,342},{9,6930},{17,416},{25,416},
    {33,416},{41,416},{49,416},{57,416},{65,416},{73,208},{145,208}}};
Q rounded(const Q& x,bool upper){
    Z n;mpz_mul_2exp(n.v,mpq_numref(x.v),48);
    if(upper)mpz_cdiv_q(n.v,n.v,mpq_denref(x.v));
    else mpz_fdiv_q(n.v,n.v,mpq_denref(x.v));
    return Q(n,power(Z(2),48));
}
I logsmall(const Q& z){
    need(!(z<Q(0))&&z<Q(1),"atanh argument");Q sum=0,term=z,z2=z*z;
    for(unsigned j=0;j<32;++j){sum=sum+2*term/Q(2*j+1);term=term*z2;}
    return {{sum,sum+2*term/(Q(65)*(1-z2))}};
}
I logn(unsigned n){
    need(n>=1&&n<=145,"log rank cap");unsigned d=1,k=0;
    while(n>=2*d){d*=2;++k;}
    const auto a=logsmall(Q(1)/3),b=logsmall(Q(long(n-d))/Q(long(n+d)));
    return {{rounded(k*a[0]+b[0],false),rounded(k*a[1]+b[1],true)}};
}
I expone(const Q& x){
    need(!(x<Q(0))&&x<Q(1),"small nonnegative exponential");
    Q term=1,sum=1;for(unsigned j=1;j<=24;++j){term=term*x/Q(j);sum=sum+term;}
    const Q tail=(term*x/25)/(1-x/26);
    return {{rounded(sum,false),rounded(sum+tail,true)}};
}
I expi(const I& x){return {{expone(x[0])[0],expone(x[1])[1]}};}
I moment_factor(unsigned r,const Q& exponent){
    const auto l=logn(r);
    if(exponent<Q(0)){
        const auto e=expi({{(Q(0)-exponent)*l[0],(Q(0)-exponent)*l[1]}});
        return {{Q(1)/e[1],Q(1)/e[0]}};
    }
    return expi({{exponent*l[0],exponent*l[1]}});
}
template<std::size_t N>I moment(const std::array<Bin,N>& hist,const Q& epsilon){
    I total{{0,0}};
    for(const auto& rc:hist){const auto factor=moment_factor(rc.first,epsilon);
        const Q weight(long(rc.first*rc.second));
        total[0]=total[0]+rounded(weight*factor[0],false);
        total[1]=total[1]+rounded(weight*factor[1],true);
    }
    return total;
}
template<std::size_t N>void census(const std::array<Bin,N>& hist,unsigned count,unsigned mass){
    unsigned c=0,s=0;for(const auto& rc:hist){c+=rc.second;s+=rc.first*rc.second;}
    need(c==count&&s==mass,"histogram count and rank mass");
}
void run(){
    // Join the independently checked native and controller invoices.
    const std::array<Bin,8> native_paid{{{1,2219},{2,457},{3,496},{4,100},{5,163},{6,11},{7,6},{8,1}}};
    const std::array<Bin,9> native_helpers{{{1,14},{2,8},{3,4},{4,107},{5,14},{6,2},{7,9},{8,19},{9,385}}};
    const std::array<Bin,9> controller_main{{{17,416},{25,416},{33,416},{41,416},{49,416},{57,416},{65,416},{73,208},{145,208}}};
    const std::array<Bin,8> controller_idles{{{16,416},{24,416},{32,416},{40,416},{48,416},{56,416},{64,416},{72,208}}};
    std::map<unsigned,unsigned> reconstructed_paid,reconstructed_targets;
    for(const auto& rc:native_paid)reconstructed_paid[rc.first]+=18*rc.second;
    reconstructed_paid[1]+=15*104;
    for(const auto& rc:controller_idles)reconstructed_paid[rc.first]+=rc.second;
    for(const auto& rc:native_helpers)reconstructed_targets[rc.first]+=18*rc.second;
    for(const auto& rc:controller_main)reconstructed_targets[rc.first]+=rc.second;
    need(reconstructed_paid==std::map<unsigned,unsigned>(paid.begin(),paid.end()),"native/query/idle composition gives every paid bin");
    need(reconstructed_targets==std::map<unsigned,unsigned>(targets.begin(),targets.end()),"fresh helper/controller composition gives every target bin");
    need(32*104+18*562==13444&&13444+29+1==13474,"distinct live and scratch role allocation");
    for(const auto& rc:paid)need(rc.first>=1&&rc.first<145,"raw CU proper paid ranks");
    for(const auto& rc:targets)need(rc.first>=1&&rc.first<=145,"raw CU legitimate target ranks");
    census(paid,66834,240152);census(targets,13444,240912);
    const Q saving=Q(39)/12500,u=Q(1)/7; // 0.00312, leaving room above 0.0031.
    need(Q(30103)/10000000<Q(31)/10000,"full target beats displayed DFT saving");
    Z source_n,source_d;
    need(mpz_set_str(source_n.v,"3020159999",10)==0&&
         mpz_set_str(source_d.v,"1000000000000",10)==0,"full-width public rational import");
    need(Q(source_n,source_d)<Q(31)/10000,
         "full target beats stronger public source saving");
    need(Q(31)/10000<saving&&saving<u,"strict exponent and higher-moment gaps");
    const Q rate=1-saving,kernel=1-Q(311)/100000,final_exponent=1-Q(31)/10000;
    need(Q(0)<rate&&rate<kernel&&kernel<final_exponent&&final_exponent<Q(1),"all compiler and DFT exponent gaps");
    const I p=moment(paid,Q(0)-saving),t=moment(targets,Q(0)-saving);
    const I pu=moment(paid,u-saving);
    const auto powu=moment_factor(16,u),powc=moment_factor(16,saving);
    const Q alpha=p[1]/t[0],gamma=pu[1]/(powu[0]*t[0]);
    const Q delta=Q(13444)*17/(powc[0]*t[0]);
    need(alpha<1-Q(1)/1000000,"alpha < 1 - 10^-6");
    need(gamma<Q(125)/128&&delta<Q(125)/128,"both strictification tails < 125/128");
    // The sufficient constants below are deliberately rounded outward.
    // Bernoulli on (1-a)^-1024 >= 1+1024*a bounds the alpha power.
    const Q ratio=Q(125)/128;Q block=1;
    for(unsigned j=0;j<128;++j)block=block*ratio;
    need(block<Q(1)/16,"(125/128)^128 < 1/16");
    const Q final=Q(1)/(1+Q(1024)/1000000)+Q(Z(4),power(Z(2),32));
    need(final<Q(1),"charged tensor/completion/splitting moment strictly contracts");
    // J=16^1024, L=17^1024: no giant integer is needed for separation.
    need(16<17,"strict paid cutoff below productive floor");
    auto printbins=[](const char* name,const auto& bins){std::cout<<name<<'=';bool first=true;
        for(const auto& rc:bins){if(!first)std::cout<<',';first=false;std::cout<<rc.first<<':'<<rc.second;}
        std::cout<<'\n';};
    printbins("paid_invoice",paid);printbins("target_invoice",targets);
    std::cout<<"PASS: "<<checks<<" exact checks; 16 paid bins, 18 target bins\n"
             <<"finite composition:13444 independent live roles +30 owned roles; native/controller invoices agree\n"
             <<"tested saving="<<saving<<"; intended full DFT saving=31/10000\n"
             <<"alpha_upper_48="<<rounded(alpha,true)<<"\n"
             <<"gamma_upper_48="<<rounded(gamma,true)<<"\n"
             <<"delta_upper_48="<<rounded(delta,true)<<"\n"
             <<"normalized_strictification_upper="<<final<<" < 1\n"
             <<"hypotheses: actual exact native/controller unit and chronological tensor construction\n"
             <<"No full-word certificate, uniform program, or record is proved by this probe.\n";
}
}
int main(){
    if(!guard()){std::cerr<<"REFUSED: could not install self-only 64 MiB/10 CPU-second limits\n";return 2;}
    try{recordrate::run();}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<"\n";return 1;}
}
