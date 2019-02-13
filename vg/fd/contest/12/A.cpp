#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=102,mod=1e9+7;
struct data {
	LL a[N][N];
}tmp,pos;
LL cnt[N],dp[N];

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

data C(data x,data y){
	data z;
	fr(i,1,101) fr(j,1,101){
		z.a[i][j]=0;
		fr(k,1,101) Add(z.a[i][j],mul(x.a[i][k],y.a[k][j]));
	}
	return z;
}

void q_pow(int y){
	fr(i,1,101) pos.a[i][i]=1;
	for(;y;y>>=1) {
		if(y&1) pos=C(pos,tmp);
		tmp=C(tmp,tmp);
	}
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) {
		int x;scanf("%d",&x);
		cnt[x]++;
	}
	dp[0]=1;
	fr(i,1,100) fr(j,1,i)
	 	Add(dp[i],mul(dp[i-j],cnt[j]));
	if(k<=100) {
		fr(i,1,k) Add(dp[101],dp[i]);
		Add(dp[101],1);
		printf("%lld\n",dp[101]);
		return 0;
	}
	fr(i,1,100) Add(dp[101],dp[i]);
	fr(i,1,99) tmp.a[i+1][i]=1;
	fr(i,1,100) tmp.a[i][100]=tmp.a[i][101]=cnt[101-i];
	tmp.a[101][101]=1;
/*	fr(i,1,101) {
		fr(j,1,101) printf("%lld ",tmp.a[i][j]);
		printf("\n");
	}*/
	LL ans=0;
	q_pow(k-100);
	fr(i,1,101) Add(ans,mul(dp[i],pos.a[i][101]));
	Add(ans,1);
	printf("%lld\n",ans);
	return 0;
}
