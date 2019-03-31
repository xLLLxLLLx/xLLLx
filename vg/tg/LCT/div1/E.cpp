#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10,M=8e6+10,inf=1e9;
int sz=0;
int rt[N],id[N],lson[M],rson[M],v[M],t[N],fa[N],pre[N];
struct data{
	int x,y;
}a[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int find(int k){
	return fa[k]==k ? k : fa[k]=find(fa[k]);
}

void build(int &x,int l,int r){
	x=++sz;
	if(l==r) return ;
	int mid=(l+r)>>1;
	build(lson[x],l,mid),build(rson[x],mid+1,r);
}

void change(int old,int nw,int l,int r,int L,int k){
	nw=++sz;
	lson[nw]=lson[old],rson[nw]=rson[old],v[nw]=v[old];
	if(l==r){ v[nw]+=k; return ; }
	int mid=(l+r)>>1;
	if(L<=mid) change(lson[nw],lson[nw],l,mid,L,k);
	else change(rson[nw],rson[nw],mid+1,r,L,k);
	v[nw]=v[lson[nw]]+v[rson[nw]];
}

int ask(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	int mid=(l+r)>>1,ans1=0,ans2=0;
	if(L<=mid) ans1=ask(lson[x],l,mid,L,R);
	if(R>mid) ans2=ask(rson[x],mid+1,r,L,R);
	return ans1+ans2;
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
	int ch[N][2],f[N],rev[N];

	bool isroot(int x){
		return (ch[f[x]][1]!=x)&&(ch[f[x]][1]!=x);
	}

	void up(int x){
		id[x]=x;
		if(t[id[ls]]<t[id[x]]) id[x]=id[ls];
		if(t[id[rs]]<t[id[x]]) id[x]=id[rs];
	}

	void down(int x){
		if(rev[x]){
			if(ls) rev[ls]^=1;
			if(rs) rev[rs]^=1;
			swap(ls,rs);
			rev[x]=0;
		}
	}

	void pushdown(int x){
		if(!isroot(x)) pushdown(f[x]);
		down(x);
	}

	void rotate(int x){
		int y=f[x],z=f[y];
		int k=(ch[z][1]==y),d=(ch[y][1]==x);
		if(!isroot(y)) ch[z][k]=x;
		f[x]=z;
		ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
		ch[x][d^1]=y,f[y]=x;
	}

	void splay(int x){
		pushdown(x);
		while(!isroot(x)){
			int y=f[x],z=f[y];
			if(!isroot(y))
				(ch[z][1]==y)^(ch[y][1]==x) ? rotate(x) : rotate(y);
			rotate(x);
		}
		up(x);
	}

	void access(int x){
		for(int i=0;x;i=x,x=f[x]){
			splay(x),rs=i,up(x);
		}
	}

	void makeroot(int x){
		access(x),splay(x);
		rev[x]^=1;
	}

	void link(int x,int y){
		makeroot(x);
		f[x]=y;
	}

	void cut(int x,int y){
		makeroot(x),access(y),splay(y);
		ch[y][0]=f[x]=0;
		up(y);
	}

	int ask(int x,int y){
		makeroot(x),access(y),splay(y);
		return id[y];
	}

}lct;

int main(){
	int n,m,k,tp;
	read(n),read(m),read(k),read(tp);
	build(rt[0],1,n);
	fr(i,1,n) fa[i]=i;
	fr(i,0,n) t[i]=inf;
	fr(i,1,m){
		read(a[i].x),read(a[i].y);
		int fx=find(a[i].x),fy=find(a[i].y);
		if(fx==fy){
			int sit=lct.ask(a[i].x,a[i].y);
			pre[i]=sit-n;
			lct.cut(sit,a[sit-n].x),lct.cut(sit,a[sit-n].y);
		} else fa[fx]=fy;
		t[i+n]=i,id[i+n]=i+n;
		lct.link(a[i].x,i+n),lct.link(a[i].y,i+n);
	}
	int ans=0;
	fr(i,1,n) change(rt[i-1],rt[i],1,n+1,pre[i]+1,1);
	for(int i=1,x,y;i<=k;++i){
		read(x),read(y);
		if(tp) x^=ans,y^=ans;
		ans=ask(rt[y],1,n+1,1,x)-ask(rt[x-1],1,n+1,1,x);
		printf("%d\n",ans);
	}
	return 0;
}