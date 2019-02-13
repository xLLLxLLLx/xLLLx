#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
struct data{
	int nt,to;
	LL w;
}a[N*N*6];
queue<int>q;
int head[N*N],dep[N*N],cur[N*N],n,m,cnt=-1,INF=1e9;

void add(int x,int y,int c){
	a[++cnt].to=y,a[cnt].w=c,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=c,a[cnt].nt=head[y],head[y]=cnt;
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
	return dep[m*n];
}

LL dfs(int s,LL v){
	if(s==n*m) return v;
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

int main(){
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	fr(i,1,n) fr(j,1,m-1) {
		int w;scanf("%d",&w);
		int x=(i-1)*m+j,y=(i-1)*m+j+1;
		add(x,y,w);
	}
	fr(i,1,n-1) fr(j,1,m) {
		int w;scanf("%d",&w);
		int x=(i-1)*m+j,y=i*m+j;
		add(x,y,w);
	}
	fr(i,1,n-1) fr(j,1,m-1) {
		int w;scanf("%d",&w);
		int x=(i-1)*m+j,y=i*m+j+1;
		add(x,y,w);
	}
	for(;bfs();) {
		fr(i,1,n*m) cur[i]=head[i];
		for(;LL d=dfs(1,INF);) 
			ans+=d;
	}
	printf("%lld\n",ans);
	return 0;
}
