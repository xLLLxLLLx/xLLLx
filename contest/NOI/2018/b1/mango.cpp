#include <bits/stdc++.h>
#define inf (0x7f7f7f7f)
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
typedef long long ll;
using namespace std;
template <class T>
inline void read(T &x){
    int ch = 0, f = 0; x = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = 1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    if(f) x = -x;
}
const int N = 2000005;
char s[N];
int res[N], n, q;
namespace Seg{
    #define mid ((l + r) >> 1)
    int lc[N*25], rc[N*25], sz[N*25], size;
    inline void ins(int &u, int l, int r, int pos){
        if(!u) u = ++size;
        if(l == r) return (void) (sz[u]++);
        if(pos <= mid) ins(lc[u], l, mid, pos);
        else ins(rc[u], mid + 1, r, pos); 
        sz[u] = sz[lc[u]] + sz[rc[u]];
    }
    inline int merge(int x, int y, int l, int r){
        if(!x || !y) return x + y;
        int o = ++size;
        if(l == r) sz[o] = sz[x] + sz[y];
        else{
            lc[o] = merge(lc[x], lc[y], l, mid);
            rc[o] = merge(rc[x], rc[y], mid + 1, r);
            sz[o] = sz[lc[o]] + sz[rc[o]];
        }
        return o;
    }
    inline int query(int u, int l, int r, int L, int R){
        if(l >= L && r <= R) return sz[u];
        int res = 0;
        if(L <= mid) res += query(lc[u], l, mid, L, R);
        if(mid < R) res += query(rc[u], mid + 1, r, L, R);
        return res;
    }
    #undef mid
}
vector<int> vec[N];
namespace SAM1{
    vector<int> g[N];
    int ch[N][26], rt[N], fa[N], len[N], size = 1, tail = 1;
    inline int newnode(int x){ return len[++size] = x, size; }
    inline void ins(int c, int x){
        int p = tail, np = newnode(len[p] + 1);
        Seg::ins(rt[np], 1, n, x);
        for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if(!p) return (void) (fa[np] = 1, tail = np);
        int q = ch[p][c];
        if(len[q] == len[p] + 1) fa[np] = q;
        else{
            int nq = newnode(len[p] + 1);           
            fa[nq] = fa[q], fa[q] = fa[np] = nq;
            for(int i = 0; i < 26; i++) ch[nq][i] = ch[q][i];
            for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }tail = np;
    }
    inline void addedge(){
        for(int i = 2; i <= size; i++) g[fa[i]].push_back(i);
    }
    inline void dfs(int u){
        for(int i = 0; i < (int) g[u].size(); i++)
            dfs(g[u][i]), rt[u] = Seg::merge(rt[u], rt[g[u][i]], 1, n);
        // for(int i = 1; i <= size; ++i)
        //     printf("%d %d\n", i, rt[i]);
    }
    inline void solve(char *s, int L, int R){
        int lenth = strlen(s + 1);
        for(int i = 1, p = 1, now = 0; i <= lenth; i++) {
            int c = s[i] - 'a';
            while(!ch[p][c] && p) p = fa[p], now = len[p];
            if(!p){ p = 1, now = 0; continue; };
            p = ch[p][c], now++;
            while(p > 1){
                if(Seg::query(rt[p], 1, n, L + now - 1, R)) break;
                if(--now == len[fa[p]]) p = fa[p];
            }
            if(p == 1) continue;
            printf("%d %d %d\n", i, p, now);
            for(int j = 0; j < (int) vec[i].size(); j++) {
                // printf("qwq%d\n", vec[i][j]);
                res[vec[i][j]] = max(res[vec[i][j]], now);
            }
        }
        // puts("hello");
        // for(int i = 1; i <= lenth; ++i)
        //     printf("%d %d\n", i, res[i]);
    }
}
namespace SAM2{
    int fa[N], len[N], ch[N][26], size, tail;
    inline void Clear(){
        for(int i = 1; i <= size; i++){
            fa[i] = len[i] = res[i] = 0;
            memset(ch[i], 0, sizeof(ch[i]));
        }
        size = tail = 1;
    }
    inline int newnode(int x){ return len[++size] = x, size; }
    inline void ins(int c, int x){
        int p = tail, np = newnode(len[p] + 1);
        vec[x].push_back(np);
        for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if(!p) return (void) (fa[np] = 1, tail = np);
        int q = ch[p][c];
        if(len[q] == len[p] + 1) fa[np] = q;
        else{
            int nq = newnode(len[p] + 1);           
            vec[x].push_back(nq);
            fa[nq] = fa[q], fa[q] = fa[np] = nq;
            for(int i = 0; i < 26; i++) ch[nq][i] = ch[q][i];
            for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }tail = np;
    }
    inline ll solve(){
        ll ans1 = 0, ans2 = 0;
        for(int i = 1; i <= size; i++){
            printf("%d %d\n", i, res[i]);
            if(res[i] > len[fa[i]])
                ans2 += 1ll * min(res[i], len[i]) - len[fa[i]];
            ans1 += 1ll * len[i] - len[fa[i]];
        }
        return ans1 - ans2;
    }
}
int main(){
    scanf("%s", s + 1), n = strlen(s + 1);
    for(int i = 1; i <= n; i++) SAM1::ins(s[i] - 'a', i);
    SAM1::addedge(), SAM1::dfs(1);  
    // for(int i = 1; i <= n; ++i)
    //     printf("%d %d\n", i, Seg::sz[i]);
    read(q); int L, R;
    while(q--){
        scanf("%s", s + 1); int m = strlen(s + 1);
        read(L), read(R);
        for(int i = 1; i <= m; i++) vec[i].clear();
        SAM2::Clear();
        for(int i = 1; i <= m; i++) SAM2::ins(s[i] - 'a', i);
        SAM1::solve(s, L, R);
        printf("%lld\n", SAM2::solve());
    }
    return 0;
}