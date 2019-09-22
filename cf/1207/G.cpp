#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
char lx[N];
typedef pair<int, int> pii;
vector<pii> a[N], b[N];
vector<int> g[N];
int res = 0, cnt = 0;
int ch[N][30], fail[N], st[N], ed[N], d[N], tr[N];

int lower(int x) {
  return x & (-x);
}

void add(int x, int k) {
  for(; x < N; x += lower(x))
    tr[x] += k;
}

int get(int x) {
  int ans = 0;
  for(; x; x -= lower(x))
    ans += tr[x];
  return ans;
}

int insert() {
  int fa = 0, len = strlen(lx + 1);
  for(int i = 1; i <= len; ++i) {
    int pos = lx[i] - 'a';
    if(!ch[fa][pos]) ch[fa][pos] = ++cnt;
    fa = ch[fa][pos];
  }
  return fa;
}

queue<int> q;
void build() {
  for(int i = 0; i < 26; ++i) 
    if(ch[0][i]) q.push(ch[0][i]);
  while(!q.empty()) {
    int h = q.front(); q.pop();
    for(int i = 0; i < 26; ++i) {
      if(ch[h][i]) {
        fail[ch[h][i]] = ch[fail[h]][i];
        q.push(ch[h][i]);
      } else {
        ch[h][i] = ch[fail[h]][i];
      }
    }
  }
  for(int i = 1; i <= cnt; ++i) {
    // printf("%d %d\n", i, fail[i]);
    g[fail[i]].push_back(i);
  }
}

void predfs(int x) {
  st[x] = ++res;
  for(int i = 0; i < (int)g[x].size(); ++i)
    predfs(g[x][i]);
  ed[x] = res;
}

void dfs(int u, int id) {
  add(st[u], 1);
  for(int i = 0; i < (int)b[id].size(); ++i) {
    pii pos = b[id][i];
    // printf("%d %d\n", pos.first, pos.second);
    d[pos.second] = get(ed[pos.first]) - get(st[pos.first] - 1);
  }
  for(int i = 0; i < (int)a[id].size(); ++i) {
    pii pos = a[id][i];
    dfs(ch[u][pos.first], pos.second);
  }
  add(st[u], -1);
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1, tp, ad; i <= n; ++i) {
    scanf("%d", &tp);
    if(tp == 1) ad = 0;
    else scanf("%d", &ad);
    scanf("%s", lx + 1);
    a[ad].push_back(pii(lx[1] - 'a', i));
  }
  int m;
  scanf("%d", &m);
  for(int i = 1, ad; i <= m; ++i) {
    scanf("%d%s", &ad, lx + 1);
    b[ad].push_back(pii(insert(), i));
  }
  build();
  predfs(0), dfs(0, 0);
  for(int i = 1; i <= m; ++i)
    printf("%d\n", d[i]);
  return 0;
}