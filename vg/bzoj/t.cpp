#include<iostream>
#include<cstdio>
#define ll long long
#define N 500005
using namespace std;
 
int n,m,tsh_cnt,pos[N],val[N],tsh[N]; bool flag;
struct node{ int l,r; }; ll id[N],inf=(ll)4611686018427387904;
bool operator <(node x,node y){
	return id[x.l]<id[y.l] || id[x.l]==id[y.l] && id[x.r]<id[y.r];
}
bool operator ==(node x,node y){
	return id[x.l]==id[y.l] && id[x.r]==id[y.r];
}
struct scp_node{
	int trtot,rt,ls[N],rs[N],sz[N]; node nd[N];
	void del(int k){
		if (ls[k]) del(ls[k]); tsh[++tsh_cnt]=k; if (rs[k]) del(rs[k]);
	}
	void build(int &k,int x,int y,ll l,ll r){
		int z=(x+y)>>1; ll mid=(l+r)>>1;
		k=tsh[z]; id[k]=mid; sz[k]=1;
		if (x<z) build(ls[k],x,z-1,l,mid); else ls[k]=0;
		if (z<y) build(rs[k],z+1,y,mid,r); else rs[k]=0;
		sz[k]=sz[ls[k]]+sz[rs[k]];
	}
	void rebuild(int &k,ll l,ll r){
		tsh_cnt=0; del(k); build(k,1,tsh_cnt,l,r);
	}
	int ins(int &k,ll l,ll r,node x){
		ll mid=(l+r)>>1;
		if (!k){
			k=++trtot; sz[k]=1; id[k]=mid;
			nd[k]=x; return k;
		}
		if (x==nd[k]) return k; else{
			sz[k]++;
			int t=(x<nd[k])?ins(ls[k],l,mid,x):ins(rs[k],mid,r,x);
			if (sz[k]*0.77>max(sz[ls[k]],sz[rs[k]])){
				if (flag)
					if (x<nd[k]) rebuild(ls[k],l,mid); else rebuild(rs[k],mid,r);
				flag=0;
			} else flag=1;
			return t;
		}
	}
}scp;
void build(int k,int l,int r){
	val[k]=l; if (l==r) return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
void mdy(int k,int l,int r,int x){
	if (l==r){ val[k]=x; return; }
	int mid=(l+r)>>1;
	if (x<=mid) mdy(k<<1,l,mid,x); else mdy(k<<1|1,mid+1,r,x);
	if (id[pos[val[k<<1]]]<id[pos[val[k<<1|1]]]) val[k]=val[k<<1|1]; else val[k]=val[k<<1];
}
int qry(int k,int l,int r,int x,int y){
	if (l==x && r==y) return val[k]; int mid=(l+r)>>1;
	if (y<=mid) return qry(k<<1,l,mid,x,y);
	else if (x>mid) return qry(k<<1|1,mid+1,r,x,y); 
	else{
		int t1=qry(k<<1,l,mid,x,mid),t2=qry(k<<1|1,mid+1,r,mid+1,y);
		if (id[pos[t2]]>id[pos[t1]]) t1=t2; return t1;
	}
}
int read(){
	int x=0; char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }
	return x;
}
int main(){
	n=read(); m=read(); int i; id[0]=-inf-1;
	scp.ins(scp.rt,-inf,inf,(node){0,0});
	for (i=1; i<=n; i++) pos[i]=1; build(1,1,n);
	char ch; int x,y,z;
	while (m--){
		ch=getchar();
		while (ch<'A' || ch>'Z') ch=getchar();
		if (ch=='C'){
			x=read(); y=read(); z=read();
			pos[z]=scp.ins(scp.rt,-inf,inf,(node){pos[x],pos[y]});
			if (flag) scp.rebuild(scp.rt,-inf,inf);
			mdy(1,1,n,z);
		} else{
			x=read(); y=read(); printf("%d\n",qry(1,1,n,x,y));
		}
		for(int i = 1;i <= n;++ i) printf("%d ",pos[i]);
		puts("");
		for(int i = 1;i <= n;++ i) printf("%lld ",id[i]);
		puts("");
	}
	return 0;
}
