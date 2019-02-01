#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int a[N];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;	
}

int main(){
	int n,maxn;scanf("%d%d",&n,&maxn);
	fr(i,1,n) scanf("%d",&a[i]);
	
	printf("%lld\n",ans);
	return 0;
}
