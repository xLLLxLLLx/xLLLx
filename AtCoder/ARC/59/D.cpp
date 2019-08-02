#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010,mod=1e9+7;
char lx[N];
LL dp[N][N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL q_pow(LL x,int y=mod-2){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

int main(){
	int k;scanf("%d",&k);
	scanf("%s",lx+1);
	int n=strlen(lx+1);
	dp[0][0]=1;
	fr(i,1,k) fr(j,0,i){
		if(j) Add(dp[i][j],mul(dp[i-1][j-1],2));
		else Add(dp[i][j],dp[i-1][j]);
		Add(dp[i][j],dp[i-1][j+1]);
		//printf("%d %d %lld\n",i,j,dp[i][j]);
	}
	LL pos=1;
	fr(i,1,n) Mul(pos,2);
	LL ans=mul(dp[k][n],q_pow(pos));
	cout<<ans<<endl;
	return 0;
}