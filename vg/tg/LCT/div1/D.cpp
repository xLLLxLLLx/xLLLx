#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
struct edge{
	int nt,to,A,B;
}a[N];
int fa[N],v[N],id[N];
int n,m;

int find(int k){
	return fa[k]==k ? k : fa[k]=find(fa[k]);
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{
	int ch[N][2],f[N],tag[N],q[N],top;

	bool isroot(int x){
		return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
	}

	void down(int x){
		if(tag[x]){
			//if(ls) 
				tag[ls]^=1;
			//if(rs) 
				tag[rs]^=1;
			swap(ls,rs);
			tag[x]=0;
		}
	}

	void pushdown(int x){
		if(!isroot(x)) pushdown(f[x]);
		down(x);
	}

	void up(int x){
		id[x]=x;
		if(v[id[ls]]>v[id[x]]) id[x]=id[ls];
		if(v[id[rs]]>v[id[x]]) id[x]=id[rs];
	}

	void rotate(int x){
		int y=f[x],z=f[y];
		int k=(ch[z][1]==y),d=(ch[y][1]==x);
		if(!isroot(y)) ch[z][k]=x;
		f[x]=z;
		ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
		ch[x][d^1]=y,f[y]=x;
		up(y),up(x);
	}

	void splay(int x){
		pushdown(x);
		while(!isroot(x)){
			int y=f[x],z=f[y];
			if(!isroot(y)) 
				(ch[y][1]==x)^(ch[z][1]==y) ? rotate(x) : rotate(y);
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
		tag[x]^=1;
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
		makeroot(x);
		access(y),splay(y);
		return id[y];
	}

}lct;

bool cmp(edge xx,edge yy){
	return xx.A < yy.A;
}

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int main(){
	read(n),read(m);
	fr(i,1,m) scanf("%d%d%d%d",&a[i].nt,&a[i].to,&a[i].A,&a[i].B);
	sort(a+1,a+1+m,cmp);
	fr(i,1,n) fa[i]=i;
	int ans=1e9;
	fr(i,1,m){
		int fx=find(a[i].nt),fy=find(a[i].to);
		if(a[i].nt==a[i].to) continue;
		if(fx==fy){
			int sit=lct.ask(a[i].nt,a[i].to);
			if(v[sit]>a[i].B){
				lct.cut(sit,a[sit-n].nt),lct.cut(sit,a[sit-n].to);
			} else continue;
		} else fa[fx]=fy;
		v[i+n]=a[i].B,id[i+n]=i+n;
		lct.link(a[i].nt,i+n),lct.link(a[i].to,i+n);
		if(find(1)==find(n)) ans=min(ans,a[i].A+v[lct.ask(1,n)]);
	}
	if(ans!=1e9) printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}