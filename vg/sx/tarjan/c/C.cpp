#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10,LOG=20;
struct data{
	int u,nt,to;
}a[N<<1],b[N<<1];
vector<int> g[N];
int head[N],hea[N],vis[N],dfn[N],low[N],st[N],col[N],mk[N];
int dep[N],f[N][LOG+1];
int cnt=-1,tp=0,res=0,num=0;

void add(int x,int y){
	a[++cnt].u=x,a[cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].u=y,a[cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void Add(int x,int y){
	printf("%d %d %d\n",x,y,cnt);
	b[++cnt].to=y,b[cnt].nt=hea[x],hea[x]=cnt;
	b[++cnt].to=x,b[cnt].nt=hea[y],hea[y]=cnt;
}

void dfs(int u,int fa){
	low[u]=dfn[u]=++res;
	int son=0;
	for(int i=head[u];~i;i=a[i].nt) {
		int to=a[i].to;
		if(vis[i/2+1]) continue;
		vis[i/2+1]=1;
		st[++tp]=i;
		son++;
		if(!dfn[to]) {
			dfs(to,u);
			low[u]=min(low[u],low[to]);
			if(low[to]>=dfn[u]) {
				num++;
				if(fa||(!fa&&son>=2)) mk[u]=1;
				if(mk[u]) {
					printf("mkmk%d\n",u);
				}
				for(;tp;){
					g[a[st[tp]].u].push_back(num);
					col[st[tp]/2+1]=num;
					g[a[st[tp]].to].push_back(num);
					// if(num==1) printf("gg%d %d\n",a[st[tp]].u,a[st[tp]].to);
					if(a[st[tp]].u==u) break;
					tp--;
				}
				tp--;
			}
		} else low[u]=min(low[u],dfn[to]);
	}
}

int GetLCA(int A,int B){
	if(dep[A]>dep[B]) swap(A,B);
	rf(i,LOG,0) {
		if(dep[f[B][i]]>=dep[A]) B=f[B][i];
	}
	if(A==B) return A;
	rf(i,LOG,0) {
		if(f[B][i]!=f[A][i]) {
			A=f[A][i],B=f[B][i];
		}
	}
	return f[A][0];
}

void Dfs(int u,int fa){
	// printf("%d %d\n",u,fa);
	vis[u]=1;
	f[u][0]=fa,dep[u]=dep[fa]+1;
	for(int i=hea[u];i;i=b[i].nt) {
		int to=b[i].to;
		if(vis[to]) continue;
		Dfs(to,u);
	}
}

void get(){
	fr(j,1,LOG) fr(i,1,num) {
		f[i][j]=f[f[i][j-1]][j-1];
	}
}

int main(){
	int n,m;
	freopen("out","r",stdin);
	memset(head,-1,sizeof head);
	while(scanf("%d%d",&n,&m)==2&&(n||m)) {
		cnt=-1,res=0,num=0,tp=0;
		fr(i,1,m) {
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		fr(i,1,n) {
			if(!dfn[i]) dfs(i,0);
		}
		fr(i,1,n) {
			printf("i=%d %d %d\n",i,dfn[i],low[i]);
		}
		cnt=0;
		printf("WAO!!!%d\n",n);
		for(int i=1;i<=n;++i){
			printf("%d\n",n);
			if(i>=99999) {
				printf("WAI!!\n");
			}
			if(mk[i]) {
				mk[i]=++num;
				int len=g[i].size();
				frl(j,0,len) {
					Add(num,g[i][j]);
				}
			}
		}
		fr(i,1,m) vis[i]=0;
		fr(i,1,num) {
			if(!vis[i]) Dfs(i,0);
		}
		get();
		int q;scanf("%d",&q);
		fr(i,1,q) {
			int x,y;scanf("%d%d",&x,&y);
			x=col[x],y=col[y];
			int lca=GetLCA(x,y);
			// printf("x=%d y=%d lca=%d\n",x,y,lca);
			int d=dep[x]+dep[y]-2*dep[lca];
			printf("%d\n",d/2);
		}
		fr(i,1,n) {
			head[i]=-1;
			dfn[i]=low[i]=mk[i]=0;
			g[i].clear();
		}
		fr(i,1,m) col[i]=0;
		fr(i,1,num) hea[i]=0,dep[i]=0;
	}
	return 0;
}