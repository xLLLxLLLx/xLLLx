#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10,LOG=63;
int mk[N];
ll sum[N],a[N],pw[LOG]={1};

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	fr(i,1,LOG-1) pw[i]=pw[i-1]*2;
	fr(i,1,n) {
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]^a[i];
	}
	ll ans=0;
	rf(i,62,0) {
		int res=0;
		fr(j,1,n) {
			if(!mk[j]&&!(sum[j]&pw[i])) res++;
		}
		if(res>=m&&!(sum[n]&pw[i])) {
			fr(j,1,n) {
				if(sum[j]&pw[i]) mk[j]=1;
			}
		} else ans|=pw[i];
	}
	printf("%lld\n",ans);
	return 0;
}