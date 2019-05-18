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
const int N=2e5+10;
ll a[N];

int find(int l,int r,ll x){
	int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
		if(a[i]<0) a[i]=-a[i];
	}
	sort(a+1,a+1+n);
	ll ans=0;
	fr(i,1,n){
		int pos=find(i+1,n,a[i]*2ll);
		if(pos) ans+=pos-i;
	}
	printf("%lld\n",ans);
	return 0;
}