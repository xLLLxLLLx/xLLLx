#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <stack>
#include <queue>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#define fuck(x) cout<<"["<<x<<"]";
#define FIN freopen("input.txt","r",stdin);
#define FOUT freopen("output.txt","w+",stdout);
using namespace std;
typedef long long LL;
typedef pair<int, int>PII;
 
const int MX = 1e5 + 5;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
 
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
 
const int matX = 2;
struct Matrix {
    int n, m, s[matX][matX];
    Matrix() {}
    void init(int _n, int _m) {
        n = _n; m = _m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) s[i][j] = 0;
        }
    }
    Matrix(int n, int m): n(n), m(n) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) s[i][j] = 0;
        }
    }
    Matrix operator*(const Matrix &P)const {
        Matrix ret(n, P.m);
        for(int i = 0; i < n; i++) {
            for(int k = 0; k < m; k++) {
                if(s[i][k]) {
                    for(int j = 0; j < P.m; j++) {
                        ret.s[i][j] = ((LL)s[i][k] * P.s[k][j] + ret.s[i][j]) % mod;
                    }
                }
            }
        }
        return ret;
    }
    Matrix operator^(const LL &P)const {
        LL num = P;
        Matrix ret(n, m), tmp = *this;
        for(int i = 0; i < n; i++) ret.s[i][i] = 1;
        while(num) {
            if(num & 1) ret = ret * tmp;
            tmp = tmp * tmp;
            num >>= 1;
        }
        return ret;
    }
};
 
 
int sum[MX << 2][2];
Matrix lazy[MX << 2];
bool col[MX << 2];
 
void push_up(int rt) {
    sum[rt][0] = (sum[rt << 1][0] + sum[rt << 1 | 1][0]) % mod;
    sum[rt][1] = (sum[rt << 1][1] + sum[rt << 1 | 1][1]) % mod;
}
void build(int l, int r, int rt) {
    if(l == r) {
        sum[rt][0] = 1;
        sum[rt][1] = 0;
        return;
    }
    col[rt] = 0;
    int m = (l + r) >> 1;
    build(lson); build(rson);
    push_up(rt);
}
void updone(int rt, Matrix x) {
    if(col[rt] == 0) {
        lazy[rt] = x;
        col[rt] = 1;
    } else lazy[rt] = lazy[rt] * x;
 
    Matrix B(2, 2);
    B.s[0][0] = sum[rt][0];
    B.s[1][0] = sum[rt][1];
    B = x * B;
    sum[rt][0] = B.s[0][0];
    sum[rt][1] = B.s[1][0];
}
void push_down(int rt) {
    if(col[rt]) {
        updone(rt << 1, lazy[rt]);
        updone(rt << 1 | 1, lazy[rt]);
        col[rt] = 0;
    }
}
void update(int L, int R, Matrix x, int l, int r, int rt) {
    if(L <= l && r <= R) {
        updone(rt, x);
        return;
    }
    int m = (l + r) >> 1;
    push_down(rt);
    if(L <= m) update(L, R, x, lson);
    if(R > m) update(L, R, x, rson);
    push_up(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) {
        return sum[rt][1];
    }
    int m = (l + r) >> 1;
    push_down(rt); int ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(R > m) ret += query(L, R, rson);
    return ret % mod;
}
 
int n, m;
int main() {
    // FIN;
    Matrix A(2, 2);
    A.s[0][0] = 1; A.s[0][1] = 1;
    A.s[1][0] = 1; A.s[1][1] = 0;
 
    scanf("%d%d", &n, &m);
    build(1, n, 1);
    for(int i = 1; i <= n; i++) {
        int t; scanf("%d", &t);
        Matrix B = A ^ t;
        update(i, i, B, 1, n, 1);
    }
    for(int i = 1; i <= m; i++) {
        int a, b, c, d;
        scanf("%d%d%d", &a, &b, &c);
        if(a == 1) {
            scanf("%d", &d);
            Matrix B = A ^ d;
            update(b, c, B, 1, n, 1);
        } else printf("%d\n", query(b, c, 1, n, 1));
    }
    return 0;
}
