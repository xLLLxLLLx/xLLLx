#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e4 + 10;
struct node {
	int to, w;
} ;
struct data{
	int nt, to;
	LL w;
}a[N << 1];
vector <node> g[N], t[N];
queue<int>q;
int n, m, cnt = -1;
int head[N], dep[N], vis[N], cur[N];
LL INF = 1e13, dis[N], Dis[N];

void add(int x,int y,int c){
	a[++cnt].to=y,a[cnt].w=c,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=0,a[cnt].nt=head[y],head[y]=cnt;
}

LL ans=0;

bool bfs(){
	q.push(1);
	memset(dep,0,sizeof dep);
	dep[1]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=a[i].nt){
			int to=a[i].to;
			if(!dep[to]&&a[i].w) dep[to]=dep[u]+1,q.push(to);
		}
	}
	return dep[n];
}

LL dfs(int s,LL v){
	if(s==n) return v;
	for(int& i=cur[s];i!=-1;i=a[i].nt){
		if(dep[a[i].to]==dep[s]+1&&a[i].w){
			LL d=dfs(a[i].to,min(a[i].w,v));
			if(d){
				a[i].w-=d;
				a[i^1].w+=d;
				return d;
			}
		}
	}
	return 0LL;
}

int main() {
	// freopen("05", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d", &n, &m);
		cnt = -1;
		for(int i = 1; i <= n; ++i) {
			dis[i] = Dis[i] = 1e13;
			head[i] = -1;
			g[i].clear();
			t[i].clear();
			cur[i] = 0;
			dep[i] = 0;
			vis[i] = 0;
		}
		for(int i = 1, x, y, w; i <= m; ++i) {
			scanf("%d%d%d", &x, &y, &w);
			g[x].push_back((node){y, w}),
			t[y].push_back((node){x, w});
		}
		dis[1] = 0;
		q.push(1), vis[1] = 1;
		while(!q.empty()) {
			int h = q.front(); q.pop();
			vis[h] = 0;
			for(int i = 0; i < g[h].size(); ++i) {
				LL pos= dis[h] + g[h][i].w;
				if(dis[g[h][i].to] > pos) {
					if(!vis[g[h][i].to]) q.push(g[h][i].to);
					dis[g[h][i].to] = pos;
					vis[g[h][i].to] = 1;
				}
			}
		}
		Dis[n] = 0;
		q.push(n), vis[n] = 1;
		while(!q.empty()) {
			int h = q.front(); q.pop();
			vis[h] = 0;
			for(int i = 0; i < t[h].size(); ++i) {
				LL pos = Dis[h] + t[h][i].w;
				if(Dis[t[h][i].to] > pos) {
					Dis[t[h][i].to] = pos;
					if(!vis[t[h][i].to]) q.push(t[h][i].to);
					vis[t[h][i].to] = 1;
				}
			}
		}
		for(int i = 1; i < n; ++i) {
			if(dis[i] + Dis[i] != dis[n]) {
				continue;
			}
			for(int j = g[i].size() - 1; j >= 0; --j) {
				if(dis[g[i][j].to] + Dis[g[i][j].to] == dis[n] && dis[i] + g[i][j].w == dis[g[i][j].to]) {
					add(i, g[i][j].to, g[i][j].w);
				}
			}
		}
		LL ans = 0;
		for(;bfs();) {
			for(int i = 1; i <= n; ++i)
				cur[i]=head[i];
			for(;LL d=dfs(1,INF);) 
				ans+=d;
		}
		printf("%lld\n", ans);
	}
	return 0;
}