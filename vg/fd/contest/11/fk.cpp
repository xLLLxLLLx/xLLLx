#include<bits/stdc++.h>
using namespace std;
const int N=205;
const int M=1e5+10;
const int inf=0x3f3f3f3f;
 
int n,cnt,E=1,S=201,T=202,a[N],pri[M];
int fir[N],vis[N],dis[N],nex[M],arr[M],cap[M],use[N],can[N][N];
queue<int> Q;
vector<int> vec[N];
 
void Init() {
	for (int i=2;i<M;i++) pri[i]=1;
	for (int i=2;i<M;i++)
		if (pri[i])
			for (int j=i+i;j<M;j+=i) pri[j]=0;
}
 
inline void Add_Edge(int x,int y,int c) {
	nex[++E]=fir[x];
	fir[x]=E; arr[E]=y; cap[E]=c;
	nex[++E]=fir[y];
	fir[y]=E; arr[E]=x; cap[E]=0;
}
 
int Bfs() {
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0; Q.push(S);
	while (!Q.empty()) {
		int u=Q.front(); Q.pop();
		for (int i=fir[u];i;i=nex[i])
			if (cap[i]&&dis[arr[i]]==inf) {
				dis[arr[i]]=dis[u]+1;
				Q.push(arr[i]);
			}
	}
	return dis[T]<inf;
}
 
int Dfs(int x,int flow) {
	if (x==T||!flow) return flow;
	int ans=0;
	for (int i=fir[x];i;i=nex[i])
		if (cap[i]&&dis[arr[i]]==dis[x]+1) {
			int del=Dfs(arr[i],min(flow,cap[i]));
			ans+=del; cap[i]-=del; cap[i^1]+=del; flow-=del;
		}
	return ans;
}
 
void Dinic() {
	for (int i=1;i<=n;i++) {
		if (a[i]&1) Add_Edge(S,i,2);
		else Add_Edge(i,T,2);
	}
	for (int i=1;i<=n;i++)
		if (a[i]&1) {
			for (int j=1;j<=n;j++)
				if (!(a[j]&1)&&pri[a[i]+a[j]]) {
					Add_Edge(i,j,1);
				} 
		}
	int ans=0;
	while (Bfs()) ans+=Dfs(S,inf);
	if (ans<n) puts("Impossible"),exit(0); 
}
 
void Getans(int x) {
	for (int i=1;i<=n;i++)
		if (can[x][i]&&!use[i]) {
			use[i]=cnt;
			vec[cnt].push_back(i);
			Getans(i);
		}
}
 
int main() {
	Init();
	scanf("%d",&n);
	if (n&1) return 0*puts("Impossible");
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) {
		if (a[i]&1) cnt++;
		else cnt--;
	}
	if (cnt) return 0*puts("Impossible");
	Dinic(); cnt=0;
	for (int i=1;i<=n;i++) {
		if (a[i]&1) {
			for (int j=fir[i];j;j=nex[j])
				if (arr[j]<=n&&!cap[j]) can[i][arr[j]]=can[arr[j]][i]=1;
		}
	}
	for (int i=1;i<=n;i++)
		if (!use[i]) {
			use[i]=++cnt;
			vec[cnt].push_back(i);
			Getans(i);
		}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++) {
		printf("%d ",vec[i].size());
		for (int j=0;j<vec[i].size();j++) printf("%d ",vec[i][j]);
		putchar('\n');
	}
	return 0;
}

