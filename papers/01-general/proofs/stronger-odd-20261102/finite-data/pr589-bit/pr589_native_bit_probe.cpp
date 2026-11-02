// Exact finite PR589 premises: rational8D frames and scalar661-field columns.
// No full address tensor, cover, or dense661x661 scalar matrix is constructed.
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
#include <tuple>
#include <vector>
namespace pr589 {
constexpr unsigned h=8,v=111,R=439,n=661;
using Mat=std::array<Q,64>;
Q& at(Mat& a,unsigned i,unsigned j){return a[i*8+j];}
const Q& at(const Mat& a,unsigned i,unsigned j){return a[i*8+j];}
Mat ident(){Mat a;for(unsigned i=0;i<8;++i)at(a,i,i)=1;return a;}
Mat mul(const Mat& a,const Mat& b){Mat c;for(unsigned i=0;i<8;++i)for(unsigned k=0;k<8;++k)if(!(at(a,i,k)==Q(0)))for(unsigned j=0;j<8;++j)if(!(at(b,k,j)==Q(0)))at(c,i,j)=at(c,i,j)+at(a,i,k)*at(b,k,j);return c;}
Mat minus(const Mat& a,const Mat& b){Mat c;for(unsigned i=0;i<64;++i)c[i]=a[i]-b[i];return c;}
Mat transpose(const Mat& a){Mat b;for(unsigned i=0;i<8;++i)for(unsigned j=0;j<8;++j)at(b,i,j)=at(a,j,i);return b;}
bool equal(const Mat& a,const Mat& b){for(unsigned i=0;i<64;++i)if(!(a[i]==b[i]))return false;return true;}
Mat inverse(Mat a,unsigned d){Mat b=ident();for(unsigned j=0;j<d;++j){unsigned p=j;while(p<d&&at(a,p,j)==Q(0))++p;need(p<d,"independent rational frame basis");for(unsigned k=0;k<d;++k){std::swap(at(a,j,k),at(a,p,k));std::swap(at(b,j,k),at(b,p,k));}const Q pivot=at(a,j,j);for(unsigned k=0;k<d;++k){at(a,j,k)=at(a,j,k)/pivot;at(b,j,k)=at(b,j,k)/pivot;}for(unsigned i=0;i<d;++i)if(i!=j){const Q c=at(a,i,j);for(unsigned k=0;k<d;++k){at(a,i,k)=at(a,i,k)-c*at(a,j,k);at(b,i,k)=at(b,i,k)-c*at(b,j,k);}}}return b;}
struct Frame{unsigned dimension=0;Mat projector;};
std::map<int,Frame> frames;
const Frame& frame(int key){const auto it=frames.find(key);need(it!=frames.end(),"frame identity present");return it->second;}
void load_frames(const std::string& dir){recordjson::Json j((dir+"/frames.json").c_str(),131072,90000);const auto f=j.children(j.key(0,"frames"));need(f.size()%2==0&&f.size()/2<=700,"finite frame cap");
    for(unsigned i=0;i<f.size();i+=2){const int key=std::stoi(j.str(f[i]));const unsigned object=f[i+1],d=j.natural(j.key(object,"dim"));need(d<=8,"frame rank cap");const auto rows=j.children(j.key(object,"B"));need(rows.size()==d,"frame basis dimension");Mat b,gram;for(unsigned a=0;a<d;++a){const auto row=j.children(rows[a]);need(row.size()==8,"rational8D basis row");for(unsigned k=0;k<8;++k)at(b,a,k)=j.rational(row[k]);}for(unsigned a=0;a<d;++a)for(unsigned c=0;c<d;++c)for(unsigned k=0;k<8;++k)at(gram,a,c)=at(gram,a,c)+at(b,a,k)*at(b,c,k);
        const auto gi=inverse(gram,d);Mat p;for(unsigned k=0;k<8;++k)for(unsigned l=0;l<8;++l)for(unsigned a=0;a<d;++a)if(!(at(b,a,k)==Q(0)))for(unsigned c=0;c<d;++c)if(!(at(b,c,l)==Q(0)))at(p,k,l)=at(p,k,l)+at(b,a,k)*at(gi,a,c)*at(b,c,l);
        need(equal(mul(p,p),p)&&equal(transpose(p),p),"exact rational idempotent/symmetry");Q trace=0;for(unsigned k=0;k<8;++k)trace=trace+at(p,k,k);need(trace==Q(long(d)),"split frame rank");need(frames.emplace(key,Frame{d,p}).second,"distinct frame labels");
    }
}
using Record=std::array<int,6>;
std::vector<Record> records;
std::array<int,n> start{},finish{};
std::vector<std::array<Q,8>> roots;
void load_word(const std::string& dir){roots.resize(v);recordjson::Json j((dir+"/WORD.json").c_str(),262144,150000);need(j.natural(j.key(0,"h"))==8&&j.natural(j.key(0,"v"))==v&&j.natural(j.key(0,"R"))==R,"actual local source type");for(const auto name:{"start","final"}){const auto a=j.children(j.key(0,name));need(a.size()==n,"all source role frames");for(unsigned i=0;i<n;++i)(name==std::string("start")?start:finish)[i]=int(j.natural(a[i]));}
    const auto lines=j.children(j.key(0,"lines"));need(lines.size()==v,"all root ports");for(unsigned i=0;i<v;++i){const auto x=j.children(lines[i]);need(x.size()==8,"root vector dimension");for(unsigned k=0;k<8;++k)roots[i][k]=j.rational(x[k]);}
    std::ifstream input(dir+"/249-records.bin",std::ios::binary);need(bool(input),"binary instruction source");input.seekg(0,std::ios::end);const auto size=input.tellg();need(size==653616&&size%24==0,"bounded complete instruction file");input.seekg(0);for(unsigned k=0;k<unsigned(size/24);++k){std::array<unsigned char,24> bytes{};input.read(reinterpret_cast<char*>(bytes.data()),24);need(bool(input),"complete six-int record");Record r{};for(unsigned z=0;z<6;++z){std::uint32_t u=0;for(unsigned t=0;t<4;++t)u|=std::uint32_t(bytes[4*z+t])<<(8*t);r[z]=u<0x80000000u?int(u):int(std::int64_t(u)-4294967296LL);}records.push_back(r);}need(records.size()<=28000,"instruction count cap");
}
void geometry(){const Mat I=ident(),zero{};for(unsigned port=0;port<v;++port){const auto& q=roots[port];Q norm=0;Mat p;for(unsigned i=0;i<8;++i){norm=norm+q[i]*q[i];for(unsigned k=0;k<8;++k)at(p,i,k)=q[i]*q[k]/4;}need(norm==Q(4),"native root norm4");const auto k=minus(I,p);need(equal(frame(start[port]).projector,p)&&equal(frame(start[v+port]).projector,zero),"actual main source frames");need(equal(frame(finish[port]).projector,I)&&equal(frame(finish[v+port]).projector,k),"actual main target frames");
        std::array<Q,8> u;Q nu=0;for(unsigned i=0;i<8;++i){u[i]=Q(long(i==0))-q[i]/2;nu=nu+u[i]*u[i];}Mat g=I;if(!(nu==Q(0)))for(unsigned i=0;i<8;++i)for(unsigned l=0;l<8;++l)at(g,i,l)=at(g,i,l)-2*u[i]*u[l]/nu;
        need(equal(mul(transpose(g),g),I),"fixed rational orthogonal port chart");for(unsigned i=0;i<8;++i)need(2*at(g,i,0)==q[i],"port chart sends2e0 to actual root");Mat aa;for(unsigned i=0;i<8;++i)for(unsigned l=0;l<8;++l)for(unsigned c=1;c<8;++c)at(aa,i,l)=at(aa,i,l)+at(g,i,c)*at(g,l,c);need(equal(aa,k)&&equal(mul(p,aa),zero),"exact7D orthogonal complement and symbolic15D involutive port lift");
    }for(unsigned i=2*v;i<n;++i)need(frame(start[i]).dimension==0&&frame(finish[i]).dimension==8,"every dirty helper has its OWN full rank8 endpoint");
}
std::map<unsigned,unsigned> expected_profile{{1,1323},{2,1342},{3,79},{4,44},{5,102},{6,11},{7,19}};
void transition_geometry(){std::set<std::tuple<int,int,int>> seen;unsigned copy=0;for(const auto& r:records){if(r[0]==0){need(r[4]>=0,"nonnegative transition rank");seen.emplace(r[2],r[3],r[4]);}else if(r[0]==2){const auto& a=frame(r[3]);const auto& b=frame(r[4]);const Frame& lo=a.dimension<b.dimension?a:b;const Frame& hi=a.dimension<b.dimension?b:a;need(equal(mul(lo.projector,hi.projector),lo.projector)&&equal(mul(hi.projector,lo.projector),lo.projector),"source-owned COPY has nested frames");const auto d=minus(hi.projector,lo.projector);need(equal(mul(d,d),d)&&hi.dimension-lo.dimension==7,"actual COPY residual rank7");++copy;}}
    for(const auto& x:seen){const auto& a=frame(std::get<0>(x));const auto& b=frame(std::get<1>(x));need(b.dimension>=a.dimension&&b.dimension-a.dimension==unsigned(std::get<2>(x)),"literal monotone residual rank");need(equal(mul(a.projector,b.projector),a.projector)&&equal(mul(b.projector,a.projector),a.projector),"exact nested rational projectors at every distinct transport");}need(copy==9,"all9 source-owned copies charged");std::cout<<"frames="<<frames.size()<<" distinct_nested_transports="<<seen.size()<<" root_ports="<<v<<" owned_copy_episodes="<<copy<<'\n';
}
void scalar(bool reverse){std::array<int,n+1> current{};for(unsigned i=0;i<n;++i)current[i]=reverse?finish[i]:start[i];current[n]=-1;int owned=-1;unsigned adds=0,copies=0;std::map<unsigned,unsigned> profile;
    for(unsigned z=0;z<records.size();++z){const auto& r=records[reverse?records.size()-1-z:z];const int op=r[0],x=r[1],y=r[2],c=r[3],f=r[4];need(x>=0&&x<int(n)&&op>=0&&op<=3,"native instruction role/op bounds");if(op==0){const int old=reverse?c:y,next=reverse?y:c;need(current[x]==old,"literal transport entrance frame");current[x]=next;if(f)++profile[unsigned(f)];}else if(op==1){need(y>=0&&y<int(n+1)&&x!=y&&current[x]==f&&current[y]==f,"actual common-frame ADD");need(owned!=x,"COPY source not overwritten while owned temporary is live");need(c==1||c==-1,"F2 data ADD coefficient is unit");++adds;}else if(op==(reverse?3:2)){need(owned<0&&y==int(n)&&current[x]==c,"private COPY entrance and ownership");owned=x;current[n]=f;const auto a=frame(c).dimension,b=frame(f).dimension;++profile[a<b?b-a:a-b];++copies;}else{need(owned==x&&y==int(n),"owned COPY closes its own lifetime");owned=-1;current[n]=-1;}}
    need(owned<0&&adds==24305&&copies==9&&profile==expected_profile,"complete literal scalar and recursive invoice");for(unsigned i=0;i<n;++i)need(current[i]==(reverse?start[i]:finish[i]),"all role endpoint frames restored");
    unsigned comparisons=0,wrong_clear=0;for(unsigned basis=0;basis<n;++basis){std::array<unsigned char,n+1> value{};value[basis]=1;int source=-1;for(unsigned z=0;z<records.size();++z){const auto& r=records[reverse?records.size()-1-z:z];const int op=r[0],x=r[1],y=r[2];if(op==1)value[x]^=value[y];else if(op==(reverse?3:2)){need(value[n]==0,"COPY starts with its owned zero");source=x;value[n]=value[x];}else if(op==0){}else{need(source==x&&value[n]==value[x],"COPY logical cleanup on arbitrary original column");source=-1;value[n]=0;}}
        for(unsigned i=0;i<n;++i){const bool expected=(i==basis)||(i>=v&&i<2*v&&i-v==basis);need(value[i]==expected,"all661 arbitrary scalar input columns");++comparisons;}need(value[n]==0,"owned temporary clears on every column");if(basis>=2*v)++wrong_clear;}
    std::cout<<(reverse?"reverse":"forward")<<" arbitrary_columns="<<n<<" streamed_scalar_output_comparisons="<<comparisons<<" ADDs="<<adds<<" COPYs="<<copies<<" dirty_helper_columns="<<wrong_clear<<'\n';
}
void run(const std::string& dir){load_frames(dir);load_word(dir);geometry();transition_geometry();scalar(false);scalar(true);std::cout<<"PASS assertions="<<checks<<" exact rational8D frames,one scalar column at a time,27234 records; no full tensor,GL cover or dense661x661 matrix\n";}
}
int main(int argc,char** argv){if(!guard()){std::cerr<<"REFUSED self-only64MiB/10CPU guard\n";return 2;}try{need(argc==3&&std::string(argv[1])=="bounded","bounded marker and pinned source directory");pr589::run(argv[2]);return 0;}catch(const std::exception& e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
