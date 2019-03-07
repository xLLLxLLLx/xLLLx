#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
LL dp[N][2][2];
int vis[N],a[N][2];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n*2){
		int x;scanf("%d",&x);
		if(vis[x]) a[x][1]=i;
		else vis[x]=1,a[x][0]=i;
	}
	memset(dp,0x3f,sizeof dp);
	dp[1][0][1]=dp[1][1][0]=a[1][0]+a[1][1]-2;
	fr(i,2,n) fr(j,0,1) fr(t,0,1){
		int ps=j^1,nw=t^1;
		int pos=abs(a[i][t]-a[i-1][j])+abs(a[i][nw]-a[i-1][ps]);
		dp[i][t][nw]=min(dp[i][t][nw],dp[i-1][j][ps]+pos);
	}
	cout<<dp[n][0][1]<<endl;
	return 0;
}
