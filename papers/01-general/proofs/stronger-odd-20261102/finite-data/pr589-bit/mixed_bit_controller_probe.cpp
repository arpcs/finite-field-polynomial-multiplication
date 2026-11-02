// Exact32-wire formal monomial controller, never its enormous address matrix.
#define main unused_prior_parameter_main
#include "../retuned_network_exponent_bounded_20261029.cpp"
#undef main
#include "bounded_json.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
namespace bitcontroller {
constexpr unsigned wires=32,ports=111,helpers=439;
using Mask=std::uint64_t;using Poly=std::set<Mask>;using Values=std::array<Poly,wires>;using Rows=std::array<Mask,wires>;
Mask number(const recordjson::Json& j,unsigned id){const auto s=j.raw(id);need(!s.empty()&&s.size()<=16,"bounded controller integer token");Mask x=0;for(char c:s){need(c>='0'&&c<='9',"unsigned controller token");x=x*10+Mask(c-'0');need(x<(Mask(1)<<50),"controller integer cap");}return x;}
void toggle(Poly& a,Mask x){auto it=a.find(x);if(it==a.end())a.insert(x);else a.erase(it);need(a.size()<=64,"formal monomial support cap64");}
Poly sum(Poly a,const Poly& b){for(Mask x:b)toggle(a,x);return a;}
Poly shift(const Poly& a,Mask s){Poly b;for(Mask x:a)b.insert(x^s);return b;}
struct Event{unsigned kind=0,a=0,b=0;Mask mask=0;bool reverse=false;};
struct Op{bool swap;unsigned a,b;};
std::vector<Op> factor(Rows a){std::vector<Op> ops;for(unsigned j=0;j<wires;++j){unsigned p=j;while(p<wires&&!((a[p]>>j)&1))++p;need(p<wires,"constant binary boundary full rank");if(p!=j){std::swap(a[p],a[j]);ops.push_back({true,p,j});}for(unsigned i=0;i<wires;++i)if(i!=j&&((a[i]>>j)&1)){a[i]^=a[j];ops.push_back({false,i,j});}}for(unsigned i=0;i<wires;++i)need(a[i]==(Mask(1)<<i),"boundary reduction ends at identity");return ops;}
Values boundary(Values x,const std::vector<Op>& ops){for(auto it=ops.rbegin();it!=ops.rend();++it){if(it->swap)std::swap(x[it->a],x[it->b]);else x[it->a]=sum(x[it->a],x[it->b]);}return x;}
Rows rows(const recordjson::Json& j,unsigned node){const auto a=j.children(node);need(a.size()==wires,"32 boundary rows");Rows out;for(unsigned i=0;i<wires;++i){out[i]=number(j,a[i]);need(out[i]<(Mask(1)<<wires),"boundary32-bit row cap");}return out;}
unsigned bits(Mask a){unsigned n=0;while(a){n+=unsigned(a&1);a>>=1;}return n;}
bool endpoint(const std::vector<Event>& events,const std::vector<Op>& left,const std::vector<Op>& right,const std::array<Mask,wires>& diagonal,int omit_kind=-1){bool omitted=false;for(unsigned basis=0;basis<wires;++basis){Values x;x[basis].insert(0);x=boundary(std::move(x),right);bool skipped=false;for(const auto& e:events){if(!skipped&&int(e.kind)==omit_kind){skipped=true;omitted=true;continue;}if(e.kind<=1){unsigned a=2*e.b,b=a+1;if(e.reverse)std::swap(a,b);x[b]=sum(x[b],shift(x[a],1));if(e.kind==0){x[a]=shift(x[a],Mask(1)<<(e.a+1));x[b]=shift(x[b],Mask(1)<<(e.a+1));}}else if(e.kind==2){x[2*e.a]=shift(x[2*e.a],e.mask);x[2*e.a+1]=shift(x[2*e.a+1],e.mask);}else if(e.kind==3)x[e.a]=sum(x[e.a],x[e.b]);else std::swap(x[e.a],x[e.b]);}x=boundary(std::move(x),left);for(unsigned i=0;i<wires;++i){const Poly expected=i==basis?Poly{diagonal[i]}:Poly{};if(x[i]!=expected)return false;}}return omit_kind<0||!omitted;}
void run(const std::string& path){recordjson::Json j(path.c_str(),32768,12000);need(j.natural(j.key(0,"pairs"))==16&&j.natural(j.key(0,"ambient_rank"))==127,"actual p16 BIT schema");const auto b=j.key(0,"boundaries");const auto lrows=rows(j,j.key(b,"left_rows")),rrows=rows(j,j.key(b,"right_rows"));const auto left=factor(lrows),right=factor(rrows);std::array<Mask,wires> diagonal{};const auto da=j.children(j.key(0,"diagonal"));need(da.size()==wires,"all32 independent output jobs");for(unsigned i=0;i<wires;++i)diagonal[i]=number(j,da[i]);
    std::vector<Event> events;std::set<unsigned> thick;unsigned queries=0,idles=0;std::map<unsigned,unsigned> paid,target;const auto ea=j.children(j.key(0,"physical_events"));need(ea.size()<=200,"finite event cap");
    for(unsigned node:ea){const auto a=j.children(node);need(!a.empty(),"nonempty controller event");const auto type=j.str(a[0]);Event e;if(type=="LOCAL"||type=="QUERY_SHEAR"){need(a.size()==4,"local event arity");e.kind=type=="LOCAL"?0:1;e.a=j.natural(a[1]);e.b=j.natural(a[2]);e.reverse=j.boolean(a[3]);need(e.a<=32&&e.b<16,"stage/pair bounds");if(e.kind==0)need(thick.insert(e.a).second,"one native helper family per thick stage");else ++queries;}else if(type=="IDLE"){need(a.size()==3,"idle arity");e.kind=2;e.a=j.natural(a[1]);const auto chosen=j.children(a[2]);need(e.a<16&&!chosen.empty()&&chosen.size()<=9,"idle pair/block bounds");for(unsigned t:chosen){const unsigned s=j.natural(t);need(s<=32&&!(e.mask&(Mask(1)<<(s+1))),"distinct idle stage block");e.mask|=Mask(1)<<(s+1);}paid[7*unsigned(chosen.size())]+=2*ports;++idles;}else{need((type=="ADD"||type=="SWAP")&&a.size()==3,"point event arity/kind");e.kind=type=="ADD"?3:4;e.a=j.natural(a[1]);e.b=j.natural(a[2]);need(e.a<wires&&e.b<wires&&e.a!=e.b,"distinct point roles");}events.push_back(e);}
    need(thick.size()==18&&queries==15,"actual thick/query counts");Mask allowed=1;for(unsigned s:thick)allowed|=Mask(1)<<(s+1);for(const auto& e:events)if(e.kind==2)need(!(e.mask&~allowed),"idle reads only actual orthogonal thick blocks");
    const std::map<unsigned,unsigned> local{{1,1323},{2,1342},{3,79},{4,44},{5,102},{6,11},{7,19}};for(auto rc:local)paid[rc.first]+=18*rc.second;paid[1]+=queries*ports;target[8]=18*helpers;for(Mask d:diagonal){need(!(d&~allowed),"output endpoint uses only actual projector blocks");target[unsigned(d&1)+7*bits(d>>1)]+=ports;}
    const auto invoice=j.key(0,"invoice");for(const auto name:{"paid","targets"}){const auto bins=j.children(j.key(invoice,name));std::map<unsigned,unsigned> expected;need(bins.size()%2==0,"invoice pairs");for(unsigned i=0;i<bins.size();i+=2)expected[unsigned(std::stoul(j.str(bins[i])))]=j.natural(bins[i+1]);need((std::string(name)=="paid"?paid:target)==expected,"derive every frozen invoice bin from actual events");}
    need(endpoint(events,left,right,diagonal),"all32 formal coefficient columns give independent declared monomials");need(!endpoint(events,left,right,diagonal,1)&&!endpoint(events,left,right,diagonal,2)&&!endpoint(events,left,right,diagonal,3),"omitted query,idle and point bridge controls fail");
    unsigned pc=0,tc=0,pm=0,tm=0;for(auto rc:paid){pc+=rc.second;pm+=rc.first*rc.second;}for(auto rc:target){tc+=rc.second;tm+=rc.first*rc.second;}need(pc==57555&&tc==11454&&tm-pm==753,"complete productive count and rank surplus");need(paid.rbegin()->first==63&&target.begin()->first==8,"raw strict separation failure retained");
    std::cout<<"formal_columns=32 native_thick_calls=18 thin_query_shears=15 helper_families=18x439 events="<<events.size()<<" idles="<<idles<<" boundary_point_ops="<<left.size()+right.size()<<'\n';
    std::cout<<"paid_queries="<<pc<<" independent_productive_fields="<<tc<<" paid_rank_mass="<<pm<<" target_rank_mass="<<tm<<" surplus="<<tm-pm<<" raw_separation=FAIL_requires_strictification\n";
    std::cout<<"negative_controls omitted_query=1 omitted_idle=1 omitted_bridge=1\nPASS assertions="<<checks<<" sparse monomial support<=64,scalar wires32,stages33; no address tensor or GL cover\n";
}
}
int main(int argc,char** argv){if(!guard()){std::cerr<<"REFUSED self-only64MiB/10CPU guard\n";return 2;}try{need(argc==3&&std::string(argv[1])=="bounded","bounded marker and pinned controller");bitcontroller::run(argv[2]);return 0;}catch(const std::exception& e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
