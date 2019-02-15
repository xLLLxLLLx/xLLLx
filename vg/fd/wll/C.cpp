#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=25,M=N*N*N*N*10;
int n,m,d,S,T,INF=1e8;
int a[N][N],dep[M];
int head[M],Next[M],to[M],w[M],cur[M],cnt=-1;
queue<int>q;

int zh(int x,int y){
	return (x-1)*m+y;
}

int hz(int x,int y){
	return (x-1)*m+y+n*m;
}

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


bool check(int x,int y,int i,int j){
	return (x-i)*(x-i)+(y-j)*(y-j)<=(d*d);
}

int main(){
	scanf("%d%d%d",&n,&m,&d);
	memset(head,-1,sizeof head);
	S=0,T=n*m*2+2;
	fr(i,1,n) fr(j,1,m){
		scanf("%1d",&a[i][j]);
		if(a[i][j]) add(zh(i,j),hz(i,j),a[i][j]);
	}
	int res=0;
	fr(i,1,n) fr(j,1,m){
		char ch;cin>>ch;
		if(ch=='L') add(S,zh(i,j),1),res++;
	}
	fr(i,1,n) fr(j,1,m) fr(k,1,n) fr(t,1,m){
		if(!a[i][j]||!a[k][t]) continue;
		if(i!=k||j!=t){
			if(check(i,j,k,t))
				add(hz(i,j),zh(k,t),INF);
		}
	}
	fr(i,1,n) fr(j,1,m){
		if(i+d>n||i-d<1||j+d>m||j-d<1)
			add(hz(i,j),T,INF);
	}
	printf("%d\n",res-Dinic());
	return 0;
}
