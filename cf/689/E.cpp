#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=4e5+10,mod=1e9+7;
struct data{
	ll l,r;
}a[N];
ll all[N],c[N],jc[N]={1},rev[N]={1};

void Add(ll &x,ll y){
	x=(x+y)%mod;
}

void Mul(ll &x,ll y){
	x=(x*y)%mod;
}

ll add(ll x,ll y){
	return (x+y)%mod;
}

ll mul(ll x,ll y){
	return x*y%mod;
}

ll q_pow(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

ll C(int x,int y){
	return mul(mul(rev[y],rev[x-y]),jc[x]);
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,N-1) jc[i]=mul(jc[i-1],i),rev[i]=q_pow(jc[i],mod-2);
	int res=0;
	fr(i,1,n){
		scanf("%lld%lld",&a[i].l,&a[i].r);
		a[i].r++;
		all[++res]=a[i].l,all[++res]=a[i].r;
	}
	sort(all+1,all+1+res);
	int m=unique(all+1,all+1+res)-all-1;
	fr(i,1,n){
		int L=lower_bound(all+1,all+1+m,a[i].l)-all;
		int R=lower_bound(all+1,all+1+m,a[i].r)-all;
		c[L]++,c[R]--;
	}
	fr(i,1,m) c[i]+=c[i-1];
	// fr(i,1,m){
	// 	printf("zz%lld %lld\n",all[i],c[i]);
	// }
	ll ans=0;
	fr(i,1,m-1){
		if(c[i]>=k) {
			Add(ans,mul(C(c[i],k),all[i+1]-all[i]));
			// printf("%lld C:%lld %lld %lld\n",c[i],C(c[i],k),all[i+1],all[i]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}