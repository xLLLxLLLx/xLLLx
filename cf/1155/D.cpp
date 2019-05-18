#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define db double
using namespace std;
const int N=3e5+10;
ll a[N],dp[N][2][2];

int main(){
	int n;ll x;
	cin>>n>>x;
	fr(i,1,n) cin>>a[i];
	ll maxn=0;
	fr(i,1,n){
		fr(j,0,1) fr(k,0,1){
			if(j&&k) continue;

		}
		dp[i][0][1]=max(dp[i][0][1],max(dp[i-1][0][0],dp[i-1][0][1])+a[i]*x);
		dp[i][0][0]=max(dp[i][0][0],dp[i-1][0][0]+a[i]);
		dp[i][1][0]=max(dp[i][1][0],max(dp[i-1][1][0],dp[i-1][0][1])+a[i]);
		fr(j,0,1) fr(k,0,1) maxn=max(maxn,dp[i][j][k]);
	}
	cout<<maxn<<endl;
	return 0;
}