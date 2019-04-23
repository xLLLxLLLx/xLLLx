#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10,mod=998244353;
ll jc[N]={1},ny[N]={1};
int a[N],tr[N];

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

int lower(int x){
	return x&(-x);
}

void insert(int x,int k){
	for(;x<N;x+=lower(x)) tr[x]+=k;
}

int Get(int x){
	int ans=0;
	for(;x;x-=lower(x)) ans+=tr[x];
	return ans;
}

ll A(int x,int y){
	if(x<y) return 0ll;
	return mul(jc[x],ny[x-y]);
}

int main(){
	int n;scanf("%d",&n);
	int res=0;
	ll ans=0;
	fr(i,1,n) jc[i]=mul(jc[i-1],i),ny[i]=q_pow(jc[i],mod-2);
	fr(i,1,n){
		scanf("%d",&a[i]);
		if(a[i]==-1) res++;
		else {
			Add(ans,i-1-res-Get(a[i]));
			insert(a[i],1);
		}
	}
	if(res) Add(ans,mul(mul(res,res-1),q_pow(4,mod-2)));
	int gg=0;
	ll bas=q_pow(res,mod-2);
	fr(i,1,n){
		if(a[i]==-1) gg++;
		else {
		 	int pos=Get(a[i]-1);
		 	int tmp=a[i]-1-pos;
		 	Add(ans,mul(gg,mul(res-tmp,bas)));
		 	Add(ans,mul(res-gg,mul(tmp,bas)));
		}
	}
	printf("%lld\n",ans);
	return 0;
}