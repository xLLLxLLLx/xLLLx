#include <iostream> 
#include <algorithm>  
#include <cstring>  
#include <map> 
using namespace std;
 
typedef long long ll;
const int maxn = 100001;
const int times = 10;
int prime[] = { 2, 3, 5, 7, 13, 17, 11, 61, 97, 24251, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 67, 71, 73, 79, 83, 89 };        //得到随机检验算子 a
map<ll, int>ump;
 
ll  Random(ll n) {
    return (double(rand()) / RAND_MAX * n + 0.5);
}
 
ll q_mul(ll a, ll b, ll mod) {
    ll ans = 0;
    while (b) {
        if (b & 1)    ans = (ans + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return ans;
    //    return (a*b)%mod;//超时就换成这个 
}
 
ll q_pow(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b & 1)    ans = q_mul(ans, a, mod);
        a = q_mul(a, a, mod);
        b >>= 1;
    }
    return ans;
}
 
bool miller_rabin(ll n) {                 //检验n是否是素数
    if (n<2) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;                //如果是2则是素数，如果<2或者是>2的偶数则不是素数
 
    ll k, j = 0, x, tem = n - 1;
    while (!(tem & 1)) tem >>= 1, j++;
    for (int i = 0; i<times; i++) {                //做times次随机检验
        if (prime[i] >= n) return true;
        x = q_pow(prime[i], tem, n);                //得到a^r mod n
        if (x == 1) continue;            //余数为1则为素数
        for (k = 0; k<j; k++) {
            if (x == n - 1) break;            //否则试验条件2看是否有满足的 j
            x = q_mul(x, x, n);
        }
        if (k == j) return false;
    }
    return true;
}
 
ll gcd(ll a, ll b) {
    if (a < 0) return gcd(-a, b);//加上这个能快些 
    return b ? gcd(b, a%b) : a;
}
 
ll pollard_rho(ll n, ll c) {//找到n的一个因子
    ll x, y, d, i = 1, k = 2;
    y = x = Random(n - 1) + 1;
    while (1) {
        i++;
        x = (q_mul(x, x, n) + c) % n;
        d = gcd(y - x, n);
        if (1<d&&d<n) return d;
        if (y == x) return n;//找到循环，选取失败，重新来
        if (i == k) {//似乎是一个优化，但是不是很清楚
            y = x;
            k <<= 1;
        }
    }
}
 
void factorization(ll n) {//分解 
    if (n == 1) return;        //此题特殊判断 
    if (miller_rabin(n)) {
        ump[n]++;
        return;
    }
    ll p = n;
    while (p >= n) p = pollard_rho(p, Random(n) + 1);
    factorization(p);
    factorization(n / p);
}
 
int main() {
    int T; cin >> T;
    ll x, ret;
    while (T--) {
        cin >> x;
        ret = 0x3f3f3f3f;
        ump.clear();
        factorization(x);
        for (map<ll, int>::iterator it = ump.begin(); it != ump.end(); it++) {
            ret = min(ret, (ll)it->second);
        }
        cout << ret << endl;
    }
    return 0;
}