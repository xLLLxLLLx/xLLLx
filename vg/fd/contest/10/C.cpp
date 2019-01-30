#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=501;
LL mod;
int a[N];
LL dp[2][N][N];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

int main(){
	//freopen("out","r",stdin);
	int n,m,b;scanf("%d%d%d%lld",&n,&m,&b,&mod);
	fr(i,1,n) scanf("%d",&a[i]);
	dp[0][0][0]=1;
	fr(o,1,n){
		int nw=(o&1);
		fr(i,0,m)
		 fr(j,0,b){
		 	dp[nw][i][j]=dp[nw^1][i][j];
		 	if(i&&j>=a[o]) Add(dp[nw][i][j],dp[nw][i-1][j-a[o]]);
		 }
	}
	LL ans=0;
	fr(i,0,b) Add(ans,dp[n&1][m][i]);
	printf("%lld\n",ans);
	return 0;
}
