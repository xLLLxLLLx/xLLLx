#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	LL w;
	int rk;
}a[N];
int n;
LL A,cf,cm,m;
LL qz[N],b[N];

bool cmp(data x,data y){
	return x.w>y.w;
}

LL check(LL x,int i){
	int l=i,r=n,ans=i-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid].w>=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return (x*(n-ans)-qz[n]+qz[ans]);
}

LL find(int i,LL k){
	LL l=0,r=A,ans=0;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid,i)<=k) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

int main(){
	scanf("%d%lld%lld%lld%lld",&n,&A,&cf,&cm,&m);
	fr(i,1,n) scanf("%lld",&a[i].w),a[i].rk=i;
	sort(a+1,a+1+n,cmp);
	fr(i,1,n) qz[i]=qz[i-1]+a[i].w;
	LL tmp=find(1,m),res=0;
	LL maxn=tmp*cm,k=m;
	fr(i,1,n){
		if(k>=A-a[i].w) {
			k-=(A-a[i].w);
			LL ans=find(i+1,k);
			LL pos=i*1LL*cf+cm*ans;
			if(maxn<pos){
				tmp=ans,res=i;
			}
			maxn=max(maxn,pos);
		}
		else break;
	}
	printf("%lld\n",maxn);
	fr(i,1,res) b[a[i].rk]=A;
	fr(i,res+1,n) b[a[i].rk]=max(tmp,a[i].w);
	fr(i,1,n) printf("%lld ",b[i]);
	return 0;
}
