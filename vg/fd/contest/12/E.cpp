#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
const int N=1e5+10;
using namespace std;
struct data{
	int d[6];
}a[N],v[N<<2],gg;
int n,m,k;

void build(int x,int l,int r){
	if(l==r){
		fr(i,1,m) v[x].d[i]=a[l].d[i];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	fr(i,1,m) v[x].d[i]=max(v[lson].d[i],v[rson].d[i]);
}

data find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	int mid=(l+r)>>1;
	if(R<=mid) return find(lson,l,mid,L,R);
	else if(L>mid) return find(rson,mid+1,r,L,R);
	else {
		data tmp=find(lson,l,mid,L,R),pos=find(rson,mid+1,r,L,R);
		data zz;
		fr(i,1,m) zz.d[i]=max(tmp.d[i],pos.d[i]);
		return zz;
	}
}

bool check(int L,int R){
	data zz=find(1,1,n,L,R);
	int tot=0;
	fr(i,1,m) tot+=zz.d[i];
	return tot<=k;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	fr(i,1,n) fr(j,1,m) scanf("%d",&a[i].d[j]);
	build(1,1,n);
	int ans=0;
	fr(i,1,n){
		int l=i,r=n,da=i-1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(check(i,mid)) l=mid+1,da=mid;
			else r=mid-1;
		}
		if(da!=i-1&&da-i+1>ans) {
			gg=find(1,1,n,i,da);
			ans=da-i+1;
		}
	}
	fr(i,1,m) printf("%d ",gg.d[i]);
	return 0;
}
