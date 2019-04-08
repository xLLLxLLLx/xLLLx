#include<bits/stdc++.h>
#define lson (x<<1)
#define rson (x<<1|1)
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
const LL inf=1e18;
LL sum[N],tag[N],a[N],k[N],b[N],c[N];

template <class T>
void read(T &x){
	char ch=getchar();x=0;bool t=0;
	for(;ch<'0'||ch>'9';ch=getchar()) t|=(ch=='-');
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	if(t) x=-x;
}

void up(int x){
	sum[x]=sum[ls]+sum[rs];
}

void cal(int x,int l,int r,LL tt){
	if(tt==-inf) return ;
	sum[x]+=c[r]-c[l-1]+(r-l+1)*tt;
	tag[x]=tt;
}

void down(int x,int l,int r){
	if(tag[x]==-inf||l==r) return ;
	int mid=(l+r)>>1;
	cal(lson,l,mid,tag[x]);
	cal(rson,mid+1,r,tag[x]);
	tag[x]=-inf;
}

void build(int x,int l,int r){
	tag[x]=-inf;
	if(l==r){
		sum[x]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	up(x);
}

void update(int x,int l,int r,int L,int R,LL tt){

}

LL Ask(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return sum[x];
	int mid=(l+r)>>1;
	down(x);
	LL ans1=0,ans2=0;
	if(L<=mid) ans1=Ask(lson,l,mid,L,R);
	if(R>mid) ans2=Ask(rson,mid+1,r,L,R);
	return ans1+ans2;
}

char lx[2];

int main(){
	int n;read(n);
	fr(i,1,n) read(a[i]);
	fr(i,1,n) b[i]=b[i-1]+a[i];
	fr(i,1,n) c[i]=c[i-1]+b[i];
	build(1,1,n);
	fr(i,2,n) read(k[i]);
	int q;read(q);
	fr(o,1,q){
		scanf("%s",lx+1);
		int l,r;read(l),read(r);
		if(lx[1]=='+'){
			int ans=0;
			while(l<=r){
				/**/
			}
		} else printf("%lld\n",Ask(1,1,n,l,r));
	}
	return 0;
}