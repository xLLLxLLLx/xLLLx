#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=210;
struct data{
	int nt,to;
	LL w;
}a[N<<1];
queue<int>q;
int head[N],dep[N],cur[N],n,m,cnt=-1,INF=1e9;

void add(int x,int y,int c){
	a[++cnt].to=y,a[cnt].w=c,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=0,a[cnt].nt=head[y],head[y]=cnt;
}

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

int main(){
	while(scanf("%d%d",&m,&n)==2){
		memset(head,-1,sizeof head);
		LL ans=0;cnt=-1;
		fr(i,1,m){
			int x,y;LL w;
			scanf("%d%d%lld",&x,&y,&w);
			add(x,y,w);
		}
		for(;bfs();) {
			fr(i,1,n) cur[i]=head[i];
			for(;LL d=dfs(1,INF);) 
				ans+=d;
		}
		fr(i,1,n) head[i]=-1;
		printf("%lld\n",ans);
	}
	return 0;
}
