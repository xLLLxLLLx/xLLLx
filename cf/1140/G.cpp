#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10,LOG=19;
struct data{
	int nt,to;
}a[N<<1];
ll pre[N][2],dis[N][LOG+1][2][2],wa[N<<1],wb[N<<1],wc[N<<1],v[N],dp[N][2],d[N];
int mn[N],head[N],dep[N],f[N][LOG+1],cnt=0,n;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	f[u][0]=fa,dep[u]=dep[fa]+1;
	dp[u][0]=v[u],mn[u]=0;
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		pre[to][0]=wa[i],pre[to][1]=wb[i];
		dfs(to,u);
		ll pos=dp[to][0]+wc[i];
		if(pos<=dp[u][0]) {
			dp[u][1]=dp[u][0];
			dp[u][0]=pos,mn[u]=to;
		} else if(pos<=dp[u][1]) {
			dp[u][1]=pos;
		}
	}
}

void sfd(int u,int fa){
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		d[to]=min(d[to],d[u]+wc[i]);
		if(mn[u]==to) d[to]=min(d[to],dp[u][1]+wc[i]);
		else d[to]=min(d[to],dp[u][0]+wc[i]);
		sfd(to,u);
	}
}

void getdis(){
	memset(dp,0x3f,sizeof dp);
	memset(d,0x3f,sizeof d);
	d[1]=v[1];
	dfs(1,0);
	sfd(1,0);
	fr(i,1,n) d[i]=min(d[i],dp[i][0]);
}

void get(){
	fr(i,1,LOG) fr(j,1,n) {
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
		if(f[A][i]!=f[B][i]) {
			A=f[A][i],B=f[B][i];
		}
	}
	return f[A][0];
}

ll len[2],nen[2];

ll go(int x,int y,int be,int ed) {
	// printf("ggzz%d %d %d %d\n",x,y,be,ed);
	if(x==y) {
		if(be==ed) return 0ll;
		else return d[x];
	}
	memset(len,0x3f,sizeof len);
	len[be]=0;
	rf(i,LOG,0) {
		if(dep[f[x][i]]>=dep[y]) {
			memset(nen,0x3f,sizeof nen);
			fr(j,0,1) {
				fr(t,0,1) nen[t]=min(nen[t],len[j]+dis[x][i][j][t]);
			}
			fr(j,0,1) len[j]=nen[j];
			x=f[x][i];
		}
	}
	// printf("!!!!!gg%d %d %d %d %lld\n",x,y,be,ed,len[ed]);
	return len[ed];
}

ll cal(int x,int y) {
	int p1=1,p2=1;
	if(x&1) p1=0;
	if(y&1) p2=0;
	x=(x+1)/2,y=(y+1)/2;
	int lca=GetLCA(x,y);
	// printf("zz%d %d\n",x,y);
	ll ans1=go(x,lca,p1,0)+go(y,lca,p2,0);
	ll ans2=go(x,lca,p1,1)+go(y,lca,p2,1);
	return min(ans1,ans2);
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) {
		scanf("%lld",&v[i]);
	}
	fr(i,1,n-1) {
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		scanf("%lld%lld",&wa[cnt],&wb[cnt]);
		wa[cnt-1]=wa[cnt],wb[cnt-1]=wb[cnt];
	}
	fr(i,1,cnt) {
		wc[i]=wa[i]+wb[i];
	}
	getdis(),get();
	memset(dis,0x3f,sizeof dis);
	fr(i,1,n) {
		int fa=f[i][0];
		dis[i][0][0][0]=min(pre[i][0],pre[i][1]+d[fa]+d[i]);
		dis[i][0][0][1]=min(pre[i][0]+d[fa],d[i]+pre[i][1]);
		dis[i][0][1][0]=min(pre[i][1]+d[fa],d[i]+pre[i][0]);
		dis[i][0][1][1]=min(pre[i][1],pre[i][0]+d[fa]+d[i]);
	}
	fr(i,1,LOG) {
		fr(j,1,n) {
			fr(k,0,1) fr(t,0,1) {
				fr(l,0,1) {
					dis[j][i][k][l]=min(dis[j][i][k][l],dis[j][i-1][k][t]+dis[f[j][i-1]][i-1][t][l]);
				}
			}
		}
	}
	// fr(i,1,n) fr(j,0,LOG) fr(k,0,1) fr(t,0,1) {
	// 	printf("dis[%d][%d][%d][%d]=%lld\n",i,j,k,t,dis[i][j][k][t]);
	// } 
	// fr(i,1,n) fr(j,0,1) printf("pre[%d][%d]=%lld\n",i,j,pre[i][j]);
	// fr(i,1,n) printf("d[%d]=%lld\n",i,d[i]);
	int q;scanf("%d",&q);
	fr(o,1,q) {
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%lld\n",cal(x,y));
	}
	return 0;
}