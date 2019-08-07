
#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 5;
const int M = 4e3 + 5;
const int MOD = 998244353;

namespace {
  int ch[M][5], fac[5];
  int Add(int a, int b) { return (a += b) >= MOD? a - MOD : a; }
  void Upd(int &a, int b) { a = Add(a, b); }
  int Mul(int a, int b) { return (long long)a * b % MOD; }
  int Inv(int x) { return (x == 1)? 1 : Mul(MOD - MOD / x, Inv(MOD % x)); }
  void Math_init() {
    for (int i = 0; i < M; ++i) {
      ch[i][0] = 1;
      for (int j = 1; j <= min(i, 4); ++j) {
        ch[i][j] = Add(ch[i - 1][j - 1], ch[i - 1][j]);
      }
    }
    fac[0] = 1;
    for (int i = 1; i < 5; ++i) {
      fac[i] = Mul(fac[i - 1], i);
    }
  }
}

bool Chkmax(int &a, int b) {
  return (a < b)? (a = b, 1) : (0);
}

struct State {
  int dp[3][3]; // (last last bar, last bar)
  State() {
    memset(dp, -1, sizeof dp);
  }

  friend bool operator < (State a, State b) {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (a.dp[i][j] != b.dp[i][j])
          return a.dp[i][j] < b.dp[i][j];
    return 0;
  }

  friend State Max(State a, State b) {
    for (int i = 0; i < 3; ++i) 
      for (int j = 0; j < 3; ++j)
        a.dp[i][j] = max(a.dp[i][j], b.dp[i][j]);
    return a;
  }

  friend State Trans(State a, int b) {
    State c;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (~a.dp[i][j])
          for (int k = 0; k < 3 && i + j + k <= b; ++k)
            Chkmax(c.dp[j][k], min(i + a.dp[i][j] + (b - i - j - k) / 3, 4));
    return c;
  }

};

struct Mahjong {
  pair<State, State> god;
  int cnt;
  Mahjong() {
    memset(god.first.dp, -1, sizeof god.first.dp);
    memset(god.second.dp, -1, sizeof god.second.dp);
    god.first.dp[0][0] = cnt = 0;
  }

  friend bool operator < (Mahjong a, Mahjong b) {
    return a.cnt != b.cnt? a.cnt < b.cnt : a.god < b.god;
  }

  friend Mahjong Trans(Mahjong a, int b) {
    a.cnt = min(a.cnt + (b >= 2), 7);
    a.god.second = Trans(a.god.second, b);
    if (b >= 2) {
      a.god.second = Max(a.god.second, Trans(a.god.first, b - 2));
    }
    a.god.first = Trans(a.god.first, b);
    return a;
  }

  bool right() {
    if (cnt == 7) return 1;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (god.second.dp[i][j] == 4) return 1;
    return 0;
  }

} mahjong[M];

int n, tot;
map<Mahjong, int> idx;
bool win[M];
int org[N], f[N][M][4 * N], trans[M][5];

void Dfs_mahjong(Mahjong now) {
  if (idx.find(now) != idx.end()) return;
  mahjong[++tot] = now;
  win[tot] = now.right();
  idx[now] = tot;
  for (int i = 0; i <= 4; ++i) {
    Dfs_mahjong(Trans(now, i));
  }
}

int main() {
  Math_init();
  Dfs_mahjong(Mahjong());

  for (int i = 1; i <= tot; ++i) {
    for (int j = 0; j <= 4; ++j) {
      trans[i][j] = idx[Trans(mahjong[i], j)];
    }
  }

  scanf("%d", &n);
  for (int i = 0, x; i < 13; ++i) {
    scanf("%d%*d", &x);
    ++org[x];
  }

  f[0][1][0] = 1;
  for (int i = 0, cp = 0; i < n; ++i) { // consider 1 ... i
    cp += org[i + 1];
    for (int j = 1; j <= tot; ++j) { // mahjong j
      for (int l = org[i + 1]; l <= 4; ++l) { // trans
        int *nf = f[i + 1][trans[j][l]], *ff = f[i][j];
        int tmp = Mul(ch[4 - org[i + 1]][l - org[i + 1]], fac[l - org[i + 1]]);
        for (int k = 0; k + l <= 4 * n; ++k) { // have chosen k cards
          if (!ff[k]) continue;
          Upd(nf[k + l], Mul(ff[k], Mul(ch[k + l - cp][l - org[i + 1]], tmp)));
        }
      }
    }
  }

  int ans = 0, dw = 1;
  for (int i = 13; i <= 4 * n; ++i) {
    int up = 0;
    for (int j = 1; j <= tot; ++j) {
      if (!win[j]) Upd(up, f[n][j][i]);
    }
    Upd(ans, Mul(up, Inv(dw)));
    dw = Mul(dw, 4 * n - i);
  }
  printf("%d\n", ans);

  return 0;
}