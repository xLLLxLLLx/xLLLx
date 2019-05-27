#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10;
struct data{
	int nt,to,w;
}a[N<<1];
int H[N],n,k,h=0,B[N],b=0;
int head[N],vis[N],g[N],dep[N],sz[N],f[N];
int ans=0,cnt=0;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,int w){
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
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

void js(){
	sort(H+1,H+1+h);
	int lt=h;
	fr(i,1,h){
		while(lt-1>=0&&H[i]+H[lt]>k) lt--;
		if(lt>i) ans+=lt-i;
		else break;
	}
}

void sj(){
	sort(B+1,B+1+b);
	int lt=b;
	fr(i,1,b){
		while(lt-1>=0&&B[i]+B[lt]>k) lt--;
		if(lt>i) ans-=lt-i;
		else break;
	}
}

void find(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa||vis[to]) continue;
		dep[to]=dep[u]+a[i].w;
		B[++b]=dep[to];
		H[++h]=dep[to];
		find(to,u);
	}
}

void dfs(int u,int fa){
	int be=Get(u,fa);
	dep[be]=0;h=1;H[1]=0;
	for(int i=head[be];i;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]) continue;
		else {
			b=1;B[1]=dep[to]=a[i].w;
			H[++h]=dep[to];
			find(to,be);
			sj();
		}
	}
	vis[be]=1;js();
	for(int i=head[be];i;i=a[i].nt){
		if(vis[a[i].to]) continue;
		dfs(a[i].to,be);
	}
}

int main(){
	while(1){
		memset(head,0,sizeof head);
		memset(vis,0,sizeof vis);
		cnt=0;ans=0;h=0;b=0;
		read(n),read(k);
		if(!n||!k) break;
		for(int i=1,x,y,w;i<n;++i){
			read(x),read(y),read(w);
			add(x,y,w);
		}
		vis[0]=1,dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}