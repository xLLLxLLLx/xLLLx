#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

ll Abs(ll x){
	if(x<0) return -x;
	else return x;
}

int main(){
	int n;scanf("%d",&n);
	ll tmp=0,res=0,nw;
	scanf("%lld",&nw);
	fr(i,2,n){
		ll x;scanf("%lld",&x);
		nw-=x;
		if(nw<0) tmp-=nw;
		else res+=nw;
		nw=x;
	}
	printf("%lld\n%lld\n",max(tmp,res),Abs(res-tmp)+1);
	return 0;
}