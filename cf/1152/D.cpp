#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
using namespace std;

ll gcd(ll a,ll b){
	return b ? gcd(b,a%b) : a;
}

int main(){
	ll a,b;cin>>a>>b;
	ll maxn=1e18,res=0;
	if(maxn>a*b/gcd(a,b)) maxn=a*b/gcd(a,b),res=0;
	fr(i,1,100000){
		ll tmp=(a+i)*(b+i);
		ll pos=gcd(a+i,b+i);
		tmp/=pos;
		if(maxn>tmp) maxn=tmp,res=i;
	}
	cout<<maxn<<" "<<res<<endl;
	return 0;
}