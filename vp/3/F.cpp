#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
vector<int> A, B;
char lx[N], s[N];
int a[N], b[N];
int pr[N][N];
int d[N][N], f[N][N], ma[N], pa[N], mb[N], pb[N];

void go(int la, int lb) {
  int pos = pr[la][lb];
  if(pos == 1) {
    go(la - 1, lb);
    A.push_back(a[la]);
    B.push_back(pa[a[la]]);
  } else if(pos == 2) {
    go(la, lb - 1);
    A.push_back(pb[b[lb]]);
    B.push_back(b[lb]);
  } else if(pos == 3) {
    go(la - 1, lb - 1);
    A.push_back(a[la]);
    B.push_back(b[lb]);
  }
}

int main() {
  freopen("dissim.in", "r", stdin);
  freopen("dissim.out", "w", stdout);
  scanf("%s", lx + 1);
  int len = strlen(lx + 1);
  scanf("%s", s + 1);
  a[0] = strlen(s + 1);
  for(int i = 1; i <= a[0]; ++i) {
    for(int j = 1; j <= len; ++j) {
      if(s[i] == lx[j]) a[i] = j;
    }
  }
  scanf("%s", s + 1);
  b[0] = strlen(s + 1);
  for(int i = 1; i <= b[0]; ++i) {
    for(int j = 1; j <= len; ++j) {
      if(s[i] == lx[j]) b[i] = j;
    }
  }
  memset(ma, 0x3f, sizeof ma);
  memset(mb, 0x3f, sizeof mb);
  for(int i = 1; i <= len; ++i)
    for(int j = 1; j <= len; ++j) {
      scanf("%d", &d[i][j]);
      if(d[i][j] < ma[i]) ma[i] = d[i][j], pa[i] = j;
      if(d[i][j] < mb[j]) mb[j] = d[i][j], pb[j] = i;
    }
  len = max(max(len, a[0]), b[0]);
  memset(f, 0x3f, sizeof f);
  f[0][0] = 0;
  for(int tot = 0; tot <= a[0] + b[0]; ++tot) {
    for(int i = max(tot - b[0], 0); i <= a[0]; ++i) {
      int j = tot - i;
      if(i + 1 <= a[0]) {
        int pos = f[i][j] + ma[a[i + 1]];
        if(f[i + 1][j] > pos) {
          f[i + 1][j] = pos;
          pr[i + 1][j] = 1;
        }
      }
      if(j + 1 <= b[0]) {
        int pos = f[i][j] + mb[b[j + 1]];
        if(f[i][j + 1] > pos) {
          f[i][j + 1] = pos;
          pr[i][j + 1] = 2;
        }
      }
      if(i + 1 <= a[0] && j + 1 <= b[0]) {
        int pos = f[i][j] + d[a[i + 1]][b[j + 1]];
        if(f[i + 1][j + 1] > pos) {
          f[i + 1][j + 1] = pos;
          pr[i + 1][j + 1] = 3;
        }
      }
    }
  }
  printf("%d\n", f[a[0]][b[0]]);
  go(a[0], b[0]);
  for(int i = 0; i < A.size(); ++i)
    printf("%c", lx[A[i]]);
  puts("");
  for(int i = 0; i < B.size(); ++i)
    printf("%c", lx[B[i]]);
  puts("");
  return 0;
}