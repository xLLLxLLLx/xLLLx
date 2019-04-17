#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls x<<1
#define rs x<<1|1
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
	int v,id;
}tr[N<<2];
struct node{
	LL mx,mn;
}seg[N<<2];
int n;
LL d[N],c[N],qz[N],a,maxn=0;

data up(data A,data B){
	data C;
	C.v=max(A.v,B.v);
	if(A.v>B.v) C.id=A.id;
	else C.id=B.id;
	return C;
}

node merge(node A,node B){
	node C;
	C.mx=max(A.mx,B.mx);
	C.mn=min(A.mn,B.mn);
	return C;
}

void insert(int x,int l,int r,int v,int L){
	if(l==r){
		tr[x]=(data){v,L};
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) insert(ls,l,mid,v,L);
	else insert(rs,mid+1,r,v,L);
	tr[x]=up(tr[ls],tr[rs]);
}

void change(int x,int l,int r,LL v,int L){
	if(l==r){
		seg[x]=(node){v,v};
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(ls,l,mid,v,L);
	else change(rs,mid+1,r,v,L);
	seg[x]=merge(seg[ls],seg[rs]);
}

node Ask(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return seg[x];
	int mid=(l+r)>>1;
	if(R<=mid) return Ask(ls,l,mid,L,R);
	else if(L>mid) return Ask(rs,mid+1,r,L,R);
	else {
		node tmp=Ask(ls,l,mid,L,R),pos=Ask(rs,mid+1,r,L,R);
		return merge(tmp,pos);
	}
}

data Get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tr[x];
	int mid=(l+r)>>1;
	if(R<=mid) return Get(ls,l,mid,L,R);
	else if(L>mid) return Get(rs,mid+1,r,L,R);
	else {
		data tmp=Get(ls,l,mid,L,R),pos=Get(rs,mid+1,r,L,R);
		return up(tmp,pos);
	}
}

LL pf(LL x){
	return x*x;
}

void work(int l,int r){
	if(l==r) {maxn=max(maxn,c[l]);return ;}
	data gg=Get(1,1,n,l+1,r);
	maxn=max(maxn,Ask(1,1,n+1,gg.id+1,r+1).mx-Ask(1,1,n+1,l,gg.id-1).mn-pf(gg.v));
	work(l,gg.id-1),work(gg.id,r);
}

int main(){
	scanf("%d%lld",&n,&a);
	fr(i,1,n) scanf("%lld%lld",&d[i],&c[i]),c[i]=a-c[i],maxn=max(maxn,c[i]);
	fr(i,1,n) qz[i]=qz[i-1]+c[i];
	fr(i,0,n) change(1,1,n+1,qz[i],i+1);
	fr(i,2,n) insert(1,1,n,d[i]-d[i-1],i);
	work(1,n);
	printf("%lld\n",maxn);
	return 0;
}