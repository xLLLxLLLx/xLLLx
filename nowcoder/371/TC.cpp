#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int nt,to;
}a[N<<1];
struct edge{
	int l,r,h,flg;
}b[N<<1];
int head[N],dfn[N],ed[N],dep[N],g[N][25];
int res=0,cnt=0;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1,g[u][0]=fa;
	dfn[u]=++res;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dfs(a[i].to,u);
	}
	ed[u]=res;
}

void yyqx(){
	fr(i,1,24)
	 fr(j,1,n) 
	  g[j][i]=g[g[j][i-1]][i-1];
}

int GetLCA(int A,int B){
	if(dep[A]>dep[B]) swap(A,B);
	rf(i,24,0) if(dep[B]-(1<<i)>=dep[A]) B=g[B][i];
	if(A==B) return A;
	rf(i,24,0)
		if(g[B][i]!=g[A][i]) A=g[A][i],B=g[B][i];
	return g[A][0];
}

int main(){
	int n,m;read(n),read(m);
	for(int i=1,x,y;i<n;++i){
		read(x),read(y);
		add(x,y);
	}
	dfs(1,1),yyqx();
	LL ans=n*1LL*(n-1);
	for(int i=1,x,y;i<=m;++i){
		read(x),read(y);
		if(dep[x]>dep[y]) swap(x,y);
		int zz=GetLCA(x,y);
		if(zz==x){
			
		} else {
			
		}
	}
	printf("%lld\n",ans/2);
	return 0;
}
