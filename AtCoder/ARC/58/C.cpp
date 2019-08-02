#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=41,MK=(1<<17),mod=1e9+7;
LL dp[N][MK];

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

int main(){
	int n,x,y,z;scanf("%d%d%d%d",&n,&x,&y,&z);
	int wr=(1<<(x-1))|(1<<(x+y-1))|(1<<(x+y+z-1));
	dp[0][0]=1;
	int mk=(1<<(x+y+z))-1;
	LL ans=1;
	fr(i,1,n) Mul(ans,10);
	fr(i,1,n) fr(j,0,mk){
		if(!dp[i-1][j]) continue;
		fr(k,1,10){
			int now=(j<<k)|(1<<(k-1));
			now&=mk;
			//printf("%d\n",now);
			if((now&wr)==wr) continue;
			else Add(dp[i][now],dp[i-1][j]);
		}
	}
	//fr(i,0,mk) printf("%lld\n",dp[n][i]);
	fr(i,0,mk) Add(ans,add(mod,-dp[n][i]));
	printf("%lld\n",ans);
	return 0;
}