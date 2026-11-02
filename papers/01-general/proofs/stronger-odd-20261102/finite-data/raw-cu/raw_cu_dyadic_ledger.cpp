// Exact coefficient/denominator ledger for the actual compact raw CU word.
// No transform is executed. All arithmetic is bounded GMP rational arithmetic.
// The result prices numerator WIDTH, not recursive running time or tape routing.
#define main unused_prior_parameter_main
#include "../retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>

namespace dyadicledger {
struct Bound {
    unsigned denom=0,norm=0,scalar=0,paid=0,mass=0;
    void add(const Bound& b,unsigned copies=1){
        need(copies<=104,"fixed replication bound");
        denom+=copies*b.denom;norm+=copies*b.norm;scalar+=copies*b.scalar;
        paid+=copies*b.paid;mass+=copies*b.mass;
        need(denom<100000000&&norm<100000000&&scalar<1000000&&paid<100000&&mass<1000000,"finite ledger caps");
    }
};
unsigned max_coefficient_denom=0,max_coefficient_norm=0;
Bound coefficient(const Q& q,bool scaling){
    need(mpz_popcount(mpq_denref(q.v))==1,"every actual rational coefficient is dyadic");
    const auto exponent=mpz_scan1(mpq_denref(q.v),0);need(exponent<=128,"coefficient denominator cap");
    Q a;mpq_abs(a.v,q.v);a.bound();
    const Q bound=scaling?(a<Q(1)?Q(1):a):Q(1)+a;
    Q power=1;unsigned norm=0;
    while(power<bound){need(norm<128,"coefficient norm cap");power=power*2;++norm;}
    need(!(power<bound),"rational induced-norm upper bound");
    if(norm)need(power/2<bound,"least power-of-two norm bound");
    max_coefficient_denom=std::max(max_coefficient_denom,unsigned(exponent));
    max_coefficient_norm=std::max(max_coefficient_norm,norm);
    return {unsigned(exponent),norm,1,0,0};
}
Bound point(const recordjson::Json& j,unsigned token){
    const auto e=j.children(token);need(e.size()>=3&&e.size()<=4,"point event arity");
    const auto op=j.str(e[0]);
    if(op=="ADD"){need(e.size()==4,"ADD arity");return coefficient(j.rational(e[3]),false);}
    if(op=="SCALE"){need(e.size()==3,"SCALE arity");return coefficient(j.rational(e[2]),true);}
    need(op=="SIGNED_SWAP"||op=="SWAP","unitary rational point opcode");return {0,0,1,0,0};
}
void run(const char* native_path,const char* raw_path){
    const recordjson::Json n(native_path,2097152,220000),g(raw_path,131072,50000);
    const auto frames=n.children(n.key(0,"frames"));need(frames.size()==1093,"actual native frames");
    std::vector<unsigned> dimension;for(unsigned t:frames){const auto b=n.children(t);need(b.size()<=9,"native frame dimension cap");dimension.push_back(unsigned(b.size()));}
    Bound native;
    const auto events=n.children(n.key(0,"program"));need(events.size()==22803,"actual native transcript");
    for(unsigned t:events){const auto e=n.children(t);const auto op=n.str(e[0]);
        if(op=="MOVE"){
            need(e.size()==5,"native MOVE arity");const unsigned u=n.natural(e[2]),v=n.natural(e[3]);
            need(u<1093&&v<1093,"native frame IDs");const unsigned r=dimension[u]>dimension[v]?dimension[u]-dimension[v]:dimension[v]-dimension[u];
            need(r>0&&r<=8,"proper nested native block rank");++native.paid;native.mass+=r;
        }else if(op=="INIT"||op=="CLEAR")++native.scalar;
        else{
            need(op=="ADD"||op=="COPY"||op=="SCALE","native scalar opcode");
            native.add(coefficient(n.rational(e[op=="SCALE"?2:3]),op=="SCALE"));
        }
    }
    need(native.scalar==19350&&native.paid==3453,"native exact event census");
    need(g.natural(g.key(0,"axes"))==145&&g.natural(g.key(0,"roles"))==13474&&
         g.natural(g.key(0,"live_roles"))==13444,"raw CU dimensions");
    const auto calls=g.children(g.key(0,"calls"));need(calls.size()==18,"native call inventory");
    std::array<bool,18> called{};Bound global;unsigned queries=0,idles=0,boundaries=0;
    const auto word=g.children(g.key(0,"word"));need(word.size()==222,"raw macro word size");
    for(unsigned t:word){const auto e=g.children(t);const auto op=g.str(e[0]);
        if(op=="NATIVE"){
            need(e.size()==2,"NATIVE macro arity");const unsigned ci=g.natural(e[1]);need(ci<18&&!called[ci],"native call once");
            called[ci]=true;global.add(native);
        }else if(op=="QUERY_SHEAR"){
            need(e.size()==4&&!g.boolean(e[3]),"actual forward query");++queries;
            // COPY to the one owned row, rank-one C, unitary X, ADD, CLEAR.
            const Bound query{0,2,3,1,1};global.add(query,104);
        }else if(op=="IDLE"){
            need(e.size()==3,"idle tuple");const auto stages=g.children(e[2]);
            need(!stages.empty()&&stages.size()<=9,"whole idle stage bound");++idles;
            global.add(Bound{0,0,0,1,8*unsigned(stages.size())},104);
            global.add(Bound{0,0,0,1,8*unsigned(stages.size())},104);
        }else if(op=="RIGHT_BOUNDARY"||op=="LEFT_BOUNDARY"){
            ++boundaries;const auto b=g.children(g.key(0,op=="RIGHT_BOUNDARY"?"right_boundary":"left_boundary"));
            need(b.size()<=256,"boundary point count cap");for(unsigned p:b)global.add(point(g,p),104);
        }else if(op=="MAIN_ENTER"||op=="MAIN_EXIT"||op=="Q_POWER"){
            // Every normalizer and even Q power is an exact monomial unitary.
        }else global.add(point(g,t),104);
    }
    need(std::all_of(called.begin(),called.end(),[](bool x){return x;})&&queries==15&&idles==15&&boundaries==2,"complete macro coverage");
    need(global.paid==66834&&global.mass==240152,"exact paid count and denominator rank mass");
    unsigned targets=18*562,max_rank=9;
    for(unsigned t:g.children(g.key(0,"main_targets"))){const auto a=g.children(t);need(a.size()==4,"main target descriptor");
        const unsigned r=g.natural(a[2]);need(r>0&&r<=145,"main target rank");max_rank=std::max(max_rank,r);targets+=104;}
    need(targets==13444&&max_rank==145&&max_rank<=global.mass,"every target admits exact terminal power-of-two cancellation");
    unsigned log_roles=0,power=1;while(power<13474){power*=2;++log_roles;}
    const unsigned slope=global.mass+145,constant=global.norm+global.denom+log_roles+2;
    std::cout<<"PASS:all scalar coefficients in the actual native/controller recipe are dyadic\n"
             <<"native:denominator_charge="<<native.denom<<" norm_log2_charge="<<native.norm
             <<" scalar_letters="<<native.scalar<<" paid_blocks="<<native.paid<<" paid_rank_mass="<<native.mass<<"\n"
             <<"global:denominator_charge_D="<<global.denom<<" norm_log2_charge_U="<<global.norm
             <<" scalar_letters="<<global.scalar<<" paid_blocks="<<global.paid<<" paid_rank_mass_S="<<global.mass<<"\n"
             <<"max coefficient:denominator_exponent="<<max_coefficient_denom<<" norm_log2_charge="<<max_coefficient_norm<<"\n"
             <<"for every f>=0:common_denominator_exponent<=e+D+S*f; every prefix l2 norm<=2^U\n"
             <<"Gaussian numerator signed width <= B+"<<slope<<"*f+"<<constant<<" bits (coarse proven bound)\n"
             <<"target rank r:remove D+(S-r)*f denominator bits exactly after the whole invocation\n"
             <<checks<<" exact/structural assertions;64 MiB/10 CPU-second self-only limits\n"
             <<"This certifies finite-word coefficients and width, not recursive depth, tape access or an integer multiplier.\n";
}
}
int main(int argc,char** argv){
    if(!guard()){std::cerr<<"REFUSED:self-only64 MiB/10 CPU-second limits unavailable\n";return 2;}
    try{need(argc==3,"native and raw CU input paths");dyadicledger::run(argv[1],argv[2]);}
    catch(const std::exception& e){std::cerr<<"FAIL:"<<e.what()<<'\n';return 1;}
}
