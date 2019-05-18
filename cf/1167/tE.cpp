#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
ll f[N],a[N];

int main(){
	int n,x;scanf("%d%d",&n,&x);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
	}
	fr(i,1,x+1) {
		f[i]=i;
	}
	ll maxn=0;
	fr(i,1,n) {
		if(maxn>a[i]) {
			f[1]=max(f[1],a[i]);
			f[a[i]+1]=max(f[a[i]+1],maxn);
		} else {
			maxn=a[i];
		}
	}
	ll pos=a[n],r=x;
	rf(i,n-1,1) {
		if(pos<a[i]) {
			r=min(r,a[i]);
		} else {
			pos=min(pos,a[i]);
		}
	}
	ll ans=0;
	// fr(i,1,x) printf("%lld\n",f[i]);
	// printf("%lld\n",r);
	ll j=0;
	for(int i=1;i<=r;++i) {
		j=max(j,f[i]);
		ans+=x-j+1;
	}
	printf("%lld\n",ans);
	return 0;
}