#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5010,mod=998244353;
int a[N],cnt[N],all[N];
ll dp[N][N],jc[N];

void Add(ll &x,ll y){
	x=(x+y)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return (x+y)%mod;
}

ll mul(ll x,ll y){
	return (x*y)%mod;
}

ll q_pow(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
	sort(all+1,all+1+n);
	int m=unique(all+1,all+1+n)-all-1;
	fr(i,1,n) a[i]=lower_bound(all+1,all+1+m,a[i])-all,cnt[a[i]]++;
	dp[0][0]=1;
	fr(i,1,m){
		dp[i][0]=1;
		fr(j,1,i){
			dp[i][j]=add(dp[i-1][j],mul(dp[i-1][j-1],cnt[i]));
		}
	}
	jc[0]=1;
	fr(i,1,n) jc[i]=mul(jc[i-1],i);
	//fr(i,1,m) fr(j,0,i) printf("dp[%d][%d]=%lld\n",i,j,dp[i][j]);
	ll ans=0;
	fr(i,1,m){
		if(cnt[i]<2) continue;
		ll tmp=mul(cnt[i],cnt[i]-1);
		fr(j,0,i-1) Add(ans,mul(mul(dp[i-1][j],tmp),jc[n-(j+2)]));
	}
	ll pos=1;
	fr(i,1,n) Mul(pos,i);
	Mul(ans,q_pow(pos,mod-2));
	printf("%lld\n",ans);
	return 0;
}