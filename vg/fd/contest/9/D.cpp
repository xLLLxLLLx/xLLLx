#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010,mod=1e9+7;
LL f[N][N];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y+mod)%mod;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,2,m) f[1][i]=1;
	fr(i,2,n) {
		LL qz=0;
		fr(j,2,m) {
			Add(qz,f[i-1][j]);
			if(j==2) f[i][j]=add(f[i-1][j],1);
			else f[i][j]=add(qz,f[i][j-1]);
		}
	}
	//fr(i,1,n) fr(j,2,m) printf("%d %d %lld\n",i,j,f[i][j]);
	LL ans=0;
	fr(i,1,n) fr(j,2,m){
		Add(ans,mul(mul(add(f[i][j],-f[i-1][j]),f[n-i+1][j]),m-j+1));
	}
	printf("%lld\n",ans);
	return 0;
}
