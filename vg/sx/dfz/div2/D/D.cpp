#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
const int inf=2e9;
struct data{
	int nt,to,w;
}a[N<<1];
int n,k,m,cnt=0,ans=0;
int vis[N],g[N],B[N],H[N],sz[N],mk[N],f[N],tr[N],head[N],dep[N],nm[N];

void add(int x,int y,int w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

int lower(int x){
	return x&(-x);
}

void upd(int x,int y){
	x++;
	for(;x<N;x+=lower(x))
		tr[x]=max(tr[x],y);
}

int get(int x){
	x++;
	int pos=-inf;
	for(;x;x-=lower(x))
		pos=max(pos,tr[x]);
	return pos;
}

int Get(int u,int fa){
	sz[u]=1;f[u]=fa;g[u]=u;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa||vis[to]) continue;
		Get(to,u);
		sz[u]+=sz[to];
	}
	int pos=-1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa||vis[to]) continue;
		if(sz[to]*2>=sz[u]) pos=g[to];
	}
	if(pos==-1) return u;
	while(sz[f[pos]]*2<=sz[u]&&f[pos]!=fa) pos=f[pos];
	return g[u]=pos;
}

void js(int x){
	fr(i,1,B[0]) {
		if(k<nm[B[i]]+x) continue;
		int gg=get(k-nm[B[i]]-x);
		ans=max(ans,dep[B[i]]+gg);
	}
}

void qk(int x){
	x++;
	for(;x<N;x+=lower(x))
		tr[x]=-inf;
}

void clear(){
	fr(i,1,H[0]) {
		qk(nm[H[i]]);
		// printf("H%d nm=%d dep=%d\n",H[i],nm[H[i]],dep[H[i]]);
		if(nm[H[i]]<=k) ans=max(ans,dep[H[i]]);
	}
}

void find(int u,int fa){
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(vis[to]||to==fa) continue;
		dep[to]=dep[u]+a[i].w,nm[to]=nm[u]+mk[to];
		B[++B[0]]=to;
		find(to,u);
	}
}

void dfs(int u,int fa){
	int be=Get(u,fa);
	// printf("u=%d fa=%d be=%d\n",u,fa,be);
	dep[be]=0,nm[be]=0;
	H[0]=0,H[++H[0]]=be;
	for(int i=head[be];i;i=a[i].nt) {
		// printf("??\n");
		int to=a[i].to;
		if(vis[to]) continue;
		dep[to]=dep[be]+a[i].w,nm[to]=nm[be]+mk[to];
		B[0]=0;
		B[++B[0]]=to;
		find(to,be),js(mk[be]);
		fr(j,1,B[0]) {
			H[++H[0]]=B[j];
			upd(nm[B[j]],dep[B[j]]);
		}
	}
	clear();
	vis[be]=1;
	for(int i=head[be];i;i=a[i].nt) {
		if(vis[a[i].to]) continue;
		dfs(a[i].to,be);
	}
}

int main(){
	scanf("%d%d%d",&n,&k,&m);
	fr(i,1,m) {
		int x;
		scanf("%d",&x);
		mk[x]=1;
	}
	fr(i,2,n) {
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
	}
	vis[0]=1,dfs(1,0);
	printf("%d\n",ans);
	return 0;
}