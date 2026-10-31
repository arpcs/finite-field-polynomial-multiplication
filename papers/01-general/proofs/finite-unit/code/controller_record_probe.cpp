// Publication copy, 31 October 2026: shared-support include path made local; checks unchanged.
// Exact replay of only the fixed 32-wire Laurent controller, one column at a time.
// The 770-public-role supplier, 2^145 data array and tensor powers are not expanded.
// Controller construction: Cinna Davis; forward wrapper: Ali Romman.
// Independent C++ replay and direct-geometry checks: this workspace.
#define main unused_prior_parameter_main
#include "retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>
#include <cstdint>
#include <map>

namespace controllercert {
using E=std::array<std::int8_t,34>;
using P=std::map<E,Q>;
using V=std::array<P,32>;
using Hist=std::map<unsigned,unsigned>;
unsigned peak_terms=0,checked_columns=0;
struct Event{std::string op;unsigned a=0,b=0;int exponent=0;bool back=false;Q q=1;std::vector<unsigned> stages;};
void capped(const V& v){unsigned count=0;for(const auto& p:v){need(p.size()<=1024,"per-wire monomial cap");count+=unsigned(p.size());}
    need(count<=8192,"whole one-column monomial cap");peak_terms=std::max(peak_terms,count);}
void add(P& dst,const P& src,const Q& q){
    need(&dst!=&src,"distinct scalar ADD wires");
    for(const auto& term:src){auto it=dst.find(term.first);const Q value=(it==dst.end()?Q(0):it->second)+q*term.second;
        if(value==Q(0)){if(it!=dst.end())dst.erase(it);}else if(it==dst.end())dst.emplace(term.first,value);else it->second=value;
        need(dst.size()<=1024,"ADD monomial cap");}
}
void scale(P& p,const Q& q){if(q==Q(0)){p.clear();return;}for(auto& term:p)term.second=term.second*q;}
void shift(P& p,const E& e,const Q& q=Q(1)){
    P out;for(const auto& term:p){E k{};for(unsigned j=0;j<34;++j){const int x=int(term.first[j])+e[j];
        need(x>=-64&&x<=64,"Laurent exponent cap");k[j]=std::int8_t(x);}
        out.emplace(k,q*term.second);}p=std::move(out);
}
std::vector<Event> events(const recordjson::Json& j,unsigned token,bool physical){
    std::vector<Event> result;
    for(unsigned t:j.children(token)){
        const auto x=j.children(t);need(x.size()>=3&&x.size()<=4,"controller event arity");
        Event e;e.op=j.str(x[0]);e.a=j.natural(x[1]);
        if(e.op=="LOCAL"||e.op=="QUERY_SHEAR"){
            need(physical&&x.size()==4&&e.a<=32,"native/query stage");e.b=j.natural(x[2]);
            need(e.b<16,"controller pair");e.back=j.boolean(x[3]);
        }else if(e.op=="IDLE"){
            need(physical&&e.a<16&&x.size()==3,"idle pair");
            for(unsigned u:j.children(x[2])){const auto s=j.natural(u);need(s<=32,"idle stage");e.stages.push_back(s);}
            auto sorted=e.stages;std::sort(sorted.begin(),sorted.end());
            need(!sorted.empty()&&std::adjacent_find(sorted.begin(),sorted.end())==sorted.end(),"distinct whole idle stages");
        }else if(e.op=="Q_POWER"){
            need(physical&&e.a<32,"Q-power wire");e.exponent=j.integer(x[2]);need(e.exponent==2||e.exponent==-2,"free even Q power");
        }else if(e.op=="SCALE"){
            need(e.a<32&&x.size()==3,"scale wire");e.q=j.rational(x[2]);
        }else{
            need(e.a<32,"scalar wire");e.b=j.natural(x[2]);need(e.b<32&&e.a!=e.b,"distinct scalar wires");
            if(e.op=="ADD"){need(x.size()==4,"ADD arity");e.q=j.rational(x[3]);}
            else need((e.op=="SWAP"||e.op=="SIGNED_SWAP")&&x.size()==3,"scalar opcode");
        }
        result.push_back(e);need(result.size()<=256,"controller event cap");
    }
    return result;
}
void step(V& rows,const Event& e){
    if(e.op=="LOCAL"||e.op=="QUERY_SHEAR"){
        unsigned x=2*e.b,y=x+1;if(e.back)std::swap(x,y);
        E term{};term[0]=e.back?1:-1;P p=rows[x];shift(p,term);add(rows[y],p,Q(e.back?-1:1));
        if(e.op=="LOCAL"){term.fill(0);term[1+e.a]=1;shift(rows[x],term);shift(rows[y],term);}
    }else if(e.op=="IDLE"){
        E term{};for(unsigned s:e.stages)term[1+s]=1;
        shift(rows[2*e.a],term);shift(rows[2*e.a+1],term);
    }else if(e.op=="Q_POWER"){
        E term{};term[0]=std::int8_t(e.exponent);shift(rows[e.a],term);
    }else if(e.op=="ADD")add(rows[e.a],rows[e.b],e.q);
    else if(e.op=="SCALE")scale(rows[e.a],e.q);
    else{std::swap(rows[e.a],rows[e.b]);if(e.op=="SIGNED_SWAP")scale(rows[e.b],Q(-1));}
    capped(rows);
}
using Diagonal=std::array<E,32>;
bool replay(const std::vector<Event>& right,const std::vector<Event>& word,const std::vector<Event>& left,
            const Diagonal& diag){
    for(unsigned col=0;col<32;++col){
        V rows{};rows[col][E{}]=1;for(const auto& e:right)step(rows,e);
        for(const auto& e:word)step(rows,e);
        for(const auto& e:left)step(rows,e);
        for(unsigned row=0;row<32;++row){P expected;if(row==col)expected.emplace(diag[col],Q(1));
            if(rows[row]!=expected)return false;}
        ++checked_columns;
    }
    return true;
}
void boundary(const recordjson::Json& j,unsigned matrix,const std::vector<Event>& program){
    const auto mat=j.children(matrix);need(mat.size()==32,"boundary matrix dimension");
    for(unsigned col=0;col<32;++col){V rows{};rows[col][E{}]=1;
        for(const auto& e:program)step(rows,e);
        for(unsigned row=0;row<32;++row){const auto values=j.children(mat[row]);need(values.size()==32,"boundary row dimension");
            P expected;const auto q=j.rational(values[col]);if(!(q==Q(0)))expected.emplace(E{},q);
            need(rows[row]==expected,"boundary scalar program exact coefficient");}
    }
}
unsigned parity(unsigned x){unsigned p=0;while(x){p^=x&1u;x>>=1;}return p;}
unsigned weight(unsigned x){unsigned p=0;while(x){p+=x&1u;x>>=1;}return p;}
unsigned act(const std::array<unsigned,9>& columns,unsigned x){unsigned y=0;for(unsigned i=0;i<9;++i)if(x&(1u<<i))y^=columns[i];return y;}
void geometry(const char* path){
    const recordjson::Json j(path,2097152,220000);const auto ports=j.children(j.key(0,"ports"));
    need(ports.size()==104,"source has 104 ports");unsigned nonzero_corrections=0,omitted_phase_errors=0;
    for(unsigned p:ports){const auto q=j.natural(p);need(q<512&&parity(q)==1&&q!=511,"noncharacteristic norm-one port");
        unsigned zero=0;while(q&(1u<<zero))++zero;need(zero<9,"zero coordinate for orthogonal completion");
        const unsigned v=q^(1u<<zero);std::array<unsigned,9> g{};
        for(unsigned k=0;k<9;++k){const unsigned swapped=k==0?zero:k==zero?0:k;
            const unsigned e=1u<<swapped;g[k]=e^(parity(v&e)?v:0);}
        need(g[0]==q,"explicit orthogonal completion through port");
        for(unsigned a=0;a<9;++a)for(unsigned b=0;b<9;++b)
            need(parity(g[a]&g[b])==unsigned(a==b),"completion preserves all dot products");
        unsigned correction=0;for(unsigned coordinate=0;coordinate<9;++coordinate){unsigned w=0;
            for(unsigned k=0;k<9;++k)w+=(g[k]>>coordinate)&1u;
            need(w%2==1,"orthogonal row has odd weight");if(((w-1)/2)%2)correction|=1u<<coordinate;}
        if(correction)++nonzero_corrections;
        // Only the nine-bit phase-polynomial domain is enumerated; no 145-axis array.
        unsigned missing_correction=0;
        for(unsigned x=0;x<512;++x){unsigned phases=0;for(unsigned k=0;k<9;++k)phases+=parity(g[k]&x);
            need(phases%4==(weight(x)+2*parity(correction&x))%4,"exact mod-four translation correction");
            if(phases%4!=weight(x)%4)++missing_correction;}
        need(missing_correction==256,"omitted translation phase fails on half the nine-bit domain");
        omitted_phase_errors+=missing_correction;
        // Verify the seventeen-axis involution on a basis, with port as the fixed line.
        std::array<unsigned,8> w{};for(unsigned k=0;k<8;++k)w[k]=g[k+1]^(1u<<(9+k));
        auto route=[&](unsigned x){unsigned y=x;for(unsigned k=0;k<8;++k)if(parity(w[k]&x))y^=w[k];return y;};
        need(route(q)==q,"seventeen-axis route fixes Q");
        for(unsigned k=0;k<8;++k){need(route(g[k+1])==(1u<<(9+k)),"route sends old orthogonal axis to fresh axis");
            need(route(1u<<(9+k))==g[k+1],"route sends fresh axis to old orthogonal axis");}
        for(unsigned a=0;a<17;++a){need(route(route(1u<<a))==(1u<<a),"route is involutive");
            for(unsigned b=0;b<17;++b)need(parity(route(1u<<a)&route(1u<<b))==unsigned(a==b),"route is orthogonal");}
        // Check that the coordinate transform is invertible without enumerating its vectors.
        for(unsigned x=0;x<9;++x)need(act(g,1u<<x)==g[x],"completion column encoding");
    }
    std::cout<<"direct_geometry:104 ports; 9-bit phase domains; 17-axis basis routes; nonzero_translation_corrections="
             <<nonzero_corrections<<"; omitted-correction errors="<<omitted_phase_errors<<"\n";
}
void run(const char* basepath,const char* wordpath){
    const recordjson::Json j(basepath);need(j.str(j.key(0,"kind"))=="complex"&&j.natural(j.key(0,"pairs"))==16&&
        j.natural(j.key(0,"prefix_pairs"))==7&&j.natural(j.key(0,"ambient_rank"))==145,"pinned p16/a7 controller");
    const auto boundaries=j.key(0,"boundaries");const auto left=events(j,j.key(boundaries,"left_program"),false);
    const auto right=events(j,j.key(boundaries,"right_program"),false);
    boundary(j,j.key(boundaries,"left"),left);boundary(j,j.key(boundaries,"right"),right);
    const auto base=events(j,j.key(0,"physical_events"),true);need(base.size()==154,"source physical event count");
    Diagonal diag{};const auto d=j.children(j.key(0,"diagonal"));need(d.size()==32,"main diagonal count");
    Hist main;for(unsigned role=0;role<32;++role){const auto term=j.children(d[role]);need(term.size()==34,"Laurent diagonal dimension");
        unsigned stages=0;for(unsigned k=0;k<34;++k){const int n=j.integer(term[k]);
            need(k==0?(n==1||n==-1):(n==0||n==1),"diagonal signed Q and stage bits");
            if(k&&n){const unsigned s=k-1;need(s==0||s==32||(s%2==1),"only thick diagonal stages");++stages;}
            diag[role][k]=std::int8_t(n);}
        main[1+8*stages]+=104;
    }
    need(replay(right,base,left,diag),"entire base Laurent identity");
    std::vector<Event> forward;unsigned wrappers=0,full=0,query=0,idle=0;Hist idles;
    std::array<unsigned,33> full_stage{},query_stage{};
    for(const auto& e:base){
        if(e.op=="LOCAL"){++full;++full_stage[e.a];if(e.back){++wrappers;
            Event a;a.op="Q_POWER";a.a=2*e.b;a.exponent=-2;forward.push_back(a);
            Event b;b.op="SIGNED_SWAP";b.a=2*e.b;b.b=b.a+1;forward.push_back(b);
            Event f=e;f.back=false;forward.push_back(f);
            a.a=2*e.b+1;a.exponent=2;forward.push_back(a);std::swap(b.a,b.b);forward.push_back(b);
        }else forward.push_back(e);}
        else{forward.push_back(e);if(e.op=="QUERY_SHEAR"){++query;++query_stage[e.a];}
            if(e.op=="IDLE"){++idle;idles[8*unsigned(e.stages.size())]+=208;
                for(unsigned s:e.stages)need(s==0||s==32||(s%2==1),"idle contains only thick stages");}}
    }
    need(wrappers==16&&full==18&&query==15&&idle==15&&forward.size()==218,"all-forward wrapper and complete census");
    for(unsigned s=0;s<=32;++s){const bool thick=s==0||s==32||(s%2==1);
        need(full_stage[s]==unsigned(thick)&&query_stage[s]==unsigned(!thick),"exact thick/thin stage sets");}
    need(replay(right,forward,left,diag),"entire all-forward Laurent identity");
    auto missing=forward;auto it=std::find_if(missing.begin(),missing.end(),[](const Event& e){return e.op=="Q_POWER";});
    need(it!=missing.end(),"Q-power negative-control site");missing.erase(it);
    need(!replay(right,missing,left,diag),"missing central translation is rejected");
    missing=forward;it=std::find_if(missing.begin(),missing.end(),[](const Event& e){return e.op=="QUERY_SHEAR";});
    need(it!=missing.end(),"query negative-control site");missing.erase(it);
    need(!replay(right,missing,left,diag),"missing paid query is rejected");
    missing=forward;it=std::find_if(missing.begin(),missing.end(),[](const Event& e){return e.op=="SIGNED_SWAP";});
    need(it!=missing.end(),"signed-swap negative-control site");it->op="SWAP";
    need(!replay(right,missing,left,diag),"wrong swap sign is rejected");
    std::cout<<"controller:32 base columns and 32 forward columns exact; boundary matrices verified; three mutations rejected\n"
             <<"native_calls="<<full<<" query_calls="<<query<<" idle_calls="<<idle<<" wrapper_sites="<<wrappers<<"\n";
    std::cout<<"main_targets=";for(const auto& rc:main)std::cout<<rc.first<<':'<<rc.second<<',';
    std::cout<<"\nwhole_idle_paid=";for(const auto& rc:idles)std::cout<<rc.first<<':'<<rc.second<<',';
    std::cout<<"\n";geometry(wordpath);
    std::cout<<"PASS:"<<checks<<" exact assertions; peak one-column monomials="<<peak_terms<<"\n"
             <<"This certifies the finite controller and direct geometry, conditional on the native supplier interface.\n";
}
}
int main(int argc,char** argv){
    if(!guard()){std::cerr<<"REFUSED: self-only 64 MiB/10 CPU-second limits unavailable\n";return 2;}
    try{need(argc==3,"controller and native-word input paths");controllercert::run(argv[1],argv[2]);}
    catch(const std::exception& e){std::cerr<<"FAIL:"<<e.what()<<"\n";return 1;}
}
