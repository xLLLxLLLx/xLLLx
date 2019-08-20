#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data{
  int nt, to;
  ll w;
} a[N];
queue<int>q;
int n, m, S, T, cnt = -1;
int head[N], dep[N], cur[N];
ll INF = 1e13, dis[N], Dis[N], d[N];

void add(int x,int y,int c){
  // printf("%d %d %d\n", x, y, c);
  a[++cnt].to=y,a[cnt].w=c,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].w=0,a[cnt].nt=head[y],head[y]=cnt;
}

bool bfs() {
  memset(dep, 0, sizeof dep);
  q.push(S), dep[S] = 1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i = head[u]; ~i; i = a[i].nt) {
      int to = a[i].to;
      if(!dep[to] && a[i].w) {
        dep[to] = dep[u] + 1;
        q.push(to);
      }
    }
  }
  return dep[T];
}

ll dfs(int s, ll v) {
  if(s == T) return v;
  for(int& i = cur[s]; ~i; i = a[i].nt) {
    if(dep[a[i].to] == dep[s] + 1 && a[i].w) {
      ll d = dfs(a[i].to, min(a[i].w, v));
      if(d) {
        a[i].w -= d;
        a[i ^ 1].w += d;
        return d;
      }
    }
  }
  return 0ll;
}

ll v[N];

int main() {
	freopen("cooling.in", "r", stdin);
	freopen("cooling.out", "w", stdout);
	memset(head, -1, sizeof head);
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; ++i) {
  	int x, y, z, w;
  	scanf("%d%d%d%d", &x, &y, &z, &w);
  	d[x] -= z, d[y] += z;
  	v[i] = z;
  	add(x, y, w - z);
  }
  S = 0, T = n + 1;
  for(int i = 1; i <= n; ++i) {
  	// printf("d[%d]=%lld\n", i, d[i]);
  	if(d[i] > 0) {
  		add(S, i, d[i]);
  	} else if(d[i] < 0) {
  		add(i, T, -d[i]);
  	}
  }
  for(; bfs();) {
    for(int i = 0; i <= n + 1; ++i)
      cur[i] = head[i];
    for(; dfs(S, INF);) ;
  }
	for(int i = head[S]; ~i; i = a[i].nt) {
		// printf("q%lld\n", a[i].w);
		if(a[i].w) {
			return printf("NO\n"), 0;
		}
	}
	for(int i = head[T]; ~i; i = a[i].nt) {
		if(a[i ^ 1].w) {
			return printf("NO\n"), 0;
		}
	}
	printf("YES\n");
	for(int i = 1; i <= m; ++i) {
		// printf("qwq%lld\n", a[i * 2 - 1].w);
		ll pos = a[i * 2 - 1].w;
		printf("%lld\n", pos + v[i]);
	}
	return 0;
}