#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, LOG = 20;
ll d1[N], d2[N], d3[N], ans = 0;

template <class T>
void read(T &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

namespace T1 {
	struct data {
		int nt, to;
		ll w;
	} a[N << 1];
	int head[N], ys[N], dep[N], ou[N << 1], g[N << 1][LOG + 1];
	int res = 0, o = 0;
	void add(int x, int y, ll w) {
		a[++o].to = y;
		a[o].w = w;
		a[o].nt = head[x];
		head[x] = o;
	}
	void predfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		ys[u] = ++res, ou[res] = u, g[res][0] = u;
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(to == fa) continue;
			d1[to] = d1[u] + a[i].w;
			g[++res][0] = u;
			predfs(to, u);
		}
	}	
	int get(int x, int y) {
		if(dep[x] > dep[y]) return y;
		else return x;
	}
	void init() {
		for(int j = 1; j <= LOG; ++j)
			for(int i = 1; i <= res; ++i) {
				if(i + (1 << j) > res + 1) continue;
				g[i][j] = get(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
			}
	}
	int GetLCA(int x, int y) {
		int l = ys[x], r = ys[y];
		if(l > r) swap(l, r);
		int k = (int)(log(double(r - l + 1)) / log(2.0));
		return get(g[l][k], g[r - (1 << k) + 1][k]);
	}
	void solve() {
		predfs(1, 0);init();
	}
}

namespace T2 {
	int id[N], idx, idx2, sta[N], top, dep[N];
	int o = 1, head[N], f[N][LOG], ys[N];
	struct Edge {
		int to, nt;
		ll w;
	} E[N << 1];
	void add(int x, int y, ll w) {
		E[o] = (Edge){y, head[x], w}, head[x] = o++;
		E[o] = (Edge){x, head[y], w}, head[y] = o++;
	}
	int get(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	void predfs(int u, int fa) {
		id[u] = ++idx;
		f[++idx2][0] = u, ys[u] = idx2;
		for(int i = head[u]; i; i = E[i].nt) {
			int v = E[i].to;
			ll w = E[i].w;
			if(v == fa) continue;
			dep[v] = dep[fa] + 1;
			d2[v] = d2[u] + w;
			predfs(v, u);
			f[++idx2][0] = u;
		}
	}
	void init() {
		for(int j = 1; j <= LOG; ++j)
			for(int i = 1; i <= idx2; ++i) {
				if(i + (1 << j) > idx2 + 1) continue;
				f[i][j] = get(f[i][j - 1], f[i + 1 << (j - 1)][j - 1]);
			}
	}
	int GetLCA(int x, int y) {
		int l = ys[x], r = ys[y];
		if(l > r) swap(l, r);
		int k = (int)(log(double(r - l + 1)) / log(2.0));
		return get(g[l][k], g[r - (1 << k) + 1][k]);
	}
	void solve() {
		predfs(1, 0), init();
		sta[++top] = 1;
	}
	ll cal(int u, int v) {
		if(!u && !v) return -2;
		if(!u || !v) return -1;
		return T3::ask(u, v);
	}
}

namespace T2{
  struct data{
      int x,y;ll v;
      data(int _x=0,int _y=0,ll _v=0):x(_x),y(_y),v(_v){};
      void init(){x=y=0;v=-2;}
      data operator +(const data&A)const{
          data re=v>A.v?*this:A;
          if(upd(re.v,cal(x,A.x)))re=data(x,A.x,re.v);
          if(upd(re.v,cal(x,A.y)))re=data(x,A.y,re.v);
          if(upd(re.v,cal(y,A.x)))re=data(y,A.x,re.v);
          if(upd(re.v,cal(y,A.y)))re=data(y,A.y,re.v);
          return re;
      }
      ll operator *(const data&A)const{
          ll re=0;
          upd(re,cal(x,A.x));
          upd(re,cal(x,A.y));
          upd(re,cal(y,A.x));
          upd(re,cal(y,A.y));
          return re;
      }
  }L[N],R[N];
  void dfs2(int u,int fa){
      L[u].init();R[u].init();
      if(fg[u]&1)L[u].x=u,L[u].v++;
      else if(fg[u])R[u].x=u,R[u].v++;
      for(int i=hd[u];i;i=E[i].nt){
          int v=E[i].v;
          if(v==fa)continue;
          dfs2(v,u);
          upd(ans,max(L[u]*R[v],R[u]*L[v])-2*d2[u]+W);
          L[u]=L[u]+L[v];R[u]=R[u]+R[v];
      }
  }
  bool cmp(int a,int b){return id[a]<id[b];}
  void query(){
      o=1;sort(st+1,st+tot+1,cmp);
      hd[1]=0;for(int i=1;i<=tot;++i)hd[st[i]]=0;
      for(int i=1;i<=tot;++i){
          if(st[i]==sta[top])continue;
          int u=st[i],w=lca(u,sta[top]);
          if(w==sta[top]){sta[++top]=u;continue;}
          while(top>1&&dep[sta[top-1]]>=dep[w])Adde(sta[top-1],sta[top]),top--;
          if(w!=sta[top])hd[w]=0,Adde(w,sta[top--]),sta[++top]=w;
          sta[++top]=u;
      }
      while(top>1)Adde(sta[top-1],sta[top]),top--;
      dfs2(1,0);
  }
}

typedef pair<int, ll> P;

namespace T3 {
	int o, head[N], cnt, size, vis[N << 1], rt, mn, sz[N];
	vector<P> g[N];
	struct Edge {
		int to, nt;
		ll w;
	}a[N << 1];
	void add(int x, int y, ll w) {
		g[x].push_back(P(y, w));
		g[y].push_back(P(x, w));
	}
	void Add(int x, int y, ll w) {
		E[o] = (Edge){y, head[x], w}, head[x] = o++;
		E[o] = (Edge){x, head[x], w}, head[y] = o++;
	}
	void dfs(int u, int fa) {
		for(int i = 0, lst = 0; i < (int)g[u].size(); ++i) {
			int v = g[u][i].first;
			ll w = g[u][i].second;
			if(v == fa) continue;
			dfs(v, u);
			if(!lst) {
				Add(u, v, w), lst = u;
				continue;
			}
			Add(lst, ++cnt, 0), Add(cnt, v, w);
			lst = cnt;
		}
	}
	void getrt(int u, int fa) {
		sz[u] = 1;
		for(int i = head[u]; ~i; i = E[i].nt) {
			int v = E[i].to;
			if(v == fa || vis[i]) continue;
			getrt(v, u), sz[u] += sz[v];
			int tmp = max(sz[v], size - sz[v]);
			if(rt == -1 || tmp < mn) mn = tmp, rt = i;
		}
	}
	void cal(int u, int fa, int col) {
		if(u <= n) fg[st[++tot] = u] = col;
		for(int i = head[u]; ~i; i = E[i].nt) {
			int v = E[i].to;
			ll w = E[i].w;
			if(v == fa || vis[i]) continue;
			d3[v] = d3[u] + w;
			cal(v, u, col);
		}
	}

	void divide(int i) {
		if(size == 1) return ;
		vis[i] = vis[i ^ 1] = 1;
		int p = E[i].to, q = E[i ^ 1].to;
		tot = 0;
		d3[p] = 0, cal(p, 0, 1);
		d3[q] = 0, cal(q, 0, 1);
		W = E[i].w;
		T2::ask();
		for(int j = 1; j <= tot; ++j)
			fg[st[j]] = 0;
		int t1 = sz[p] < sz[q] ? sz[p] : size - sz[q];
		int t2 = size - t1;
		rt = -1, size = t1;
		getrt(p, 0);
		divide(rt);
		rt = -1, size = t2;
		getrt(q, 0);
		divide(rt);
	}
	void solve(){ 
		for(int i = 1; i <= n * 2; ++i) head[i] = -1;
		cnt = n;
		dfs(1, 0);
		rt = -1, size = cnt;
		getrt(1, 0);
		divide(rt);
	}
}

int main() {
	int n;
	read(n);
	int x, y; ll w;
	for(int i = 1; i < n; ++i) {
		read(x), read(y), read(w);
		T1::add(x, y, w);
	}
	for(int i = 1; i < n; ++i) {
		read(x), read(y), read(w);
		T2::add(x, y, w);
	}
	for(int i = 1; i < n; ++i) {
		read(x), read(y), read(w);
		T3::add(x, y, w);
	}
	T1::solve();
	T2::solve();
	T3::solve();
	printf("%lld\n", ans);
	return 0;
}