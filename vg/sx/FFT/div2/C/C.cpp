#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e4+10,M=3e6+10;
const double PI=acos(-1.0);
struct data{
	int nt,to;
}ed[N<<1];
ll ans=0,c[M];
int A=0,B=0,cnt=0;
int mk[M],yz[M],dep[N];
int rev[M],sz[N],g[N],f[N],head[N],vis[N];

struct C {
	double r,i;
	C(){}
	C(double _r,double _i){ r=_r,i=_i; }
	C operator + (C x){ return C(r+x.r,i+x.i); }
	C operator - (C x){ return C(r-x.r,i-x.i); }
	C operator * (C x){ return C(r*x.r-i*x.i,i*x.r+r*x.i); }
}a[M],b[M],w[M];

void fft(C a[],int n){
	frl(i,0,n)
		if(rev[i]>i) {
			swap(a[i],a[rev[i]]);
		}
	for(int t=n>>1,d=1;d<n;d<<=1,t>>=1)
		for(int i=0;i<n;i+=(d<<1)) {
			frl(j,0,d) {
				C tmp=w[t*j]*a[i+j+d];
				a[i+j+d]=a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp;
			}
		}
}

ll mul(C a[],int z){
	int L=0,n=1;
	for(;n<=2*z;L++,n<<=1) ;
	frl(i,0,n) {
		if(i%2==0) c[i]=-a[i>>1].r;
		else c[i]=0;
		w[i]=C(cos(2.0*i*PI/n),sin(2.0*i*PI/n));
		rev[i]=(rev[i>>1]>>1)+((i&1)<<(L-1));
	}
	fft(a,n);
	frl(i,0,n) {
		a[i]=a[i]*a[i];
		w[i].i=-w[i].i;
	}
	fft(a,n);
	ll pos=0;
	frl(i,0,n) {
		c[i]+=(long long)(a[i].r/n+0.5);
		c[i]>>=1;
		if(!mk[i]) pos+=c[i];
		a[i]=C(0,0);
	}
	return pos;
}

void add(int x,int y){
	ed[++cnt].to=y,ed[cnt].nt=head[x],head[x]=cnt;
	ed[++cnt].to=x,ed[cnt].nt=head[y],head[y]=cnt;
}

int Get(int u,int fa){
	sz[u]=1,f[u]=fa,g[u]=u;
	for(int i=head[u];i;i=ed[i].nt){
		int to=ed[i].to;
		if(to==fa||vis[to]) continue;
		Get(to,u);
		sz[u]+=sz[to];
	}
	int pos=-1;
	for(int i=head[u];i;i=ed[i].nt){
		int to=ed[i].to;
		if(to==fa||vis[to]) continue;
		if(sz[to]*2>=sz[u]) pos=g[to];
	}
	if(pos==-1) return u;
	while(sz[f[pos]]*2<=sz[u]&&f[pos]!=fa) pos=f[pos];
	return g[u]=pos;
}

void find(int u,int fa){
	for(int i=head[u];i;i=ed[i].nt){
		int to=ed[i].to;
		if(to==fa||vis[to]) continue;
		dep[to]=dep[u]+1;
		b[dep[to]].r+=1;
		a[dep[to]].r+=1;
		A=max(A,dep[to]),B=max(B,dep[to]);
		find(to,u);
	}
}

void dfs(int u,int fa){
	int be=Get(u,fa);
	dep[be]=0,A=0;
	a[dep[be]].r+=1;
	for(int i=head[be];i;i=ed[i].nt){
		int to=ed[i].to;
		if(vis[to]) continue;
		else {
			dep[to]=dep[be]+1;
			b[dep[to]].r+=1;
			a[dep[to]].r+=1;
			A=max(A,dep[to]),B=max(B,dep[to]);
			find(to,be);
			ans-=mul(b,B);
			B=0;
		}
	}
	vis[be]=1;
	ans+=mul(a,A);
	for(int i=head[be];i;i=ed[i].nt){
		if(vis[ed[i].to]) continue;
		dfs(ed[i].to,be);
	}
}

void init(){
	mk[0]=mk[1]=1;
	frl(i,2,M) {
		if(!mk[i]) yz[++yz[0]]=i;
		fr(j,1,yz[0]) {
			if((i*1ll*yz[j])>=M) break;
			mk[i*yz[j]]=1;
			if(i%yz[j]==0) break;
		}
	}
}

int main(){
	init();
	int n;
	scanf("%d",&n);
	fr(i,2,n) {
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	vis[0]=1,dfs(1,0);
	ll tot=1LL*n*(n-1)/2;
	printf("%.10f\n",double(ans)/double(tot));
	return 0;
}