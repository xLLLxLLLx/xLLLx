#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
LL a[N],b[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%lld",&a[i]);
	LL sum=0;
	fr(i,1,m){
		int tp,x,y;LL w;
		scanf("%d",&tp);
		if(tp==1){
			scanf("%d%lld",&x,&w);
			b[x]=sum,a[x]=w;
		}
		else if(tp==2){
			scanf("%lld",&w);
			sum+=w;
		}
		else {
			scanf("%d",&x);
			LL pos=sum-b[x]+a[x];
			printf("%lld\n",pos);
		}
	}
	return 0;
}
