#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define bug(x); cout<<#x<<"="<<x<<endl;
#define LL long long
using namespace std;
const int N=3e5+10,mod=1e9+9;
LL lz[N<<2][2],v[N<<2],a[N],f[N],qz[N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

void build(int x,int l,int r){
	if(l==r) { v[x]=a[l];return ; }
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	v[x]=add(v[lson],v[rson]);
}

LL js(LL A,LL B,LL nm){
	if(nm==1) return A;
	return add(mul(A,add(qz[nm-2],1)),mul(qz[nm-1],B));
}

LL get(LL A,LL B,LL nm){
	if(nm==1) return A;
	return add(mul(f[nm-1],B),mul(f[nm-2],A));
}

void Get(int x,int l,int r,int L,int R){
	Add(lz[x][0],f[l-L+1]);
	if(l+1<=r) Add(lz[x][1],f[l-L+2]);
}

void pushdown(int x,int l,int r){
	int mid=(l+r)>>1;
	if(!lz[x][0]&&!lz[x][1]) return ;
	Add(v[x],js(lz[x][0],lz[x][1],r-l+1));
	if(l==r) {
		lz[x][0]=lz[x][1]=0;
		return ;
	}
	Add(lz[lson][0],lz[x][0]);
	if(mid>l) Add(lz[lson][1],lz[x][1]);
	Add(lz[rson][0],get(lz[x][0],lz[x][1],mid+2-l));
	if(mid+1<r) Add(lz[rson][1],get(lz[x][0],lz[x][1],mid+3-l));
	lz[x][0]=lz[x][1]=0;
}

void change(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) {
		Get(x,l,r,L,R);
		pushdown(x,l,r);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if(L<=mid) change(lson,l,mid,L,R);
	if(R>mid) change(rson,mid+1,r,L,R);
	pushdown(lson,l,mid),pushdown(rson,mid+1,r);
	v[x]=add(v[lson],v[rson]);
}

LL find(int x,int l,int r,int L,int R){
	if(L>r||R<l) return 0LL;
	pushdown(x,l,r);
	if(L<=l&&r<=R) return v[x];
	int mid=(l+r)>>1;
	return add(find(lson,l,mid,L,R),find(rson,mid+1,r,L,R));
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%lld",&a[i]);
	build(1,1,n);
	f[1]=1,f[2]=1;
	fr(i,3,n) f[i]=add(f[i-1],f[i-2]);
	fr(i,1,n) qz[i]=add(qz[i-1],f[i]);
	fr(i,1,m){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(x==1) change(1,1,n,y,z);
		else printf("%lld\n",find(1,1,n,y,z));
	}
	return 0;
}
