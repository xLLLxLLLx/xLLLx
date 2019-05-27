#pragma comment(linker, "/STACK:102400000,102400000") 
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10,LOG=20;
struct data{
	int u,nt,to;
}a[N<<1];
vector<int>g[N];
int head[N],dfn[N],low[N],mk[N],col[N],vis[N],st[N];
int dep[N],vs[N],f[N][LOG+1];
int top=0,cnt=-1,res=0,num=0;

void add(int x,int y){
	a[++cnt].u=x,a[cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].u=y,a[cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	dfn[u]=low[u]=++res;
	int son=0;
	for(int i=head[u];~i;i=a[i].nt) {
		if(vis[i]) continue;
		vis[i]=vis[i^1]=1;
		st[++top]=i;
		int to=a[i].to;
		if(!dfn[to]) {
			dfs(to,u),son++;
			low[u]=min(low[u],low[to]);
			if(low[to]>=dfn[u]) {
				++num;
				if(fa||(!fa&&son>=2)) mk[u]=1;
				for(;;) {
					g[a[st[top]].u].push_back(num);
					col[st[top]/2+1]=num;
					g[a[st[top]].to].push_back(num);
					if(a[st[top]].u==u) break;
					top--;
				}
				top--;
			}
		} else low[u]=min(low[u],dfn[to]);
	}
}

void Dfs(int u,int fa){
	vs[u]=1,dep[u]=dep[fa]+1,f[u][0]=fa;
	for(int i=head[u];~i;i=a[i].nt) {
		int to=a[i].to;
		if(vs[to]) continue;
		Dfs(to,u);
	}
}

void get(){
	fr(i,1,LOG) fr(j,1,num) {
		f[j][i]=f[f[j][i-1]][i-1];
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


int main(){
	int n,m;
	memset(head,-1,sizeof head);
	while(scanf("%d%d",&n,&m)==2&&(n||m)) {
		cnt=-1,res=num=top=0;
		fr(i,1,m) {
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		fr(i,1,n) {
			if(!dfn[i]) dfs(i,0);
		}
		fill(head,head+n+1,-1);
		cnt=-1;
		fr(i,1,n) {
			if(mk[i]) {
				mk[i]=++num;
				int len=g[i].size();
				frl(j,0,len) {
					add(num,g[i][j]);
				}
			}
		}
		fr(i,1,num) {
			if(!vs[i]) {
				Dfs(i,0);
			}
		}
		get();
		int q;scanf("%d",&q);
		fr(o,1,q) {
			int x,y;scanf("%d%d",&x,&y);
			x=col[x],y=col[y];
			// printf("x=%d y=%d\n",x,y);
			int lca=GetLCA(x,y);
			printf("%d\n",(dep[x]+dep[y]-2*dep[lca])/2);
		}
		fr(i,1,n) g[i].clear();
		fill(head, head + num + 1, -1);
		fill(vs,vs+num+1,0);
		fill(mk,mk+n+1,0);
		fill(vis,vis+m+1,0);
		fill(dfn,dfn+n+1,0);
		fill(low,low+n+1,0);
	}
}