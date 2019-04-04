#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
LL maxn=0,minn=1e18;
LL tot;

LL gcd(LL a,LL b){
	return b?gcd(b,a%b):a;
}

void js(LL x){
	if(x<=0||x>tot) return ;
//	printf("%lld\n",x);
	LL gg=gcd(x,tot);
	LL tmp=tot/gg;
	maxn=max(maxn,tmp);
	minn=min(minn,tmp);
}

int main(){
	LL n,k;cin>>n>>k;
	LL a,b;cin>>a>>b;
	tot=n*k;
	fr(i,0,n+1){
		js(i*k+(a+b));
		js(i*k-(a+b));
		js(i*k+(a-b));
		js(i*k+(b-a));
	}
	printf("%lld %lld\n",minn,maxn);
	return 0;
}