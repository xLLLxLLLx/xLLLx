#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
const ll inf=(1ll<<32);
char lx[N];
ll a[N];

int main(){
	int n;scanf("%d",&n);
	ll ans=0;
	int now=0;a[0]=1;
	fr(i,1,n) {
		scanf("%s",lx+1);
		if(lx[1]=='a') {
			ans+=a[now];
		} else if(lx[1]=='e') {
			a[now]=0,now--;
		} else {
			ll x;scanf("%lld",&x);
			a[now+1]=min(inf,a[now]*x);
			now++;
		}
	}
	if(ans>=inf) printf("OVERFLOW!!!\n");
	else printf("%lld\n",ans);
	return 0;
}