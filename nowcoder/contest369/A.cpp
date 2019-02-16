#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=50,mod=1e9+7,M=510;
int vis[N][N][N];
LL dp[M][N][N];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,m){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		vis[x][y][z]=1,vis[x][z][y]=1;
		vis[y][x][z]=1,vis[y][z][x]=1;
		vis[z][x][y]=1,vis[z][y][x]=1;
	}
	fr(i,1,49) fr(j,1,49) dp[1][i][j]=1;
	fr(i,1,n-2){
		fr(j,1,49) fr(k,1,49) fr(t,1,49){
			if(vis[j][k][t]) continue;
			Add(dp[i+1][k][t],dp[i][j][k]);
		}
	}
	LL ans=0;
	fr(i,1,49) fr(j,1,49) Add(ans,dp[n-1][i][j]);
	printf("%lld\n",ans);
	return 0;
}
