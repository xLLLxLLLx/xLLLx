#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int mod=1e9+7,N=2e5+10;
LL f[N][3],k[5];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

int zh(int x){
	x=max(0,x);
	return x;
}

int main(){
	int n,l,r;cin>>n>>l>>r;
	f[0][0]=1;
	k[0]=r/3-(l-1)/3;k[1]=(r+2)/3-(l+1)/3;k[2]=(r+1)/3-l/3;
	fr(i,1,n)
	 fr(j,0,2)
	  fr(t,0,2){
	 	Add(f[i][(j+t)%3],mul(k[t],f[i-1][j]));
	 }
	printf("%lld\n",f[n][0]);
	return 0;
}
