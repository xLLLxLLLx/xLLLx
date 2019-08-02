#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=55,M=2510;
int a[N];
ll dp[2][N][M];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%d",&a[i]);
	dp[0][0][0]=1;
	int nw=0;
	fr(i,1,n){
		memset(dp[nw^1],0,sizeof dp[nw^1]);
		fr(j,0,i-1) fr(k,0,2500){
			if(!dp[nw][j][k]) continue;
			dp[nw^1][j][k]+=dp[nw][j][k];
			dp[nw^1][j+1][k+a[i]]+=dp[nw][j][k];
		}
		nw^=1;
	}
	ll ans=0;
	fr(i,1,n) ans+=dp[nw][i][i*m];
	printf("%lld\n",ans);
	return 0;
}