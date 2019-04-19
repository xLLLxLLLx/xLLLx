#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
int n;
ll a[N];

ll cal(ll x,ll y){
	if(x>=y) return y*(x-y);
	else if(x<y) return (y-x)*(n-y+1);
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	ll ans=0;
	fr(i,0,n-1) ans+=cal(a[i],a[i+1]);
	cout<<ans<<endl;
	return 0;
}