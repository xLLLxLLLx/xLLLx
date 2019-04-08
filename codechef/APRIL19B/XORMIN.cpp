#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=2e6+10,LOG=20;
struct data{
	int nt,to;
}a[N<<1];
int cnt=0,res=0,sz=0;
int ch[M][2],nm[M],mk[M],rt[N];
int w[N],head[N],st[N],ys[N],ed[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	st[u]=++res,ys[res]=u;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to!=fa) dfs(to,u);
	}
	ed[u]=res;
}

void build(int &x,int dep){
	x=++sz;nm[x]=0;
	if(!dep) return ;
	build(ch[x][0],dep-1),build(ch[x][1],dep-1);
}

void change(int &nw,int old,int v,int dep){
	if(dep<0) return ;
	nw=++sz;
	ch[nw][0]=ch[old][0],ch[nw][1]=ch[old][1];
	if((v>>dep)&1) 
}

int main(){
	int T;read(T);
	fr(o,1,T){
		int n,m;read(n),read(m);
		cnt=res=sz=0,memset(head,0,sizeof head);
		fr(i,1,n) read(w[i]);
		for(int i=1,x,y;i<n;++i) read(x,y),add(x,y);
		dfs(1,0);
		build(rt[0],LOG);
		fr(i,1,res) change(rt[i],rt[i-1],w[ys[i]],LOG);
	}
	return 0;
}