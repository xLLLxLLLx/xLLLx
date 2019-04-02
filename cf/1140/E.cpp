#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10,mod=998244353;
LL dp[N];
int a[N],b[N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

int main(){
	int n;LL k;
	scanf("%d%lld",&n,&k);
	fr(i,1,n) scanf("%d",&a[i]);
	int zz,pre;LL pos=0,tmp=0;
	if(a[1]<0) dp[1]=1,zz=1,pos=1;
	else dp[1]=0,zz=a[1],pos=1;
	for(int i=3;i<=n;i+=2){
		if(a[i]<0){
			dp[i]=add(mul(k-2,dp[i-2]),pos);
			pos=mul(k-1,dp[i-2]);
		} else {
			if(zz==a[i]) pos=mul(k-1,dp[i-2]);
				else pos=add(mul(k-2,dp[i-2]),pos);
			zz=a[i];
		}
	//	printf("%d %lld %lld\n",i,pos,dp[i]);
	}
	if(a[2]<0) dp[2]=1,pre=1,tmp=1;
	else dp[2]=0,pre=a[2],tmp=1;
	for(int i=4;i<=n;i+=2){
		if(a[i]<0){
			dp[i]=add(mul(k-2,dp[i-2]),tmp);
			tmp=mul(k-1,dp[i-2]);
		} else {
			if(pre==a[i]) tmp=mul(k-1,dp[i-2]);
				else tmp=add(mul(k-2,dp[i-2]),tmp);
			pre=a[i];
		}
	}
//	cout<<dp[n]<<" "<<dp[n-1]<<" "<<pos<<" "<<tmp<<endl;
	if(n&1) printf("%lld\n",mul(add(pos,mul(k-1,dp[n])),add(tmp,mul(k-1,dp[n-1])))); 
		else printf("%lld\n",mul(add(pos,mul(k-1,dp[n-1])),add(tmp,mul(k-1,dp[n]))));
	return 0;
}