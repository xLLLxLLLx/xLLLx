#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
vector<int> g[N];
int opt[N], d[N];
vector<pair<int, int> > que[N];
char c[N], s[N];



void dfs(int now, int nowd) {
  nowd = AC::f(nowd, c[now]);
  treeArr::add(AC::dfn[nowd], 1);
  for(int i = 0; i < g[nowd].size(); ++i) 
    dfs(g[nowd][i], nowd);
  for(int i = 0; i < que[now].size(); ++i)
    ans[que[now][i].second] = AC::getans(que[now][i].fist);
  treeArr::add(AC::dfn[nowd], -1);
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", opt[i]);
    if(opt[i] == 2) {
      scanf("%d", &fa);
      g[fa].push_back(i);
    }
    scanf("%s", c + i);
  }
  return 0;
}