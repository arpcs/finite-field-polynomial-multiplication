// Frozen finite partition only: no discovery or growing operator/tensor.
// Install limits before any imported dynamically initialized finite table.
#include "../bounded_chirp_process_limits.hpp"
struct EarlyGuard {
  EarlyGuard() {
    if(!install_chirp_process_limits()) ExitProcess(2);
  }
};
static EarlyGuard required_before_imported_tables;
#define E8_ORTHOGONAL_TREE_SIDES_LIBRARY_ONLY
#include "../e8_orthogonal_tree_sides_bounded_20261030.cpp"
int main(){
  (void)&guard; // Imported guard is unused; EarlyGuard already installed ours.
  try{
    const auto geo=tree_sides::geometry();
    tree_sides::prepare(geo);
    const auto plan=tree_sides::make_plan(geo,true,tree_sides::frozen());
    std::array<unsigned,37> paid{},target{};
    std::array<std::array<unsigned,9>,9> hist{};
    paid[1]=45+1200;paid[2]=1200;paid[4]=1200;paid[7]=45+720;
    target[8]=5*unsigned(plan.size());target[22]=240;target[36]=240;
    for(const auto&r:plan){
      const unsigned a=tree_sides::pop(r.sm),b=tree_sides::pop(r.tm);
      check(a+b<=8,"orthogonal rectangle rank bound");
      ++hist[a][b];paid[a]+=5;paid[b]+=5;if(a+b<8)paid[8-a-b]+=5;
    }
    const std::array<unsigned,7> expect={27445,10400,2200,4340,7760,8120,765};
    for(unsigned j=0;j<7;++j)check(paid[j+1]==expect[j],"literal partial-bank paid profile");
    check(plan.size()==3782 && target[8]==18910,"frozen rectangle count");
    unsigned pm=0,tm=0;
    for(unsigned r=1;r<=36;++r){pm+=r*paid[r];tm+=r*target[r];}
    check(pm==165080&&tm==165200,"all finite rank masses");
    std::cout<<"{\"pass\":true,\"rectangle_count\":"<<plan.size()
      <<",\"paid_rank_mass\":"<<pm<<",\"target_rank_mass\":"<<tm
      <<",\"checks\":"<<checks<<",\"histogram\":[";
    bool comma=false;
    for(unsigned a=1;a<9;++a)for(unsigned b=1;b<9;++b)if(hist[a][b]){
      if(comma)std::cout<<',';
      comma=true;
      std::cout<<'['<<a<<','<<b<<','<<hist[a][b]<<']';
    }
    std::cout<<"],\"rectangles_sf_sn_tf_tn_sm_tm\":[";comma=false;
    for(const auto&r:plan){if(comma)std::cout<<',';comma=true;
      std::cout<<'['<<r.sf<<','<<r.sn<<','<<r.tf<<','<<r.tn<<','<<r.sm<<','<<r.tm<<']';}
    std::cout<<"],\"limits\":\"64MiB/10CPUSeconds;single-thread;fixed120roots;no_discovery\"}\n";
    return 0;
  }catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
