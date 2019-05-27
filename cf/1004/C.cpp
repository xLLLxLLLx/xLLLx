#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
int a[N],mk[N],vs[N];

int main(){
	int n;scanf("%d",&n);
	ll pos=0,tmp=0;
	fr(i,1,n) {
		scanf("%d",&a[i]);
		if(!mk[a[i]]) tmp++;
		mk[a[i]]++;
	}
	ll ans=0;
	fr(i,1,n-1) {
		ll res=0,cnt=0;
		mk[a[i]]--;
		if(!vs[a[i]]) res++,pos++;
		if(!mk[a[i]]) cnt++,tmp--;
		vs[a[i]]++;
		if(res) {
			ans+=tmp;
		}
	}
	printf("%lld\n",ans);
	return 0;
}