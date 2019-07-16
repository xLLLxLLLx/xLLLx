#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
 
const int N = 601000;
 
int n, m, x, y, f[N], from[N], b[N], tot, q[N], st[N], deg[N], vis[N];
vector<int> g[N];
pair<int, int> e[N << 1];
 
void Print(int x) {
  if(!x) return;
  Print(from[x]);
  printf("%d ", x);
}
 
int main(void) {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
    deg[x]++; deg[y]++;
    if(x == 1 || y == 1) continue;
    e[++tot] = make_pair(x, y);
    e[++tot] = make_pair(y, x);
  }
 
  queue<int> Q;
  Q.push(1);
  memset(f, 0x3f, sizeof(f));
  f[1] = 0;
  while(!Q.empty()) {
    int x = Q.front(); Q.pop();
    for(int i = 0; i < g[x].size(); i++) {
      int v = g[x][i];
      if(f[v] > f[x] + 1) {
      	f[v] = f[x] + 1;
      	from[v] = x;
      	Q.push(v);
      }
    }
  }
  if(f[n] <= 4) { printf("%d\n", f[n]); Print(n); return 0; }
  for(int i = 0; i < g[1].size(); i++)
    b[g[1][i]] = 1;
  for(int i = 1; i <= tot; i++) {
    if(b[e[i].F] && !b[e[i].S]) {
      printf("4\n%d %d %d %d %d\n", 1, e[i].F, e[i].S, 1, n);
      return 0;
    }
  }
  for(int i = 0; i < g[1].size(); i++) {
    if(vis[g[1][i]]) continue;
    long long E = 0;
    int V = 0, h = 1, t = 0;
    q[++t] = g[1][i];
    vis[q[1]] = 1;
    while(h <= t) {
      int x = q[h++];
      E += deg[x] - 1; V++;
      for(int j = 0; j < g[x].size(); j++) {
      	int v = g[x][j];
      	if(!vis[v] && v != 1)
      	  q[++t] = v, vis[v] = 1;
      }
    }
    if(t < 3 || 1LL * V * (V - 1) == E) continue;
    for(int j = 1; j <= t; j++)
      if(deg[q[j]] <= V) {
      	int x = q[j];
      	memset(vis, 0, sizeof(vis));
      	for(int k = 0; k < g[x].size(); k++)
      	  vis[g[x][k]] = 1;
      	for(int k = 0; k < g[x].size(); k++) {
      	  int v = g[x][k];
      	  if(v == 1) continue;
      	  for(int l = 0; l < g[v].size(); l++)
      	    if(!vis[g[v][l]] && g[v][l] != q[j] && g[v][l] != 1) {
      	      printf("5\n%d %d %d %d %d %d", 1, q[j], v, g[v][l], q[j], n);
      	      return 0;
      	    }
        }
      }
  }
  puts("-1");
  return 0;
}