#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1e4 + 5;
const int M = 1e5 + 5;
const int Lg = 25;

int n, m, qn, tot, head[2][N << 1], top, sta[N];
int dfsc, dfn[N], low[N], dccCnt, root;
int bel[N], eb[M], fa[N << 1][Lg], dep[N << 1], id[N];
bool cut[N], vis[N << 1];
vector <int> dcc[N];

struct Edge {
    int to, nxt, id;
} e[M << 2];

inline void add(int type, int from, int to, int eid) {
    e[++tot].to = to;
    e[tot].id = eid;
    e[tot].nxt = head[type][from];
    head[type][from] = tot;
}

inline void read(int &X) {
    X = 0;
    char ch = 0;
    int op = 1;
    for(; ch > '9'|| ch < '0'; ch = getchar())
        if(ch == '-') op = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        X = (X << 3) + (X << 1) + ch - 48;
    X *= op;
}

inline int min(int x, int y) {
    return x > y ? y : x;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++dfsc;
    sta[++top] = x;
    if(x == root && head[0][x] == 0) {
        dcc[++dccCnt].push_back(x);
        return;
    }
    
    int son = 0;
    for(int i = head[0][x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if(dfn[x] <= low[y]) {
                ++son;
                if(x != root || son > 1) cut[x] = 1;
                ++dccCnt;
                for(int z; ; ) {
                    z = sta[top--];
                    dcc[dccCnt].push_back(z);
                    if(z == y) break;
                }
                dcc[dccCnt].push_back(x);
            }
        } else low[x] = min(low[x], dfn[y]);
    }
}

int main() {
    for(; ; ) {
        read(n), read(m);
        if(n == 0 && m == 0) break;
        tot = 0;
        memset(head, 0, sizeof(head));
        for(int x, y, i = 1; i <= m; i++) {
            read(x), read(y);
            add(0, x, y, i), add(0, y, x, i);
        } 
        
        dfsc = dccCnt = top = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(cut, 0, sizeof(cut));
        for(int i = 1; i <= n; i++) dcc[i].clear();
        
        for(int i = 1; i <= n; i++)
            if(!dfn[i]) tarjan(root = i);
        
        int now = dccCnt;
        for(int i = 1; i <= n; i++)
            if(cut[i]) id[i] = ++now;
        for(int i = 1; i <= dccCnt; i++) {
            for(unsigned int j = 0; j < dcc[i].size(); j++) {
                int x = dcc[i][j];
                if(cut[x]) add(1, id[x], i, 0), add(1, i, id[x], 0);
                bel[x] = i;
            }
            
            for(unsigned int j = 0; j < dcc[i].size(); j++) {
                int x = dcc[i][j];
                for(int k = head[0][x]; k; k = e[k].nxt) {
                    int y = e[k].to;
                    if(bel[y] == i) eb[e[k].id] = i;
                }
            }
        }
        memset(dep, 0, sizeof(dep));
        memset(fa, 0, sizeof(fa));
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= now; i++)
            if(!vis[i]) dfs(i, 0, 1);
        
        read(qn);
        for(int x, y; qn--; ) {
            read(x), read(y);
            x = eb[x], y = eb[y];
            if(x == y) puts("0");
            else printf("%d\n", (dep[x] + dep[y] - 2 * dep[getLca(x, y)]) / 2); 
        }
    }
    return 0;
}