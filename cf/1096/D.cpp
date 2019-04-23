#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
char lx[N];
ll dp[N][5],a[N];

int get(char ch){
	if(ch=='h') return 1;
	if(ch=='a') return 2;
	if(ch=='r') return 3;
	if(ch=='d') return 4;
	return 0;
}

void Min(ll &x,ll y){
	if(x==-1) x=y;
	else x=min(x,y);
}

int main(){
	int n;scanf("%d%s",&n,lx+1);
	fr(i,1,n) scanf("%lld",&a[i]);
	memset(dp,-1,sizeof dp);
	dp[0][0]=0;
	fr(i,1,n) fr(j,0,4){
		if(dp[i-1][j]==-1) continue;
		int pos=get(lx[i]);
		if(pos) {
			if(pos==j+1) Min(dp[i][j+1],dp[i-1][j]),Min(dp[i][j],dp[i-1][j]+a[i]);
			 else Min(dp[i][j],dp[i-1][j]);
		} else Min(dp[i][j],dp[i-1][j]);
	}
	ll maxn=1e18;
	fr(i,0,3) if(dp[n][i]!=-1) maxn=min(maxn,dp[n][i]);
	cout<<maxn<<endl;
	return 0;
}