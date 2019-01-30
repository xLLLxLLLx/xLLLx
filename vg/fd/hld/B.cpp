#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=1e4+10,M=10;
struct data{
	int nt,to,w,rk;
}a[N<<1];
char lx[M];
int cnt=0,res=0,n,wtf;
int v[N<<2],head[N],ys[N],w[N],tp[N],s[N],dep[N],f[N],sz[N],id[N],ed[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,int w,int rk){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].rk=rk,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].rk=rk,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs1(int u,int fa){
	sz[u]=1,f[u]=fa,dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		ys[a[i].rk]=to,w[to]=a[i].w,dfs1(to,u);
		if(sz[s[u]]<sz[to]) s[u]=to;
		sz[u]+=sz[to];
	}
}

void dfs2(int u,int v){
	id[u]=++res,tp[u]=v;
	if(!s[u]) {
		ed[u]=res;
		return ;
	}
	dfs2(s[u],v);
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==f[u]||to==s[u]) continue;
		dfs2(to,to);
	}
	ed[u]=res;
}

void change(int x,int l,int r,int L,int k){
	if(l==r&&l==L){
		v[x]=k;
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	v[x]=max(v[lson],v[rson]);
}

int get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	int mid=(l+r)>>1,ans1=0,ans2=0;
	if(L<=mid) ans1=get(lson,l,mid,L,R);
	if(R>mid) ans2+=get(rson,mid+1,r,L,R);
	return max(ans1,ans2);
}

int find(int x,int y){
	int fx=tp[x],fy=tp[y];
	int maxn=0;
	for(;fx!=fy;){
		if(dep[fx]>dep[fy]) {
			maxn=max(maxn,get(1,1,n,id[fx],id[x]));
			x=f[fx],fx=tp[x];
		} else {
			maxn=max(maxn,get(1,1,n,id[fy],id[y]));
			y=f[fy],fy=tp[y];
		}
	}
	if(dep[x]>dep[y]) maxn=max(maxn,get(1,1,n,id[y]+1,id[x]));
	if(dep[x]<dep[y]) maxn=max(maxn,get(1,1,n,id[x]+1,id[y]));
	return maxn;
}

int main(){
	//freopen("out","r",stdin);
	int T;read(T);
	fr(o,1,T){
		memset(head,0,sizeof head);
		memset(s,0,sizeof s);
		cnt=0,res=0;
		read(n);
		fr(i,1,n-1) {
			int x,y,z;
			read(x),read(y),read(z);
			add(x,y,z,i);
		}
		dfs1(1,1),dfs2(1,1);
		fr(i,2,n) change(1,1,n,id[i],w[i]);
		for(;;){
			int x,y;
			scanf("%s",lx+1);
			if(lx[1]=='D') break;
			read(x),read(y);
			if(lx[1]=='Q'){
				printf("%d\n",find(x,y));
			} else if(lx[1]=='C'){
				change(1,1,n,id[ys[x]],y);
			} 
		}
	}
	return 0;
}
