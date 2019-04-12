#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int nt,to;
}a[N<<1];
map<LL,int>ys;
int cnt=0,head[N],sz[N];
LL d[N],dis[N];

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void fail(){
	printf("-1\n");
	exit(0);
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dis[a[i].to]=dis[u]+1;
		dfs(a[i].to,u);
	}
}

int main(){
	int n;read(n);
	fr(i,1,n) read(d[i]),ys[d[i]]=i;
	sort(d+1,d+1+n);
	fr(i,1,n) sz[i]=1;
	rf(i,n,2){
		int u=ys[d[i]];
		int gg=n-2*sz[u];
		if(gg<0) fail();
		LL pos=d[i]-gg;
		if(!ys.count(pos)) fail();
		sz[ys[pos]]+=sz[u];
		add(ys[pos],u);
	}
	dfs(ys[d[1]],0);
	fr(i,1,n) d[1]-=dis[i];
	if(d[1]) fail();
	fr(u,1,n){
		for(int i=head[u];i;i=a[i].nt){
			if(i&1) printf("%d %d\n",a[i].to,u);
		}
	}
	return 0;
}