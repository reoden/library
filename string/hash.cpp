#include <random>

using namespace std;
using ULL = unsigned long long;
const int maxn = 1e6 + 5;
static const ULL mod = (1ull << 61) - 1;
ULL power[maxn];
mt19937_64 rnd(random_device{}());
uniform_int_distribution<ULL> dist(100, mod - 1);
const ULL base = dist(rnd);
 
static inline ULL add(ULL a, ULL b){
    a += b;
    if (a >= mod) a -= mod;
    return a;
}
 
static inline ULL mul(ULL a, ULL b){
    __uint128_t c = __uint128_t(a) * b;
    return add(c >> 61, c & mod);
}
 
ULL merge(ULL h1, ULL h2, int len2){
    return add(mul(h1, power[len2]), h2);
}
 
void init(){
    power[0] = 1;
    for(int i = 1; i < maxn; i++)
        power[i] = mul(power[i - 1], base);
}
 
ULL query(const vector<ULL> &s, int l, int r){
    return add(s[r], mod - mul(s[l - 1], power[r - l + 1]));
}
 
vector<ULL> build(const string &s){
    int sz = s.size();
    vector<ULL> hashed(sz + 1);
    for (int i = 0; i < sz; i++){
        hashed[i + 1] = add(mul(hashed[i], base), s[i]);
    }
    return hashed;
}
 
template <typename T>
vector<ULL> build(const vector<T> &s){
    int sz = s.size();
    vector<ULL> hashed(sz + 1);
    for (int i = 0; i < sz; i++){
        hashed[i + 1] = add(mul(hashed[i], base), s[i]);
    }
    return hashed;
}