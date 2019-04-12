#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int yz[N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	LL ans=0;
	LL gg=n/k;
	ans=gg*gg*gg;
	if(k%2==0){
		LL pos=n/k;
		if(pos*k+(k/2)<=n) pos++;
		ans+=pos*pos*pos;
	}
	printf("%lld\n",ans);
	return 0;
}