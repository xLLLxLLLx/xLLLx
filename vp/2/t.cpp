#include <bits/stdc++.h>
#define rep(_i, _j) for(int _i = 1; _i <= _j; ++_i)
const int inf = 0x3f3f3f3f;
typedef long long LL;
typedef double DB;
using namespace std;

const int maxm = 20 + 2;
const int maxn = 400 + 20;
const int maxlen = 140 + 10;
struct big_num {
    int d[maxlen], len;
    big_num() {
        memset(d, 0, sizeof d);
        len = 1;
    }
    inline int & operator [] (int index) {
        return d[index];
    }
    friend big_num operator + (big_num lhs, big_num rhs) {
        big_num ret;
        ret.len = max(lhs.len, rhs.len);
        for(int i = 1; i <= ret.len; ++i) {
            ret[i] += lhs[i] + rhs[i];
            if(ret[i] > 9) {
                ret[i] %= 10, ret[i + 1] += 1;
            }
        }
        if(ret[ret.len + 1] > 0) ++ret.len;
        return ret;
    }
    friend big_num operator / (big_num lhs, int rhs) {
        big_num ret;
        int remain = 0;
        for(int i = lhs.len; 0 < i; --i) {
            remain = remain * 10 + lhs[i];
            if(remain >= rhs) {
                ret[i] = remain / rhs;
                remain %= rhs;
            }
        }
        for(ret.len = maxlen - 1; 1 < ret.len; --ret.len) {
            if(ret[ret.len] > 0) break;
        }
        return ret;
    }
    void print() {
        for(int i = len; 0 < i; --i)
            printf("%d", d[i]);
    }
};
big_num pow2[maxn], ans;

int n, m;
int cache[maxn], Hash[maxn];
int Ranma[maxm][maxm];

void right_shift() {
    for(register int i = 0, t; i < n; ++i) {
        t = Ranma[i][m - 1];
        for(int j = m - 1; 0 < j; --j) {
            Ranma[i][j] = Ranma[i][j - 1];
        }
        Ranma[i][0] = t;
    }
}
void down_shift() {
    for(register int i = 0, t; i < m; ++i) {
        t = Ranma[n - 1][i];
        for(int j = n - 1; 0 < j; --j) {
            Ranma[j][i] = Ranma[j - 1][i];
        }
        Ranma[0][i] = t;
    }
}
void rot() {
    int tmp[maxm][maxm];
    memcpy(tmp, Ranma, sizeof Ranma);
    for(int i = 0; i < m; ++i) {
        for(int j = n - 1; -1 < j; --j) {
            Ranma[i][n - 1 - j] = tmp[j][i];
        }
    }
    swap(n, m);
}

int calc() {
    int ret = 0;
    memset(Hash, 0, sizeof Hash);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cache[i * m + j] = Ranma[i][j];
        }
    }
    for(register int i = 0, uper = n * m, now; i < uper; ++i) {
        if(!Hash[i]) {
            ++ret;
            for(now = i; !Hash[now]; Hash[now] = 1, now = cache[now]);
        }
    }
    printf("res=%d\n", ret);
    return ret;
}
void print() {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            printf("%d ", Ranma[i][j]);
        }
        puts("");
    }
    puts("");
}
int main() {

    pow2[0].d[1] = 1;
    for(int i = 1; i < maxn; ++i)
        pow2[i] = pow2[i - 1] + pow2[i - 1];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            Ranma[i][j] = i * m + j;
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ans = ans + pow2[calc()];
            rot();
            if(n == m) ans = ans + pow2[calc()];
            rot();
            ans = ans + pow2[calc()];
            rot();
            if(n == m) ans = ans + pow2[calc()];
            rot();
            right_shift();
            ans.print();
            puts("");
        }
        down_shift();
    }
    ans.print();
    puts("");
    ans = ans / (n * m * 2 * (n == m ? 2 : 1));
    ans.print();
    puts("");

    return 0;
}