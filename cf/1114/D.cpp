#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=5010;
int dp[N][N][2],a[N];

int main(){
	int n;scanf("%d",&n);
	memset(dp,0x3f,sizeof dp);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n) fr(t,0,1) dp[i][i][t]=0;
	fr(len,1,n) fr(l,1,n-len+1) fr(it,0,1) {
		int r=l+len-1;
		int c=(it?a[r]:a[l]);
        dp[l-1][r][0]=min(dp[l-1][r][0],dp[l][r][it]+(c!=a[l-1]));
        dp[l][r+1][1]=min(dp[l][r+1][1],dp[l][r][it]+(c!=a[r+1]));
	}
	//fr(i,1,n) fr(j,1,n) fr(t,0,1) printf("f[%d][%d][%d]=%d\n",i,j,t,dp[i][j][t]);
	printf("%d\n",min(dp[1][n][0],dp[1][n][1]));
	return 0;
}

