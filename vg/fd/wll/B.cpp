#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,M=1e5+10;
int v[N],dep[N<<1],head[N<<1],cur[N<<1],Next[M<<2],to[M<<2],w[M<<2];
int n,m,S=0,T,cnt=-1,INF=1e9;
queue<int>q;

void add(int x,int y,int z){
	to[++cnt]=y,w[cnt]=z,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,w[cnt]=0,Next[cnt]=head[y],head[y]=cnt;
}

bool bfs(){
	memset(dep,0,sizeof dep);
	q.push(S);dep[S]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=Next[i]){
			if(!dep[to[i]]&&w[i]) dep[to[i]]=dep[u]+1,q.push(to[i]);
		}
	}
	return dep[T];
}

int dfs(int u,int flow){
	if(u==T) return flow;
	for(int& i=cur[u];i!=-1;i=Next[i]){
		if(dep[to[i]]==dep[u]+1&&w[i]){
			int pos=dfs(to[i],min(flow,w[i]));
			if(pos){
				w[i]-=pos;w[i^1]+=pos;
				return pos;
			}
		}
	}
	return 0;
}

int Dinic(){
	int ans=0;
	for(;bfs();){
		fr(i,S,T) cur[i]=head[i];
		for(;int d=dfs(S,INF);) ans+=d;
	}
	return ans;
}

int main(){
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);T=2*n+1;
	int sum=0;
	fr(i,1,n) scanf("%d",&v[i]),sum+=v[i];
	fr(i,1,n) add(S,i,v[i]),add(i+n,T,v[i]);
	fr(i,1,m){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y+n,z);
	}
	printf("%d\n",sum-Dinic());
	return 0;
}
