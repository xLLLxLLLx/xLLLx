#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=110;
int a[N];

int main(){
	int n,d;
	scanf("%d%d",&n,&d);
	fr(i,1,n) {
		scanf("%d",&a[i]);
	}
	ll ans=2;
	fr(i,1,n-1) {
		ll dis=a[i+1]-a[i];
		if(dis==2*d) ans++;
		else if(dis>2*d) ans+=2;
	}
	printf("%lld\n",ans);
	return 0;
}