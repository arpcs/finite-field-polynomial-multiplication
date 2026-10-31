// Bounded exact binary-polynomial Karatsuba. Caller installs job limits.
// Native fields here have d<=54 and modulus X^d+X^(d/2)+1.
struct BoundedRawProduct { U low=0,high=0; };
static BoundedRawProduct bounded_raw_xor(BoundedRawProduct a,BoundedRawProduct b) {
  return {a.low^b.low,a.high^b.high};
}
static BoundedRawProduct bounded_raw_shift(BoundedRawProduct a,unsigned shift) {
  if(!shift) return a;
  if(shift==64) return {0,a.low};
  return {a.low<<shift,(a.high<<shift)^(a.low>>(64-shift))};
}
static BoundedRawProduct bounded_karatsuba_raw(U a,U b,unsigned width) {
  if(width==1) return {a&b,0};
  unsigned half=width/2; U mask=(U(1)<<half)-1;
  U a0=a&mask,a1=a>>half,b0=b&mask,b1=b>>half;
  BoundedRawProduct low=bounded_karatsuba_raw(a0,b0,half);
  BoundedRawProduct high=bounded_karatsuba_raw(a1,b1,half);
  BoundedRawProduct middle=bounded_karatsuba_raw(a0^a1,b0^b1,half);
  middle=bounded_raw_xor(middle,bounded_raw_xor(low,high));
  return bounded_raw_xor(low,bounded_raw_xor(bounded_raw_shift(middle,half),bounded_raw_shift(high,2*half)));
}
static U bounded_karatsuba_field(U a,U b,unsigned degree) {
  check(2<=degree&&degree<=54&&degree%2==0,"bounded Karatsuba field degree");
  unsigned padded=1; while(padded<degree) padded*=2;
  BoundedRawProduct raw=bounded_karatsuba_raw(a,b,padded);
  auto bit=[&](unsigned i) { return ((i<64?raw.low:raw.high)>>(i%64))&1; };
  auto toggle=[&](unsigned i) { if(i<64) raw.low^=U(1)<<i; else raw.high^=U(1)<<(i-64); };
  for(unsigned i=2*degree-1;i>degree;--i) if(bit(i-1)) {
    toggle(i-1); toggle(i-1-degree); toggle(i-1-degree+degree/2);
  }
  check(raw.high==0&&(raw.low>>degree)==0,"bounded Karatsuba sparse reduction canonical");
  return raw.low;
}
