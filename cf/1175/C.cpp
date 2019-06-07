#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
ll a[N];

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T) {
		int n,k;
		scanf("%d%d",&n,&k);
		fr(i,1,n) {
			scanf("%lld",&a[i]);
		}
		if(!k) printf("%d\n",a[1]);
		else {
			k++;
			int maxn=1e9,ans=0;
			fr(i,1,n-k+1) {
				int pos=(a[i]+a[i+k-1])/2;
				int tmp=max(abs(pos-a[i]),abs(pos-a[i+k-1]));
				if(tmp<maxn) maxn=tmp,ans=pos;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}