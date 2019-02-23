#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
const int MAXN = 1e4 + 10;

inline LL in()
{
    LL x = 0, flag = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') flag = -1; ch = getchar(); }
    while (ch >='0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return x * flag;
}

int n, xx, yy;

int a[4][MAXN], b[4][MAXN];
int state[MAXN];
LL f[MAXN][10], ans;

bool valid(int a, int b) {return (a & b) == b && (a | b) == a;}
bool check(int now, int nex)
{
    for (int i = 0; i <= 2; i ++)
        if (nex & (1 << i))
        {
            if (now & (1 << i)) return false;
            else now |= (1 << i);
        }
    return now == 7 || now == 1 || now == 4;
}
void print_bit(int x)
{
    for (int i = 3; i >= 0; i --) if (x & (1 << i)) printf("1"); else printf("0");
    printf(" ");
}
LL solve()
{
    memset(state, 0, sizeof state);
    for (int i = 1; i <= n; i ++)
        for (int j = 0; j <= 2; j ++)
            state[i] |= (b[j][i] << j);
    memset(f, 0, sizeof f);
    f[1][state[1]] = 1;
    for (int i = 1; i <= n; i ++)
    {
        for (int now = 0; now < 8; now ++)
        {
            if (!valid(now, state[i])) continue;
            if (f[i][now] == 0) continue;
            for (int nex = 0; nex < 8; nex ++)
            {
                if (nex & state[i + 1]) continue;
                if (!check(now, nex)) continue;
                int rnex = nex | state[i + 1];
//                printf("i : %d now : %d,%lld  nex : %d,%lld ", i, now, f[i][now], rnex, f[i + 1][rnex]);
                (f[i + 1][rnex] += f[i][now]) %= MOD;
//                printf("--> %lld\n", f[i + 1][rnex]);
            }
        }
    }
	printf("%lld\n",f[n+1][0]);
    return f[n + 1][0];
}
void rst()
{
    for (int i = 0; i <= 2; i ++)
        for (int j = 1; j <= n; j ++)
            b[i][j] = a[i][j];
}
bool jd(int opt, int x, int y)
{
    if (opt == 0) return x == 2     && b[0][y]     == 0 && b[1][y]     == 0;
    if (opt == 1) return x == 0     && b[2][y]     == 0 && b[1][y]     == 0;
    if (opt == 2) return y >= 3     && b[x][y - 2] == 0 && b[x][y - 1] == 0;
    if (opt == 3) return y <= n - 2 && b[x][y + 1] == 0 && b[x][y + 2] == 0;
}
void cv(int opt, int x, int y)
{
    if (opt == 0) b[0][y]     = b[1][y]     = 1;
    if (opt == 1) b[1][y]     = b[2][y]     = 1;
    if (opt == 2) b[x][y - 2] = b[x][y - 1] = 1;
    if (opt == 3) b[x][y + 1] = b[x][y + 2] = 1;
}
/*
attention !!!
0 : up
1 : down
2 : left
3 : right
 */
void print()
{
    for (int i = 0; i <= 2; i ++, printf("\n"))
        for (int j = 1; j <= n; printf("%d ", b[i][j]), j ++);
}
void irritable(int x, int y)
{
    for (int i = 1; i < 16; i ++)
    {
        int cnt = 0;
        rst();
        bool flag = true;
        for (int j = 0; j <= 3; j ++)
            if (i & (1 << j))
            {
                if (!jd(j, x, y)) {flag = false; break;}
                cnt ++;
                cv(j, x, y);
            }
        if (!flag) continue;
//        printf("%d %d\n", i, cnt);
//        puts("##### MAP : #####");
//        print();
        if (cnt & 1) (ans += solve()) %= MOD;
        else (ans += MOD - solve()) %= MOD;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i <= 2; i ++)
    {
        for (int j = 1; j <= n; j ++)
        {
            char ch = getchar();
            while (ch != '.' && ch != 'X' && ch != 'O') ch = getchar();
            if (ch == '.') a[i][j] = 0;
            else if (ch == 'X') a[i][j] = 1;
            else if (ch == 'O') a[i][j] = 1, xx = i, yy = j;
        }
    }
    irritable(xx, yy);
    cout << ans;
    return 0;
}
/*
0*
10
10
 */

