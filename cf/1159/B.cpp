#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
struct data{
	ll w,id;
}a[N],b[N];

bool cmp(data A,data B){
	return A.w>B.w;
}

ll js(ll x,ll y){
	return x/y;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i].w),a[i].id=i;
	sort(a+1,a+1+n,cmp);
	ll ans=1e18,pos=a[1].id,tmp=a[1].id;
	int res=0;
	fr(i,1,n){
		if(a[i].w!=a[i-1].w){
			fr(j,1,res) pos=max(pos,b[j].id),tmp=min(tmp,b[j].id);
			fr(j,1,res) if(pos>b[j].id) ans=min(ans,js(b[j].w,pos-b[j].id));
			fr(j,1,res) if(tmp<b[j].id) ans=min(ans,js(b[j].w,b[j].id-tmp));
			res=0,b[++res]=a[i];
		} else b[++res]=a[i];
		pos=max(pos,a[i].id);
		tmp=min(tmp,a[i].id);
	}
	fr(j,1,res) pos=max(pos,b[j].id),tmp=min(tmp,b[j].id);
	fr(j,1,res) if(pos>b[j].id) ans=min(ans,js(b[j].w,pos-b[j].id));
	fr(j,1,res) if(tmp<b[j].id) ans=min(ans,js(b[j].w,b[j].id-tmp));
	if(ans==1e18) ans=0;
	printf("%lld\n",ans);
	return 0;
}