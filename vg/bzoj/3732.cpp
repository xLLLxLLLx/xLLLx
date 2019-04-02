#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=6e4+10;
struct data{
	int nt,to,w;
}a[N<<1],b[N];
int n,m,k,cnt=0,nw=0;
int head[N],f[N],dep[N],g[N][25],val[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

bool cmp(data xx,data yy){
	return xx.w<yy.w;
}

int find(int k){
	return f[k]==k ? k : f[k]=find(f[k]);
}

void dfs(int u,int fa){
	g[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		dfs(to,u);
	}
}

void yyqx(){
	fr(j,1,24) fr(i,1,n*2-1) g[i][j]=g[g[i][j-1]][j-1];
}

int GetLCA(int A,int B){
	if(dep[A]>dep[B]) swap(A,B);
	rf(i,24,0) if(dep[g[B][i]]>=dep[A]) B=g[B][i];
	if(A==B) return A;
	rf(i,24,0)
		if(g[A][i]!=g[B][i]) A=g[A][i],B=g[B][i];
	return g[A][0];
}

int main(){
	read(n),read(m),read(k);
	fr(i,1,n*2) f[i]=i;
	fr(i,1,m) read(b[i].nt),read(b[i].to),read(b[i].w);
	sort(b+1,b+1+m,cmp);
	nw=n;
	fr(i,1,m){
		int fx=find(b[i].nt),fy=find(b[i].to);
		if(fx==fy) continue;
		val[++nw]=b[i].w;
		add(fx,nw),add(fy,nw);
		f[fx]=f[fy]=nw;
	}
	dfs(nw,0),yyqx();
	fr(i,1,k){
		int x,y;
		read(x),read(y);
		printf("%d\n",val[GetLCA(x,y)]);
	}
	return 0;
}