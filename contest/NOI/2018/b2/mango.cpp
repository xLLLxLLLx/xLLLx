/*program by mangoyang*/
#include<bits/stdc++.h>
#define inf (0x7f7f7f7f)
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
typedef long long ll;
using namespace std;
template <class T>
inline void read(T &x){
    int f = 0, ch = 0; x = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = 1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    if(f) x = -x;
}
#define int ll
#define fi first
#define se second
#define N (300005)
multiset<int> S;
int a[N], b[N], c[N], p[N], atk[N], n, m;
struct Node{ int x, m; } d[N];
namespace Crt{
    int Mod;
    inline int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
    inline int Mult(int a, int b){
        int ans = 0ll;
        for(; b; b >>= 1, a = (a + a) % Mod)
            if(b & 1) ans = (ans + a) % Mod;
        return ans;
    }   
    inline void exgcd(int a, int b, int &x, int &y){
        if(!b) return (void) (x = 1ll, y = 0ll);
        exgcd(b, a % b, y, x), y -= a / b * x;
    }
    inline pair<int, int> get_exgcd(int a, int b, int c){
        int g = gcd(a, b);
        if(c % g) return make_pair(-1ll, -1ll);
        int x, y; exgcd(a, b, x, y);
        x = (x + Mod) % Mod, y = (y + Mod) % Mod;
        x = Mult(x, c / g), y = Mult(y, c / g);
        return make_pair(x, y);
    }
    inline Node merge(Node A, Node B){
        if(A.x > B.x) swap(A, B);
        int g = gcd(A.m, B.m); Mod = A.m / g * B.m;
        pair<int, int> now = get_exgcd(A.m, B.m, B.x - A.x); 
        if(now.fi == -1) return (Node){-1ll, -1ll};
        return (Node){(A.x + Mult(A.m, now.fi)) % Mod, Mod};
    }
    inline Node solve(Node *A){
        if(n == 1) return A[1];
        Node now = merge(A[1], A[2]);
        for(int i = 3; i <= n; now = merge(now, A[i]), i++)
            if(now.x == -1 && now.m == -1) return now;
        return now;
    }
}
inline void init(){
    read(n), read(m);
    for(int i = 1; i <= n; i++) read(a[i]);
    for(int i = 1; i <= n; i++) read(p[i]);
    for(int i = 1; i <= n; i++) read(b[i]);
    for(int i = 1; i <= m; i++) read(c[i]);
}
inline void prepare(){
    S.clear();
    multiset<int>::iterator q;
    for(int i = 1; i <= m; i++) S.insert(c[i]); 
    for(int i = 1; i <= n; i++){
        q = S.upper_bound(a[i]);
        if(q != S.begin()) q--; 
        atk[i] = *(q), S.erase(q), S.insert(b[i]);
    }
}
inline void solve(){ 
    init(), prepare();
    for(int i = 1; i <= n; i++){
        Crt::Mod = p[i];
        pair<int, int> now = Crt::get_exgcd(atk[i], p[i], a[i]);
        if(now.fi == -1) return (void) puts("-1");
        d[i] = (Node){now.fi, p[i] / Crt::gcd(atk[i], p[i])};
    }
    Node res = Crt::solve(d);
    if(res.x == -1 && res.m == -1) return (void) puts("-1");
    int x = res.x, m = res.m; x %= m;
    for(int i = 1; i <= n; i++){
        int ned = a[i] % atk[i] == 0 ? a[i] / atk[i] : a[i] / atk[i] + 1;
        if(x < ned){
            int tmp = ned - x;
            if(tmp % m == 0) x += tmp / m; else x += tmp / m + 1;
        }
    }
    printf("%lld\n", x);    
}
main(){
    int T; read(T); while(T--) solve();
    return 0;
}