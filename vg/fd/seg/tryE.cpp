#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x); cout<<#x<<"="<<x<<endl;
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int vis[N<<2];
LL v[N<<2][2];
struct data{
	LL a[2][2];
}lz[N<<2];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

data mu(data x,data y){
	data tmp;
	fr(i,0,1) fr(j,0,1) {
		tmp.a[i][j]=0;
		fr(k,0,1) Add(tmp.a[i][j],mul(x.a[i][k],y.a[k][j]));
	}
	return tmp;
}

data jz(data x,int y){
	data tmp;
	fr(i,0,1) fr(j,0,1) tmp.a[i][j]=(i==j);
	for(;y;y>>=1){
		if(y&1) tmp=mu(tmp,x);
		x=mu(x,x);
	}
	return tmp;
}

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void pushup(int x){
	v[x][0]=add(v[lson][0],v[rson][0]);
	v[x][1]=add(v[lson][1],v[rson][1]);
}

void build(int x,int l,int r){
	if(l==r){v[x][0]=1,v[x][1]=0;return ;}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	pushup(x);
}

void Get(int x,data A){
	if(!vis[x]) lz[x]=A,vis[x]=1;
	else lz[x]=mu(lz[x],A);
}

void pushdown(int x,int z){
	if(!vis[x]) return ;
	data A;vis[x]=0;
	A.a[0][0]=v[x][0],A.a[1][0]=v[x][1];
	A=mu(lz[x],A);
	v[x][0]=A.a[0][0],v[x][1]=A.a[1][0];
	if(z) return ;
	if(vis[lson]) lz[lson]=mu(lz[lson],lz[x]);
	else vis[lson]=1,lz[lson]=lz[x];
	if(vis[rson]) lz[rson]=mu(lz[rson],lz[x]);
	else vis[rson]=1,lz[rson]=lz[x];
}

void change(int x,int l,int r,data A,int L,int R){
	if(L<=l&&r<=R) {
		Get(x,A),pushdown(x,l==r);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l==r);
	if(L<=mid) change(lson,l,mid,A,L,R);
	else pushdown(lson,l==mid);
	if(R>mid) change(rson,mid+1,r,A,L,R);
	else pushdown(rson,(mid+1==r));
	pushup(x);
}

LL find(int x,int l,int r,int L,int R){
	pushdown(x,l==r);
	if(L<=l&&r<=R) return v[x][1];
	int mid=(l+r)>>1;
	LL ans1=0,ans2=0;
	if(L<=mid) ans1=find(lson,l,mid,L,R);
	if(R>mid) ans2=find(rson,mid+1,r,L,R);
	return add(ans1,ans2);
}

int main(){
	int n,m;read(n),read(m);
	build(1,1,n);
	data cs;
	cs.a[0][0]=1,cs.a[0][1]=1;
	cs.a[1][0]=1,cs.a[1][1]=0;
	fr(i,1,n) {
		int x;read(x);
		data A=jz(cs,x);
		change(1,1,n,A,i,i);
	}
	fr(i,1,m){
		int x,y,z;read(x),read(y),read(z);
		if(x==2) printf("%lld\n",find(1,1,n,y,z));
		else {
			read(x);
			data A=jz(cs,x);
			change(1,1,n,A,y,z);
		}
	}
	return 0;
}
