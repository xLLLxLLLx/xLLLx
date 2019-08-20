#include <bits/stdc++.h>
using namespace std;
const int N = 2010, M = 140, Mask = 40;
struct data {
  string s;
  int y, x;
  data() { s = ""; }
} a[N];
struct node {
  int k, ed, st, is;
} pr[M][6][6];
int all[N], qx[M];
bool mk[M][6];
vector<string> g[M][6];
int f[M][6][6], cnt[Mask], nm[M][Mask];

void print(int now, int zt, int ed) {
  if(!now) return ;
  node res = pr[now][zt][ed];
  print(now - 1, res.k, res.st, res.ed);
  // printf("%d %d %d %d\n", now, zt, st, ed);
  for(int i = 0; i < g[now][st].size(); ++i)
    cout << g[now][st][i] << endl;
  if(st != ed) {
    for(int i = 0; i < 5; ++i) {
      if(mk[now][i] && i != st && i != ed) {
        for(int j = 0; j < g[now][i].size(); ++j)
          cout << g[now][i][j] << endl;
      }
    }
    for(int i = 0; i < g[now][ed].size(); ++i)
      cout << g[now][ed][i] << endl;
  }
}

void Max(int &x, int y) {
  x = max(x, y);
}

string lx;

int main() {
  freopen("dvd.in", "r", stdin);
  freopen("dvd.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    for(;;) {
      cin >> lx;
      a[i].s += lx;
      if(lx[lx.length() - 1] == '"') break;
      a[i].s += " ";
    }
    scanf("%d%d", &a[i].y, &a[i].x);
    a[i].x--;
    all[i] = a[i].y;
  }
  // for(int i = 1; i <= n; ++i)
  //   cout<<a[i].s<<endl;
  sort(all + 1, all + 1 + n);
  int m = unique(all + 1, all + 1 + n) - all - 1;
  for(int i = 1; i <= n; ++i) {
    a[i].y = lower_bound(all + 1, all + 1 + m, a[i].y) - all;
    g[a[i].y][a[i].x].push_back(a[i].s);
    if(!mk[a[i].y][a[i].x]) {
      qx[a[i].y]++;
      mk[a[i].y][a[i].x] = 1;
    }
  }
  int tot = (1 << 5);
  for(int i = 1; i <= m; ++i)
    for(int j = 0; j < tot; ++j) {
      for(int k = 0; k < 5; ++k) {
        if(j & (1 << k)) {
          nm[i][j] += (int)g[i][k].size();
        }
      }
    }
  for(int i = 0; i < tot; ++i)
    for(int j = 0; j < 5; ++j)
      if(i & (1 << j)) cnt[i]++;
  for(int i = 1; i <= m; ++i) 
    for(int k = 0; k <= 5; ++k) 
      for(int j = 0; j < 5; ++j) {
        //f[i - 1][k][t][j] last mask
        for(int z = 0; z < 5; ++z)
          for(int q = 0; q < 5; ++q) {
            if(z == q) {
              int pos = k + (j != z);
              if(pos <= 5) {
                if(f[i][pos][q] < f[i - 1][k][j] + nm[i][(1 << z)]) {
                  f[i][pos][q] = f[i - 1][k][j] + nm[i][(1 << z)];
                  pr[i][pos][q] = (node){k, j, 1};
                }
              }
            } else {
              if(mk[i][z] && mk[i][q]) {
                int pos = k + qx[i] - (j == z);
                if(pos <= 5) {
                  if(f[i][pos][q] < f[i - 1][k][j] + nm[i][tot - 1]) {
                    f[i][pos][q] = f[i - 1][k][j] + nm[i][tot - 1];
                    pr[i][pos][q] = (node){k, j, 0};
                  }
                }
              }
            }
          }
        }
  int ans = 0;
  for(int i = 0; i <= 5; ++i)
    for(int j = 0; j < 5; ++j)
      for(int k = 0; k < 5; ++k)
        Max(ans, f[m][i][j][k]);
  printf("%d\n", ans);
  for(int i = 0; i <= 5; ++i)
    for(int j = 0; j < 5; ++j)
      for(int k = 0; k < 5; ++k) {
        if(ans == f[m][i][j][k]) {
          print(m, i, j, k);
          // for(int o = 1; o <= B[0]; ++o)
          //   printf("%d", B[o]);
          return 0;
        }
      }
  return 0;
}
