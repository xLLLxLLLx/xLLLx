#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=401;
int dp[N][N][N],a[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n) fr(j,i+1,n) dp[i][j][0]=a[j]-a[i];
	fr(i,1,n) fr(j,i+1,n){
		int w=i;
		fr(k,1,n){
			while(w+1<=n&&max(dp[i][w+1][k-1],a[j]-a[w+1])<max(dp[i][w][k-1],a[j]-a[w])) w++;
			dp[i][j][k]=max(dp[i][w][k-1],a[j]-a[w]);
		}
	}
	LL maxn=0;
	fr(o,1,m){
		int s,t,c,r;scanf("%d%d%d%d",&s,&t,&c,&r);
		maxn=max(maxn,(dp[s][t][r]*1LL*c));
	}
	printf("%lld\n",maxn);
	return 0;
}