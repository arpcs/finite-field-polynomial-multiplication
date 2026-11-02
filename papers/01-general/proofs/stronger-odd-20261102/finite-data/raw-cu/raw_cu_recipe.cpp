// Assemble a compact, effective 145-axis CU recipe from the checked finite parts.
// This checks integration and ranks, not the previously certified scalar/Laurent identities.
// No complex transform, tensor power, or 2^145 data array is materialized.
#define main unused_prior_parameter_main
#include "../retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>
#include <cstdint>
#include <map>
#include <set>
#include <sstream>

namespace rawcu {
constexpr unsigned axes=145,live_count=13444,role_count=13474;
using Hist=std::map<unsigned,unsigned>;
struct Bits {
    std::array<std::uint64_t,3> v{};
    bool get(unsigned j)const{return (v[j/64]>>(j%64))&1u;}
    void set(unsigned j){need(j<axes,"binary coordinate bound");v[j/64]|=std::uint64_t(1)<<(j%64);}
    Bits& operator^=(const Bits& b){for(unsigned j=0;j<3;++j)v[j]^=b.v[j];return *this;}
};
Bits unit(unsigned j){Bits b;b.set(j);return b;}
Bits small(unsigned q){Bits b;need(q<512,"nine-bit direction bound");b.v[0]=q;return b;}
struct Rank {
    std::array<Bits,axes> p{};std::array<bool,axes> have{};unsigned size=0;
    bool add(Bits b){for(unsigned j=axes;j-->0;)if(b.get(j)){
        if(have[j])b^=p[j];else{p[j]=b;have[j]=true;++size;return true;}}
        return false;}
};
unsigned binary_rank(const std::vector<unsigned>& b){Rank r;for(unsigned x:b)r.add(small(x));return r.size;}
struct Recipe{unsigned rank=0;bool used=false;};
using Pair=std::pair<unsigned,unsigned>;
std::map<Pair,Recipe> read_recipes(const char* path){
    std::ifstream in(path,std::ios::binary);need(bool(in),"native recipe open");
    in.seekg(0,std::ios::end);need(in.tellg()>0&&in.tellg()<524288,"native recipe byte cap");in.seekg(0);
    std::map<Pair,Recipe> out;std::string line;need(bool(std::getline(in,line))&&line[0]=='#',"recipe header");
    while(std::getline(in,line)){
        need(line.size()<1024,"native recipe line cap");std::stringstream s(line);unsigned u,v,r;
        need(bool(s>>u>>v>>r)&&u<1093&&v<1093&&r>0&&r<=9,"native recipe tuple");
        for(unsigned side=0;side<2;++side){std::string csv;need(bool(s>>csv),"native monomial descriptor");
            std::replace(csv.begin(),csv.end(),',',' ');std::stringstream a(csv);std::array<unsigned,29> x{};
            for(auto& value:x)need(bool(a>>value),"29 monomial parameters");
            std::string extra;need(!(a>>extra),"no extra monomial parameter");
            need(x[0]<512&&x[1]<4,"affine shift and absolute phase");Rank g;
            for(unsigned j=0;j<9;++j){g.add(small(x[2+j]));need(x[11+j]<4,"linear phase coefficient");
                need(x[20+j]<512&&(x[20+j]&((1u<<(j+1))-1))==0,"upper quadratic mask");}
            need(g.size==9,"monomial address map invertible");}
        std::string extra;need(!(s>>extra),"no extra recipe field");
        need(out.emplace(Pair{u,v},Recipe{r,false}).second,"unique ordered native recipe");
        need(out.size()<=3000,"recipe count cap");
    }
    need(out.size()==2922,"complete2922 native recipes");return out;
}
unsigned use(std::map<Pair,Recipe>& recipes,unsigned u,unsigned v){
    const auto i=recipes.find({u,v});need(i!=recipes.end(),"every transition has an exact adapter recipe");
    i->second.used=true;return i->second.rank;
}
unsigned fresh(unsigned stage){need(stage>0&&stage<=32&&(stage==32||stage%2==1),"noncentral thick stage");
    return 9+8*(stage==32?16:(stage-1)/2);}
void append_stage(std::vector<Bits>& d,unsigned stage,unsigned q,bool main){
    if(stage==0){
        if(main){for(unsigned j=0;j<9;++j)d.push_back(unit(j));}
        else{
            unsigned j=0;while(j<9&&(q&(1u<<j)))++j;need(j<9,"port has a zero coordinate");
            const unsigned v=q^(1u<<j);
            for(unsigned k=1;k<9;++k){unsigned e=1u<<(k==j?0:k); // swap coordinates0 andj
                if(j==0)e=1u<<k;
                const unsigned b=e^((__builtin_popcount(v&e)&1)?v:0);d.push_back(small(b));}
        }
    }else for(unsigned j=0;j<8;++j)d.push_back(unit(fresh(stage)+j));
}
void independent_and_complete(const std::vector<Bits>& d,unsigned expected){
    need(d.size()==expected&&expected>0&&expected<=axes,"specified target/idle direction count");
    Rank r;for(const auto& v:d)need(r.add(v),"actual145-axis directions independent");
    for(unsigned j=0;j<axes;++j)r.add(unit(j));
    need(r.size==axes,"deterministic standard-axis extension gives a basis");
}
struct Call{unsigned stage,pair,helper_base;};
void run(const char* native_path,const char* controller_path,const char* recipes_path,const char* output){
    auto recipes=read_recipes(recipes_path);
    const recordjson::Json n(native_path,2097152,220000),c(controller_path);
    const auto fb=n.children(n.key(0,"frames"));need(fb.size()==1093,"native frame count");
    std::vector<std::vector<unsigned>> frames;
    for(unsigned t:fb){std::vector<unsigned> b;for(unsigned x:n.children(t))b.push_back(n.natural(x));
        need(b.size()<=9&&binary_rank(b)==b.size(),"independent native subspace basis");frames.push_back(b);}
    const auto si=n.children(n.key(0,"initial")),sf=n.children(n.key(0,"final"));
    const auto sl=n.children(n.key(0,"live")),sp=n.children(n.key(0,"ports"));
    need(si.size()==770&&sf.size()==770&&sl.size()==104&&sp.size()==104,"native public ABI");
    std::array<int,770> port{},helper{};port.fill(-1);helper.fill(-1);
    std::array<bool,770> y{};std::array<unsigned,104> ports{};
    for(unsigned k=0;k<104;++k){const unsigned x=n.natural(sl[k]),q=n.natural(sp[k]);
        need(x<112&&port[x]<0&&q>0&&q<511&&(__builtin_popcount(q)&1),"distinct main source role and port");
        port[x]=port[x+112]=int(k);y[x+112]=true;ports[k]=q;}
    Hist native_paid,helper_hist,paid,target;unsigned hcount=0,moves=0;
    std::vector<std::array<unsigned,4>> helpers;
    for(unsigned r=0;r<770;++r)if(port[r]<0){helper[r]=int(hcount++);
        const unsigned u=n.natural(si[r]),v=n.natural(sf[r]);need(u<1093&&v<1093,"helper frame bounds");
        const unsigned rank=use(recipes,u,v);need(frames[v].size()==frames[u].size()+rank,"helper rank matches endpoint dimensions");
        auto joined=frames[u];joined.insert(joined.end(),frames[v].begin(),frames[v].end());
        need(binary_rank(joined)==frames[v].size(),"nested helper endpoint");
        ++helper_hist[rank];helpers.push_back({r,u,v,rank});}
    need(hcount==562,"exactly562 helper source roles");
    const auto program=n.children(n.key(0,"program"));need(program.size()==22803,"native word size");
    for(unsigned t:program){const auto e=n.children(t);if(n.str(e[0])=="MOVE"){
        need(e.size()==5,"MOVE tuple");const unsigned u=n.natural(e[2]),v=n.natural(e[3]);
        const unsigned r=use(recipes,u,v);need(r<=8,"proper native paid rank");++native_paid[r];++moves;}}
    need(moves==3453,"every3453 paid contact covered");
    for(const auto& p:recipes)need(p.second.used,"no detached or unused lowering recipe");
    const auto boundaries=c.key(0,"boundaries");
    const auto diagonal=c.children(c.key(0,"diagonal"));
    need(diagonal.size()==32&&c.natural(c.key(0,"ambient_rank"))==axes,"controller dimension");
    std::array<std::vector<unsigned>,32> target_stages;std::array<int,32> target_sign{};
    for(unsigned wire=0;wire<32;++wire){const auto e=c.children(diagonal[wire]);need(e.size()==34,"diagonal Laurent arity");
        target_sign[wire]=c.integer(e[0]);need(target_sign[wire]==1||target_sign[wire]==-1,"unit signed Q exponent");
        for(unsigned j=1;j<34;++j){const unsigned v=c.natural(e[j]);need(v<=1,"diagonal stage bit");
            if(v){const unsigned stage=j-1;need(stage==0||stage==32||stage%2==1,"thick target stage");target_stages[wire].push_back(stage);}}
        const unsigned rank=1+8*unsigned(target_stages[wire].size());target[rank]+=104;
        for(unsigned q:ports){std::vector<Bits> d;
            if(std::find(target_stages[wire].begin(),target_stages[wire].end(),0)==target_stages[wire].end())d.push_back(small(q));
            for(unsigned stage:target_stages[wire])append_stage(d,stage,q,true);
            independent_and_complete(d,rank);}}
    std::vector<Call> calls;std::vector<std::string> word;std::array<unsigned,33> stage_calls{},query_calls{};
    std::array<bool,role_count> credited{};for(unsigned r=0;r<3328;++r)credited[r]=true;
    unsigned wrappers=0,queries=0,idles=0;
    auto native=[&](unsigned stage,unsigned pair){
        need(calls.size()<18&&pair<16,"native call bound");const unsigned ci=unsigned(calls.size()),base=3328+562*ci;
        std::array<bool,role_count> used{};
        for(unsigned r=0;r<799;++r){unsigned mapped;
            if(r>=770)mapped=live_count+r-770;
            else if(port[r]>=0)mapped=104*(2*pair+unsigned(y[r]))+unsigned(port[r]);
            else mapped=base+unsigned(helper[r]);
            need(mapped<role_count-1&&!used[mapped],"injective799-role native relocation, excluding query scratch");used[mapped]=true;
            if(r<770&&port[r]<0){need(!credited[mapped]&&mapped<live_count,"fresh helper ownership");credited[mapped]=true;}}
        calls.push_back({stage,pair,base});++stage_calls[stage];word.push_back("[\"NATIVE\","+std::to_string(ci)+"]");};
    auto qp=[&](unsigned wire,int power){word.push_back("[\"Q_POWER\","+std::to_string(wire)+","+std::to_string(power)+"]");};
    auto sw=[&](unsigned a,unsigned b){word.push_back("[\"SIGNED_SWAP\","+std::to_string(a)+","+std::to_string(b)+"]");};
    for(unsigned t:c.children(c.key(0,"physical_events"))){const auto e=c.children(t);const auto op=c.str(e[0]);
        if(op=="LOCAL"){
            const unsigned stage=c.natural(e[1]),pair=c.natural(e[2]);need(stage<=32,"native stage bound");const bool back=c.boolean(e[3]);
            if(back){++wrappers;qp(2*pair,-2);sw(2*pair,2*pair+1);}
            native(stage,pair);
            if(back){qp(2*pair+1,2);sw(2*pair+1,2*pair);}
        }else if(op=="QUERY_SHEAR"){
            need(e.size()==4&&!c.boolean(e[3]),"all15 source queries are forward");const unsigned stage=c.natural(e[1]);
            need(stage<=32&&c.natural(e[2])<16,"query stage/pair");++query_calls[stage];++queries;word.push_back(c.raw(t));
        }else if(op=="IDLE"){
            need(e.size()==3&&c.natural(e[1])<16,"idle tuple");std::vector<unsigned> stages;std::set<unsigned> seen;
            for(unsigned s:c.children(e[2])){const unsigned stage=c.natural(s);need(stage<=32&&seen.insert(stage).second,"distinct idle stages");stages.push_back(stage);}
            const unsigned rank=8*unsigned(stages.size());paid[rank]+=208;++idles;
            for(unsigned q:ports){std::vector<Bits> d;for(unsigned stage:stages)append_stage(d,stage,q,false);independent_and_complete(d,rank);}
            word.push_back(c.raw(t));
        }else{need(op=="ADD"||op=="SCALE"||op=="SWAP"||op=="SIGNED_SWAP","literal controller point letter");word.push_back(c.raw(t));}}
    need(calls.size()==18&&wrappers==16&&queries==15&&idles==15&&word.size()==218,"complete controller expansion");
    for(unsigned stage=0;stage<=32;++stage){const bool thick=stage==0||stage==32||stage%2==1;
        need(stage_calls[stage]==unsigned(thick)&&query_calls[stage]==unsigned(!thick),"exact thick/thin stage partition");}
    unsigned credit=0;for(unsigned r=0;r<role_count;++r){credit+=unsigned(credited[r]);need(credited[r]==(r<live_count),"live injection and scratch exclusion");}
    need(credit==live_count,"13444 independent productive owners");
    for(const auto& b:native_paid)paid[b.first]+=18*b.second;
    paid[1]+=104*queries;
    for(const auto& b:helper_hist)target[b.first]+=18*b.second;
    const Hist expected_paid{{1,41502},{2,8226},{3,8928},{4,1800},{5,2934},{6,198},{7,108},{8,18},{16,416},{24,416},{32,416},{40,416},{48,416},{56,416},{64,416},{72,208}};
    const Hist expected_target{{1,252},{2,144},{3,72},{4,1926},{5,252},{6,36},{7,162},{8,342},{9,6930},{17,416},{25,416},{33,416},{41,416},{49,416},{57,416},{65,416},{73,208},{145,208}};
    need(paid==expected_paid&&target==expected_target,"assembled finite word has every charged invoice bin");
    std::ofstream out(output);need(bool(out),"raw CU recipe output open");
    out<<"{\n\"format\":\"FastMul-CU-macro-word-v1\",\n\"axes\":145,\"roles\":13474,\"live_roles\":13444,\n"
       <<"\"status\":\"effective finite recipe; not a Lean object or an end-to-end RAM program certificate\",\n"
       <<"\"main_role\":\"104*wire+port_index\",\"native_owned\":[13444,13472],\"query_owned\":13473,\n"
       <<"\"main_source_roles\":"<<n.raw(n.key(0,"live"))<<",\n\"ports\":"<<n.raw(n.key(0,"ports"))<<",\n"
       <<"\"helper_records_format\":[\"source_role\",\"initial_frame\",\"final_frame\",\"rank\"],\n\"helpers\":[";
    bool comma=false;for(const auto& h:helpers){if(comma)out<<',';comma=true;out<<'['<<h[0]<<','<<h[1]<<','<<h[2]<<','<<h[3]<<']';}
    out<<"],\n\"calls_format\":[\"stage\",\"controller_pair\",\"first_helper_role\",\"fresh_axis_start_or_minus_one\"],\n\"calls\":[";
    comma=false;for(const auto& a:calls){if(comma)out<<',';comma=true;out<<'['<<a.stage<<','<<a.pair<<','<<a.helper_base<<','<<(a.stage?int(fresh(a.stage)):-1)<<']';}
    out<<"],\n\"main_targets_format\":[\"wire\",\"Q_sign\",\"rank\",\"thick_stages\"],\n\"main_targets\":[";
    for(unsigned wire=0;wire<32;++wire){if(wire)out<<',';out<<'['<<wire<<','<<target_sign[wire]<<','<<1+8*target_stages[wire].size()<<",[";
        comma=false;for(unsigned s:target_stages[wire]){if(comma)out<<',';comma=true;out<<s;}out<<"]]";}
    out<<"],\n\"right_boundary\":"<<c.raw(c.key(boundaries,"right_program"))<<",\n\"left_boundary\":"<<c.raw(c.key(boundaries,"left_program"))<<",\n"
       <<"\"word\":[[\"MAIN_ENTER\"],[\"RIGHT_BOUNDARY\"]";
    for(const auto& e:word)out<<','<<e;
    out<<",[\"LEFT_BOUNDARY\"],[\"MAIN_EXIT\"]],\n"
       <<"\"native_macro\":\"helper B^-1; main stage entrances; relocated WORD using exact A*C_r*B recipes; main stage exits; helper A^-1\",\n"
       <<"\"native_MOVE_expansion\":\"chronological right B, coordinate C_r, left A on the relocated source role; all native scalar coefficients stay unchanged\",\n"
       <<"\"monomial_convention\":\"|x> maps to i^q(x)|Gx+a>; GMove.perm uses the inverse address map\",\n"
       <<"\"base_geometry\":\"j is the least zero coordinate of q; v=q+e_j; G=(I+v*v^T)*Swap(0,j)=(q,b_1,...,b_8); t_k=(rowweight_k(G)-1)/2 mod2; D0=X_t*product_i C_b_i\",\n"
       <<"\"main_normalizer\":\"columns: q if stage0 absent, otherwise nine standard base axes; append selected fresh axes; greedily complete by standard axes; enter P_G; exit P_G^-1*X_q if Q_sign=-1, otherwise P_G^-1\",\n"
       <<"\"idle_factor\":\"columns: b_i for stage0, plus selected fresh axes; complete by standard axes; chronological P_G^-1, C_rank, P_G, X_t if stage0 present\",\n"
       <<"\"fresh_stage\":\"P=I+sum_i (b_i+e_fresh_i)(b_i+e_fresh_i)^T; enter P on both main rows; exit X_(P*t)*P on both; helpers unchanged\",\n"
       <<"\"query_macro\":\"for each port: COPY x to query_owned; C_q; X_q; ADD to y; CLEAR query_owned; no productive credit\",\n"
       <<"\"basis_completion\":\"scan standard axes in order, retaining exactly those that increase rank\",\n"
       <<"\"dependency\":[\"WORD.json\",\"controller_base.json\",\"native_lowering_recipes.tsv\",\"native_scalar_record_probe.txt\",\"controller_record_probe.txt\",\"native_lowering_record_certificate.txt\",\"record_rate_probe.txt\"]\n}\n";
    need(bool(out),"complete raw CU recipe written");
    std::cout<<"PASS:compact raw-CU recipe;13444 live+30 owned roles;18 injective native relocations\n"
             <<"all2922 native recipes linked;3328 main and1560 idle direction families independent on145 axes (each idle family used on two rows)\n"
             <<"main normalizers enclose both controller boundaries; helpers normalized independently inside their fresh calls\n"
             <<"every paid/target invoice bin agrees; query scratch receives no productive credit\n"
             <<"caps:145 packed binary vectors,799-role relocation; no transform arrays or tensor powers\n"
             <<checks<<" structural/exact assertions; previous scalar/phase/Laurent certificates are explicit dependencies\n";
}
}
int main(int argc,char** argv){
    if(!guard()){std::cerr<<"REFUSED:self-only64 MiB/10 CPU-second limits unavailable\n";return 2;}
    try{need(argc==5,"native, controller, lowering and output paths");rawcu::run(argv[1],argv[2],argv[3],argv[4]);}
    catch(const std::exception& e){std::cerr<<"FAIL:"<<e.what()<<'\n';return 1;}
}
