#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=3e4+10,mod=10007;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int mul(int x,int y){
	return 1LL*x*y%mod;
}

int add(int x,int y){
	return (x+y)%mod;
}

struct data{
	int k,b;
	data(){ k=1,b=0; }
	data(int _k,int _b){ k=_k,b=_b; }
	int cal(int x){ return add(mul(k,x),b); }
	void print(){ printf("%d %d\n",k,b); }
};

data operator + (data A,data B){
	return (data){mul(A.k,B.k),add(mul(A.b,B.k),B.b)};
}

void exgcd(int a,int b,int &x,int &y){
	if(!b) x=1,y=0;
	else {
	 	exgcd(b,a%b,y,x);
	 	y-=(a/b)*x;
	}
}

#define ls ch[x][0]
#define rs ch[x][1]

struct LCT{

	int ch[N][2],f[N],sf[N],vis[N],in[N];
	data v[N],sum[N];

	void dfs(int u){
		vis[u]=in[u]=1;
		int fa=f[u];
		if(in[fa]){
			f[u]=0;
			sf[u]=fa;
		} else if(!vis[fa]) dfs(fa);
		in[u]=0;
	}

	void insert(int n){
		fr(i,1,n){
			int k,b;
			read(k),read(f[i]),read(b);
			sum[i]=v[i]=(data){k,b};
		}
		fr(i,1,n) if(!vis[i]) dfs(i);
	}

	bool isroot(int x){
		return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
	}

	void up(int x){
		sum[x]=sum[ls]+v[x]+sum[rs];
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
		for(;!isroot(x);rotate(x))
			if(!isroot(f[x]))
				(ch[f[x]][1]==x)^(ch[f[f[x]]][1]==f[x]) ? rotate(x) : rotate(f[x]);
	}

	void access(int x){
		for(int i=0;x;i=x,x=f[x]){
			splay(x),rs=i,up(x);
		}
	}

	int findroot(int x){
		access(x),splay(x);
		while(ls) x=ls;
		splay(x);
		return x;
	}

	void cut(int x){
		access(x),splay(x);
		ls=f[ls]=0;
		up(x);
	}

	void link(int x,int y){
		access(x),splay(x);
		f[x]=y;
	}

	int ask(){
		int x;scanf("%d",&x);
		access(x),splay(x);
		data res=sum[x];
		int y=findroot(x),ff=sf[y];
		access(ff),splay(ff);
		data tmp=sum[ff];
		if(tmp.k==1) return tmp.b ? -1 : -2;
			else if(!tmp.k) return res.cal(tmp.b);
		int a,b;
		exgcd(tmp.k-1,mod,a,b);
		//res.print(),tmp.print();
		return res.cal(mul((mod-a)%mod,tmp.b));
	}

	int pd(int u,int v){
		int ff=sf[v];
		if(u==ff) return 1;
		access(ff),splay(ff);
		splay(u);
		return !isroot(ff);
	}

	void UPD(){
		int u,fa,k,b;read(u),read(k),read(fa),read(b);
		access(u),splay(u);
		v[u]=data(k,b),up(u);
		int ro=findroot(u);
		//printf("%d %d\n",ro,fa);
		if(u==ro) {
			int rf=findroot(fa);
			//printf("%d\n",rf);
			if(rf==ro) sf[u]=fa;
			else sf[u]=0,link(u,fa);
		} else {
			if(pd(u,ro)){
				cut(u),link(ro,sf[ro]);
				sf[ro]=0;
				int rf=findroot(fa);
				if(rf==u) sf[u]=fa;
				else link(u,fa);
			} else {
				cut(u);
				int rf=findroot(fa);
				if(rf==u) sf[u]=fa;
				else link(u,fa);
			}
		}
	}

}lct;

char lx[2];

int main(){
	int n;read(n);
	lct.insert(n);
	int m;read(m);
	fr(i,1,m){
		scanf("%s",lx+1);
		if(lx[1]=='A') printf("%d\n",lct.ask());
		else lct.UPD();
	}
	return 0;
}