#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
ll a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
	}
	if(n==1) return printf("%lld\n",a[1]),0;
	sort(a+1,a+1+n);
	ll ans=a[n]-a[1];
	fr(i,2,n-1) ans+=max(a[i],-a[i]);
	printf("%lld\n",ans);
	return 0;
}