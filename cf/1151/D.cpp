#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
LL a[N];

int main(){
	LL ans=0;
	int n;scanf("%d",&n);
	fr(i,1,n) {
		LL x,y;
		scanf("%lld%lld",&x,&y);
		ans+=y*((n-1)*1LL);
		a[i]=x-y;
	}
	sort(a+1,a+1+n);
	fr(i,1,n) ans+=a[n-i+1]*(1LL*(i-1));
	printf("%lld\n",ans);
	return 0;
}