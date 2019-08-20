#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int N = 66;
stack<int> g[N];
int pr[N][N], vs[N];
ll f[N][N];

void init() {
  memset(f, 0x3f, sizeof f);
  for(int i = 1; i < N; ++i) {
    f[0][i] = 0;
    f[1][i] = 1;
  }
  for(int i = 2; i < N; ++i) {
    f[i][3] = f[i - 1][3] * 2 + 1;
    pr[i][3] = i - 1;
  }
  for(int i = 2; i < N; ++i) {
    for(int j = 4; j < N; ++j) {
      for(int k = 1; k < i; ++k) {
        if(f[i][j] > f[k][j] * 2 + f[i - k][j - 1]) {
          f[i][j] = f[k][j] * 2 + f[i - k][j - 1];
          pr[i][j] = k;
        }
      }
    }
  }
}

int qn, qm;

void go(int n, int m, int be, int ed) {
  if(n == 1) {
    if(g[ed].size()) {
      printf("move %d from %d to %d atop %d\n", g[be].top(), be, ed, g[ed].top());
    } else {
      printf("move %d from %d to %d\n", g[be].top(), be, ed);
    }
    g[ed].push(g[be].top());
    g[be].pop();
    vs[be] = 0;
    return ;
  }
  int mid = 0;
  for(int i = 1; i <= qm; ++i) {
    if(i != be && i != ed && !vs[i]) {
      mid = i;
      break;
    }
  }
  go(pr[n][m], m, be, mid);
  vs[mid] = 1;
  go(n - pr[n][m], m - 1, be, ed);
  vs[mid] = 0;
  go(pr[n][m], m, mid, ed); 
}

int main() {
  freopen("hanoi.in", "r", stdin);
  freopen("hanoi.out", "w", stdout);
  init();
  scanf("%d%d", &qn, &qm);
  printf("%u\n", f[qn][qm]);
  for(int i = qn; i >= 1; --i)
    g[1].push(i);
  go(qn, qm, 1, qm);
  return 0;
}