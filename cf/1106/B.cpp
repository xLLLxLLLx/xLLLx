#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
LL a[N],b[N];

LL pf(LL x){
	return x*x;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	if(n&1) {
		int res=0;
		LL ans=0;
		b[++res]=a[1]+a[2];
		fr(i,3,n) b[++res]=a[i];
		fr(i,1,res/2){
			ans+=pf(a[i]+a[n-i+1]);
		}
		printf("%lld\n",ans);
	} else {
		LL ans=0;
		fr(i,1,n/2) {
			ans+=pf(a[i]+a[n-i+1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
