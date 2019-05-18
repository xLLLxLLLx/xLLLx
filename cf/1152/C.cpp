#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
using namespace std;
ll n,m,maxn,res,dis;

ll gcd(ll a,ll b){
	return b ? gcd(b,a%b) : a;
}

ll get(ll k){
	return (n+k)*(m+k)/gcd(n+k,m+k);
}

void cal(ll x){
	//printf("%lld\n",x);
	ll add=x-n%x;
	//printf("add=%lld\n",add);
	ll gg=get(add);
	if(maxn>gg) maxn=gg,res=add;
}

int main(){
	ll a,b;cin>>a>>b;
	n=a,m=b;
	dis=a-b;
	if(dis<0) dis=-dis;
	ll pos=gcd(a,b);
	ll len=sqrt(dis);
	maxn=a*b/pos,res=0;
	fr(i,1,len){
		if(dis%i) continue;
		cal(i),cal(dis/i);
	}
	cout<<res<<endl;
	return 0;
}