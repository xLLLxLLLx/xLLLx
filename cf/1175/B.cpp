#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
const ll inf=(1ll<<32)-1;
char lx[N];
ll a[N],b[N];

long double mul(long double x,long double y){
	return x*y;
}

long double add(long double x,long double y){
	return x+y;
}

void fail(){
	printf("OVERFLOW!!!\n");
	exit(0);
}

void Add(ll &x,ll y){
	if(add(x,y)>inf) fail();
	x+=y;
}

void Mul(ll &x,ll y){
	if(mul(x,y)>inf) fail();
	x*=y;
}

int main(){
	ll ans=0;
	int n;scanf("%d",&n);
	int now=0;
	ll pos=0;
	int flg=0,ff=1;
	fr(i,1,n) {
		scanf("%s",lx+1);
		if(lx[1]=='a') {
			if(!now) Add(ans,ff);
			else b[now]++;
		} else if(lx[1]=='f') {
			scanf("%lld",&a[++now]);
		} else {
			Mul(pos,a[now]),Add(pos,a[now]*b[now]);
			a[now]=b[now]=0;
			now--;
			if(!now) Add(ans,pos),pos=0,flg=0;
		}
	}
	printf("%lld\n",ans);
	return 0;
}