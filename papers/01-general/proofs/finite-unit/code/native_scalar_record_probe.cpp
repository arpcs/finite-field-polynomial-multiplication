// Publication copy, 31 October 2026: shared-support include path made local; checks unchanged.
// Exact streaming certificate of the finite logical scalar endpoint.
// One column at a time: at most 799 rational scalars, never a 799x799 matrix.
// Frames/owned contacts and their complete rank invoice are checked once.
#define main unused_prior_parameter_main
#include "retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>
#include <map>

namespace nativescalar {
using Hist=std::map<unsigned,unsigned>;
enum class Op{zero,add,copy,scale};
struct Event{Op op;unsigned dst,src;Q coefficient;};
unsigned rank(std::vector<unsigned> basis){
    std::array<unsigned,9> p{};unsigned result=0;
    for(unsigned v:basis){need(v>0&&v<512,"nine-bit nonzero frame vector");
        for(int b=8;b>=0;--b)if(v&(1u<<b)){if(p[b])v^=p[b];else{p[b]=v;++result;break;}}}
    return result;
}
unsigned joined(const std::vector<unsigned>& a,const std::vector<unsigned>& b){auto both=a;both.insert(both.end(),b.begin(),b.end());return rank(both);}
unsigned parity(unsigned n){unsigned p=0;while(n){p^=n&1u;n>>=1;}return p;}
struct Word{std::vector<Event> scalar;Hist paid,helpers;std::array<bool,112> live{};unsigned events=0;};
Word read(const char* path){
    const recordjson::Json j(path,2097152,220000);Word word;
    need(j.natural(j.key(0,"public"))==770&&j.natural(j.key(0,"owned_fields"))==29,"exact public/owned inventory");
    need(j.str(j.key(0,"schema"))=="p104-accumulated-block-composition/2","native word schema");
    std::vector<std::vector<unsigned>> frames;
    for(unsigned f:j.children(j.key(0,"frames"))){std::vector<unsigned> basis;
        for(unsigned x:j.children(f))basis.push_back(j.natural(x));
        need(basis.size()<=9&&rank(basis)==basis.size(),"independent frame basis");frames.push_back(basis);}
    need(frames.size()==1093,"exact frame table size");
    auto frame=[&](unsigned id)->const std::vector<unsigned>&{need(id<frames.size(),"frame ID bound");return frames[id];};
    const auto initial=j.children(j.key(0,"initial")),final=j.children(j.key(0,"final"));
    need(initial.size()==770&&final.size()==770,"public boundary lengths");
    std::array<unsigned,799> at{};std::array<unsigned,770> start{},end{};std::array<bool,799> active{};
    for(unsigned r=0;r<770;++r){at[r]=start[r]=j.natural(initial[r]);end[r]=j.natural(final[r]);frame(at[r]);frame(end[r]);active[r]=true;}
    const auto live=j.children(j.key(0,"live")),ports=j.children(j.key(0,"ports"));
    need(live.size()==104&&ports.size()==104,"live port lists");
    for(unsigned k=0;k<104;++k){const unsigned r=j.natural(live[k]),q=j.natural(ports[k]);
        need(r<112&&!word.live[r]&&q<512&&parity(q)==1&&q!=511,"distinct legal main role and port");word.live[r]=true;
        const auto& ix=frame(start[r]);const auto& ox=frame(end[r]);
        const auto& iy=frame(start[r+112]);const auto& oy=frame(end[r+112]);
        need(ix.size()==1&&ix[0]==q&&ox.size()==9&&iy.empty()&&oy.size()==8,"exact main boundary subspaces");
        for(unsigned v:oy)need(parity(v&q)==0,"Y endpoint is the port hyperplane");
    }
    unsigned owned=0,peak=0,lifetimes=0;
    for(unsigned t:j.children(j.key(0,"program"))){
        const auto a=j.children(t);need(a.size()>=3&&a.size()<=5,"native event arity");
        const auto op=j.str(a[0]);const auto r=j.natural(a[1]);need(r<799,"native register bound");++word.events;
        if(op=="INIT"){
            need(a.size()==3&&r>=770&&!active[r],"owned INIT chronology");at[r]=j.natural(a[2]);frame(at[r]);active[r]=true;
            ++lifetimes;peak=std::max(peak,++owned);word.scalar.push_back({Op::zero,r,0,Q(0)});
        }else if(op=="CLEAR"){
            need(a.size()==3&&r>=770&&active[r]&&at[r]==j.natural(a[2]),"owned CLEAR chronology/chart");
            active[r]=false;--owned;word.scalar.push_back({Op::zero,r,0,Q(0)});
        }else if(op=="MOVE"){
            need(a.size()==5&&active[r],"active MOVE");const unsigned u=j.natural(a[2]),v=j.natural(a[3]);
            const bool private_move=j.boolean(a[4]);need(at[r]==u&&private_move==(r>=770),"MOVE chart/private flag");
            const auto& old=frame(u);const auto& next=frame(v);const unsigned common=joined(old,next);
            need(private_move?(old.size()>next.size()&&common==old.size()):
                              (old.size()<next.size()&&common==next.size()),"strict nested chronological transport");
            const unsigned paid=unsigned(private_move?old.size()-next.size():next.size()-old.size());
            need(paid>=1&&paid<=8,"proper local paid rank");++word.paid[paid];at[r]=v;
        }else{
            need(active[r]&&(op=="ADD"||op=="COPY"||op=="SCALE"),"active scalar opcode");
            const unsigned coeff=op=="SCALE"?2:3,last=op=="SCALE"?3:4;
            need(a.size()==last+1&&at[r]==j.natural(a[last]),"scalar destination chart");
            const auto q=j.rational(a[coeff]);need(!(q==Q(0))&&mpz_popcount(mpq_denref(q.v))==1,"nonzero dyadic coefficient");
            if(op=="SCALE")word.scalar.push_back({Op::scale,r,0,q});
            else{const auto s=j.natural(a[2]);need(s<799&&s!=r&&active[s]&&at[s]==at[r],"identical exact common chart");
                if(op=="COPY")need(r>=770,"COPY only overwrites an owned role");
                word.scalar.push_back({op=="COPY"?Op::copy:Op::add,r,s,q});}
        }
        need(word.events<=26000&&word.scalar.size()<=26000,"fixed native word cap");
    }
    need(word.events==22803&&lifetimes==31&&peak==13&&owned==0,"complete native event/owned census");
    for(unsigned r=0;r<770;++r){need(at[r]==end[r],"all final public charts");
        const bool main=(r<112&&word.live[r])||(r>=112&&r<224&&word.live[r-112]);
        if(!main){const auto& u=frame(start[r]);const auto& v=frame(end[r]);
            need(v.size()>u.size()&&joined(u,v)==v.size(),"whole helper endpoint strictly nested");
            ++word.helpers[unsigned(v.size()-u.size())];}
    }
    need(word.paid==Hist{{1,2219},{2,457},{3,496},{4,100},{5,163},{6,11},{7,6},{8,1}},"complete native paid invoice");
    need(word.helpers==Hist{{1,14},{2,8},{3,4},{4,107},{5,14},{6,2},{7,9},{8,19},{9,385}},"all 562 independent helper ranks");
    return word;
}
bool column(const Word& w,unsigned col,int mutation){
    std::array<Q,799> rows{};rows[col]=1;unsigned site=0;
    for(const auto& e:w.scalar){
        if(mutation==1&&e.op==Op::add&&site++==0)continue;
        if(e.op==Op::zero)rows[e.dst]=0;
        else if(e.op==Op::scale)rows[e.dst]=rows[e.dst]*e.coefficient;
        else if(e.op==Op::copy)rows[e.dst]=rows[e.src]*e.coefficient;
        else rows[e.dst]=rows[e.dst]+rows[e.src]*e.coefficient;
    }
    for(unsigned r=0;r<799;++r){
        const long expected=long(r==col)+long(r>=112&&r<224&&w.live[r-112]&&r-112==col);
        if(!(rows[r]==Q(expected)))return false;
    }
    return true;
}
void run(const char* path){
    const Word word=read(path);
    for(unsigned col=0;col<770;++col)need(column(word,col,0),"exact scalar endpoint on every public input basis column");
    bool rejects=false;for(unsigned col=0;col<770&&!rejects;++col)rejects=!column(word,col,1);
    need(rejects,"omitted first scalar ADD rejected");
    std::cout<<"PASS:770 exact streamed input columns; all 799 output coefficients checked per column\n"
             <<"scalar_events="<<word.scalar.size()<<" frame_events="<<word.events-word.scalar.size()
             <<"; main shear + 562 independent helper identities; owned output zero\n"
             <<"common charts, strict nested transports, owned lifetimes and main boundary spaces verified\n"
             <<"peak rational state=799; no dense global matrix; per-rational cap=2048 bits\n"
             <<"missing-ADD negative control rejected; "<<checks<<" structural/exact assertions\n"
             <<"Native frame operators/lowerings use the separate mathematical construction.\n";
}
}
int main(int argc,char** argv){
    if(!guard()){std::cerr<<"REFUSED: self-only 64 MiB/10 CPU-second limits unavailable\n";return 2;}
    try{need(argc==2,"native-word input path");nativescalar::run(argv[1]);}
    catch(const std::exception& e){std::cerr<<"FAIL:"<<e.what()<<"\n";return 1;}
}
