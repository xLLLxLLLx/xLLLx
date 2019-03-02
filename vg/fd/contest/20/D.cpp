#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010,mod=1e9+7;
LL f[N][N],dp[N][N],jc[N]={1};

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

void init(){
	fr(i,0,N-1) f[i][0]=f[i][i]=1;
	fr(i,1,N-1) fr(j,1,i-1)
		f[i][j]=add(f[i-1][j],f[i-1][j-1]);
}

int main(){
	init();
	int t;scanf("%d",&t);
	dp[1][1]=1;
	fr(i,1,1000) fr(j,1,i) {
		if(j) Add(dp[i][j],dp[i-j+1][j-1]);
		Add(dp[i][j],dp[i-j][j]);
	}
	fr(i,1,1000) jc[i]=mul(jc[i-1],i);
	fr(i,1,1000) fr(j,1,1000) {
		Mul(dp[i][j],jc[j]);
	}
	fr(o,1,t){
		int n,k;scanf("%d%d",&n,&k);
		LL ans=0;
		fr(i,k,n){
			int yu=n-i+1;
			Add(ans,mul(dp[i][k],f[yu][k]));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
