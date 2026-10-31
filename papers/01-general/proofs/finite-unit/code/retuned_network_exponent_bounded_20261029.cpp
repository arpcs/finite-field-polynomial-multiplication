// Exact, tiny parameter certificate. This does not certify the imported paper.
// Fixed h<=120, integers<=2048 bits, seven margins, no input-dependent search.
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <gmp.h>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <psapi.h>
#endif
class Z {
public:
    mpz_t v;
    Z(long x=0) { mpz_init_set_si(v,x); }
    Z(const Z& x) { mpz_init_set(v,x.v); }
    ~Z() { mpz_clear(v); }
    Z& operator=(const Z& x) { mpz_set(v,x.v); return *this; }
    friend Z operator+(const Z& a,const Z& b) { Z r; mpz_add(r.v,a.v,b.v); return r; }
    friend Z operator-(const Z& a,const Z& b) { Z r; mpz_sub(r.v,a.v,b.v); return r; }
    friend Z operator*(const Z& a,const Z& b) { Z r; mpz_mul(r.v,a.v,b.v); return r; }
    friend Z operator/(const Z& a,unsigned long b) { Z r; mpz_tdiv_q_ui(r.v,a.v,b); return r; }
    Z& operator*=(const Z& b) { mpz_mul(v,v,b.v); return *this; }
    friend bool operator<(const Z& a,const Z& b) { return mpz_cmp(a.v,b.v)<0; }
    friend bool operator>(const Z& a,const Z& b) { return b<a; }
    friend bool operator<=(const Z& a,const Z& b) { return !(b<a); }
    friend bool operator==(const Z& a,const Z& b) { return mpz_cmp(a.v,b.v)==0; }
    friend bool operator!=(const Z& a,const Z& b) { return !(a==b); }
    friend std::ostream& operator<<(std::ostream& o,const Z& z) {
        if(mpz_sizeinbase(z.v,2)>2048) throw std::runtime_error("print integer cap");
        std::array<char,640> s{};
        mpz_get_str(s.data(),10,z.v); return o<<s.data();
    }
};
class Q {
public:
    mpq_t v;
    Q(long n=0) { mpq_init(v); mpq_set_si(v,n,1); }
    Q(const Z& n,const Z& d) {
        mpq_init(v); mpq_set_num(v,n.v); mpq_set_den(v,d.v); mpq_canonicalize(v);
    }
    Q(const Q& x) { mpq_init(v); mpq_set(v,x.v); }
    ~Q() { mpq_clear(v); }
    Q& operator=(const Q& x) { mpq_set(v,x.v); return *this; }
    void bound() const {
        if(mpz_sizeinbase(mpq_numref(v),2)>2048 ||
           mpz_sizeinbase(mpq_denref(v),2)>2048)
            throw std::runtime_error("rational integer cap");
    }
    friend Q operator+(const Q& a,const Q& b) {
        Q r; mpq_add(r.v,a.v,b.v); r.bound(); return r;
    }
    friend Q operator-(const Q& a,const Q& b) {
        Q r; mpq_sub(r.v,a.v,b.v); r.bound(); return r;
    }
    friend Q operator*(const Q& a,const Q& b) {
        Q r; mpq_mul(r.v,a.v,b.v); r.bound(); return r;
    }
    friend Q operator/(const Q& a,const Q& b) {
        if(mpq_sgn(b.v)==0) throw std::runtime_error("zero denominator");
        Q r; mpq_div(r.v,a.v,b.v); r.bound(); return r;
    }
    friend bool operator<(const Q& a,const Q& b) { return mpq_cmp(a.v,b.v)<0; }
    friend bool operator>(const Q& a,const Q& b) { return b<a; }
    friend bool operator==(const Q& a,const Q& b) { return mpq_equal(a.v,b.v)!=0; }
    friend std::ostream& operator<<(std::ostream& o,const Q& q) {
        q.bound(); std::array<char,1280> s{};
        mpq_get_str(s.data(),10,q.v); return o<<s.data();
    }
};
static unsigned checks=0;
void need(bool b,const char* msg) {
    ++checks;
    if(!b) throw std::runtime_error(msg);
}
bool guard() {
#ifdef _WIN32
    HANDLE job=CreateJobObjectW(nullptr,nullptr);
    if(!job) return false;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info{};
    info.BasicLimitInformation.LimitFlags=
        JOB_OBJECT_LIMIT_PROCESS_MEMORY|JOB_OBJECT_LIMIT_PROCESS_TIME;
    info.ProcessMemoryLimit=64u*1024u*1024u;
    info.BasicLimitInformation.PerProcessUserTimeLimit.QuadPart=10ll*10000000ll;
    return SetInformationJobObject(job,JobObjectExtendedLimitInformation,&info,sizeof(info))
        &&AssignProcessToJobObject(job,GetCurrentProcess());
#else
    return false;
#endif
}
Z power(Z a,unsigned e) {
    need(e<=180,"power exponent cap");
    Z r=1;
    while(e--) {
        r*=a;
        need(mpz_sizeinbase(r.v,2)<=2048,"integer cap");
    }
    return r;
}
Q dy(unsigned e) { return Q(1,power(Z(2),e)); }
struct Network {
    unsigned h,nu;
    Z v,N,m,I,zb,zc,Wb,Wc,Lb,Lc,sb,sc;
    Q etab,etac;
    explicit Network(unsigned size):h(size) {
        need(39<=h && h<=120,"ground-size cap");
        v=Z(h)*(h-1)*(h-2)/6;
        N=v*v*v; m=Z(h)*h*h; I=3*v*v;
        zb=Z(3)*(h-3)*(h-4)/2;
        zc=Z(h-3)*(h-4)*(h-5)/6+3*(h-3);
        Wb=2*N+I*(v*zb+h);
        Wc=2*N+I*(v*zc+h+1);
        Lb=I*h*h; Lc=I*h*(h+1);
        sb=Wb*m-N+2*Lb;
        sc=Wc*m-2*N+2*Lc;
        need(sb<Wb*m && sc<Wc*m,"strict corrected rank deficits");
        need(2*Lb<N && 2*Lc<N,"both central-loss ratios below half");
        etab=Q(Wb*m-sb,Wb*m);
        etac=Q(Wc*m-sc,Wc*m);
        const Z E=64*power(Wc+m+1,3), B=sc+E;
        nu=1;
        while(power(m,nu)<B) {
            ++nu; need(nu<=17,"guard exponent implies C1=20");
        }
        need(nu+3<=20,"C1=20 retained");
    }
};
void certify(unsigned h,unsigned taue,unsigned sigmae,unsigned log_m_upper,
             unsigned kappa_e,std::ostream& out) {
    Network n(h);
    const Q A=dy(taue), Bs=dy(sigmae);
    const Q tau=1-A, sigma=1-Bs, beta(1,2), delta(1,16);
    const Q eps=Q(3,4)*A, c=Q(3,8)*A;
    const Q lam=1-A/8, lamp=1-A/16, kappa=dy(kappa_e);
    // ln(2)<7/10 follows from exp(7/10)>2 using its first four terms.
    const Q x(7,10);
    need(1+x+x*x/2+x*x*x/6>Q(2),"rational logarithm certificate");
    if(log_m_upper==14) {
        need(n.m<power(Z(2),20),"ln(m)<20 ln2<14");
    } else {
        need(log_m_upper==12 && n.m<power(Z(2),17),"ln(m)<17 ln2<12");
    }
    need(n.etab>Q(log_m_upper)*A,"bit exponent rank certificate");
    need(n.etac>Q(log_m_upper)*Bs,"complex exponent rank certificate");
    need(tau>0 && tau<1 && sigma>0 && sigma<1,"network exponent range");
    need(tau<lam && sigma<lam && lam<1,"lambda range");
    need(tau*(1+c/beta)<lam,"packed basis-change recurrence");
    need(lam<lamp && sigma+beta*(1-sigma)<lamp && lamp<1,"leaf/group recurrence");
    need(eps<Q(1,12) && eps*20<1,"dimension and exact guard widths");
    need(eps*(2-tau)<1-tau,"axis layout");
    need(Q(3,4)+delta+Q(3,2)*eps<1,"Gaussian line exponent");
    need(eps*(1+c)<1 && eps+delta<1,"other scans");
    std::array<Q,7> g{
        1-eps*(1+c),eps*c*(1-tau),eps*(1-lamp),
        1-tau-eps*(2-tau),Q(1,4)-delta-Q(3,2)*eps,
        1-delta-eps,eps
    };
    for(const auto& margin:g) need(margin>2*kappa,"all seven margins exceed 2 kappa");
    for(unsigned i=0;i<g.size();++i) if(i!=1)
        need(g[1]<g[i],"address row still bottleneck");
    need(g[1]==Q(9,32)*A*A*A,"exact routing margin");
    out<<"h="<<h<<", m="<<n.m<<", guard_nu="<<n.nu
       <<", tau=1-2^-"<<taue<<", sigma=1-2^-"<<sigmae
       <<", kappa=2^-"<<kappa_e<<"\n";
    out<<"v="<<n.v<<", N="<<n.N<<", invocations="<<n.I<<"\n";
    out<<"Wb="<<n.Wb<<"\nWc="<<n.Wc<<"\nsb="<<n.sb<<"\nsc="<<n.sc<<"\n";
    out<<"eta_b="<<n.etab<<"\neta_c="<<n.etac<<"\n";
    out<<"epsilon="<<eps<<", c="<<c<<", lambda="<<lam
       <<", lambda_prime="<<lamp<<"\n";
    for(unsigned i=0;i<g.size();++i) out<<"g"<<i+1<<"="<<g[i]<<"\n";
}
int main() {
    if(!guard()) { std::cerr<<"Required 64 MiB/10 CPU-second guard unavailable.\n"; return 2; }
    try {
        std::ofstream out("investigation/retuned_network_exponent_bounded_20261029.txt");
        need(bool(out),"report open");
        certify(100,40,42,14,123,out);
        certify(45,36,36,12,111,out);
        // This fixed-size scan checks only the corrected combinatorial counts.
        for(unsigned h=40;h<=80;++h) {
            Network n(h);
            need(n.m!=729,"nondegenerate rational ambient form");
        }
#ifdef _WIN32
        PROCESS_MEMORY_COUNTERS pmc{};
        need(GetProcessMemoryInfo(GetCurrentProcess(),&pmc,sizeof(pmc))!=0,"working-set query");
        out<<"peak_working_set_bytes="<<pmc.PeakWorkingSetSize<<"\n";
#endif
        out<<"assertions="<<checks<<"\n";
        out<<"Scope: exact finite counts and parameter inequalities only; imported "
              "network, tape, precision and numerical-recovery proofs require review.\n";
        std::cout<<"PASS: "<<checks<<" exact bounded assertions; report saved.\n";
        return 0;
    } catch(const std::exception& e) { std::cerr<<e.what()<<"\n"; return 1; }
}
