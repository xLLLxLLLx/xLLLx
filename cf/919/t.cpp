//It is made by Awson on 2018.2.2
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N = 400000;
void read(int &x) {
    char ch; bool flag = 0;
    for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
    for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
    x *= 1-2*flag;
}
void print(int x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(int x) {if (x < 0) putchar('-'); print(Abs(x)); }

int S[N+5], C[N+5], cnt;
struct hs {
    int a[8];
    hs() {memset(a, 0, sizeof(a)); }
    hs(int x) {for (int i = 7; i >= 0; i--) a[i] = x%5, x /= 5; }
    hs(int *_a) {for (int i = 0; i < 8; i++) a[i] = _a[i]; }
    void rd() {for (int i = 0; i < 8; i++) read(a[i]); }
    void st() {sort(a, a+8); }
    int hash() {
        int ans = 0;
        for (int i = 0; i < 8; i++) ans = ans*5+a[i];
        return ans;
    }
};
struct tt {int to, next; }edge[(N<<6)+5];
int path[N+5], top, in[N+5], ans[N+5];

void add(int u, int v) { ++in[v]; edge[++top].to = v, edge[top].next = path[u]; path[u] = top; }
int no(int a, int b) {return (a-1)*cnt+b-1; }
void dfs(int cen, int last, int h) {
    if (cen == 8) {S[++cnt] = h, C[h] = cnt; return; }
    for (int i = last; i < 5; i++) dfs(cen+1, i, h*5+i);
}
void prework() {
    dfs(0, 0, 0);
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++) {
            hs a(S[i]), b(S[j]);
            for (int p = 0; p < 8; p++) if (a.a[p])
                for (int q = 0; q < 8; q++) if (b.a[q]) {
                    hs c(a.a);
                    c.a[p] = (a.a[p]+b.a[q])%5;
                    c.st(); int tmp = C[c.hash()];
                    //printf("%d %d %d\n",a.a[p],b.a[q],tmp);
                    add(no(j, tmp), no(i, j));
                }
        }
    queue<int>Q; while (!Q.empty()) Q.pop();
    for (int i = 2; i <= cnt; i++) ans[no(i, 1)] = 1, Q.push(no(i, 1));
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = path[u]; i; i = edge[i].next) if (!ans[edge[i].to]) {
            if (ans[u] == 1) {ans[edge[i].to] = -1; Q.push(edge[i].to); }
            else if (--in[edge[i].to] == 0) {
                Q.push(edge[i].to); ans[edge[i].to] = 1;
            }
        }
    }
 //   for(int i=1;i<=cnt*cnt;++i) printf("%d\n",ans[i]);
}
void work() {
    prework();
    int t, f; hs a, b; read(t);
    while (t--) {
        read(f); a.rd(), b.rd(); a.st(); b.st();
        if (f) swap(a, b);
        printf("%d %d %d\n",a.hash(),b.hash(),no(C[a.hash()], C[b.hash()]));
        int as = ans[no(C[a.hash()], C[b.hash()])];
        if (as == 0) puts("Deal");
        else if (as == -1 && f || as == 1 && !f) puts("Bob");
        else puts("Alice");
    }
}
int main() {
    work();
    return 0;
}