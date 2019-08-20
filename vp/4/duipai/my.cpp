#include <bits/stdc++.h>
using namespace std;
const int N = 2010, M = 210, Mask = 110;
struct data {
  string s;
  int y, x;
  data() { s = ""; }
} a[N];
struct node {
  int k, t, ed, b, be;
} pr[M][Mask][6][6];
int all[N];
vector<string> g[M][6];
int f[M][Mask][6][6], cnt[Mask], nm[M][Mask];

void print(int now, int zt, int t, int ed) {
  if(!now) return ;
  node res = pr[now][zt][t][ed];
  print(now - 1, res.k, res.t, res.ed);
  if(res.b) {
    // printf("%d %d %d\n", now, res.be, ed);
    cout << g[now][ed][0] << endl;
    for(int i = 0; i < 5; ++i) {
      if(i != ed && (zt & (1 << i))) {
        for(int j = 0; j < g[now][i].size(); ++j)
          cout << g[now][i][j] << endl;
      }
    }
    for(int i = 1; i < g[now][ed].size(); ++i)
      cout << g[now][ed][i] << endl;
  } else {
    if(res.be != -1) 
      for(int i = 0; i < g[now][res.be].size(); ++i) {
        cout << g[now][res.be][i] << endl;
      }
    for(int i = 0; i < 5; ++i) {
      if(zt & (1 << i)) {
        if(i == ed || i == res.be) continue;
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
  // freopen("dvd.in", "r", stdin);
  // freopen("dvd.out", "w", stdout);
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
  }
  int tot = (1 << 5);
  for(int i = 1; i <= m; ++i)
    for(int j = 0; j < tot; ++j) {
      for(int k = 0; k < 5; ++k) {
        if(j & (1 << k)) 
          nm[i][j] += (int)g[i][k].size();
      }
    }
  for(int i = 0; i < tot; ++i)
    for(int j = 0; j < 5; ++j)
      if(i & (1 << j)) cnt[i]++;
  for(int i = 1; i <= m; ++i) 
    for(int k = 0; k < tot; ++k) 
      for(int t = 0; t <= 5; ++t) 
        for(int j = 0; j < 5; ++j) {
          //f[i - 1][k][t][j] last mask
          for(int z = 0; z < 5; ++z)
            for(int nk = 1; nk < tot; ++nk) {
              int tmp = f[i - 1][k][t][j] + nm[i][nk];
              if(nk == (1 << z)) {
                int pos = t + (z != j);
                if(pos > 5) continue;
                if(f[i][nk][pos][z] < tmp) {
                  f[i][nk][pos][z] = tmp;
                  pr[i][nk][pos][z] = (node) {k, t, j, 0, -1};
                }
              } else if(nk & (1 << z)) {
                for(int q = 0; q < 5; ++q) {
                  int pos = t + cnt[nk] - (z == j);
                  if(nk & (1 << q)) {
                    if(z == q) {
                      if(nm[i][z] >= 2 && pos + 1 <= 5) {
                        if(f[i][nk][pos + 1][q] < tmp) {
                          f[i][nk][pos + 1][q] = tmp;
                          pr[i][nk][pos + 1][q] = (node){k, t, j, 1, z};
                        }
                      }
                    } else if(pos <= 5){
                      if(f[i][nk][pos][q] < tmp) {
                        f[i][nk][pos][q] = tmp;
                        pr[i][nk][pos][q] = (node){k, t, j, 0, z};
                      }
                    }
                  }
                }
              }
            }
        }
  int ans = 0;
  for(int i = 0; i < tot; ++i)
    for(int j = 0; j <= 5; ++j)
      for(int k = 0; k < 5; ++k)
        Max(ans, f[m][i][j][k]);
  printf("%d\n", ans);
  // for(int i = 0; i < tot; ++i)
  //   for(int j = 0; j <= 5; ++j)
  //     for(int k = 0; k < 5; ++k) {
  //       if(ans == f[m][i][j][k]) {
  //         print(m, i, j, k);
  //         return 0;
  //       }
  //     }
  return 0;
}