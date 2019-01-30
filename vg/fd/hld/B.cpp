#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=3e4+10;
struct data{
	int nt,to;
}a[N<<2];
int cnt=0,res=0,n,m;
int v[N<<2],sum[N<<2];
int head[N],dep[N],w[N],f[N],sz[N],s[N],id[N],tp[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs1(int u,int fa){
	dep[u]=dep[fa]+1,f[u]=fa,sz[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		dfs1(to,u);
		sz[u]+=sz[to];
		if(sz[to]>sz[s[u]]) s[u]=to;
	}
}

void dfs2(int u,int v){
	id[u]=++res;tp[u]=v;
	if(!s[u]) return ;
	dfs2(s[u],v);
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==f[u]||a[i].to==s[u]) continue;
		dfs2(a[i].to,a[i].to);
	}
}

void change(int x,int l,int r,int L,int k){
	if(l==r&&L==l) {
		v[x]=k;sum[x]=k;
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	v[x]=max(v[lson],v[rson]);
	sum[x]=sum[lson]+sum[rson];
}

int get_m(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	int mid=(l+r)>>1,ans1=-6e8,ans2=-6e8;
	if(L<=mid) ans1=get_m(lson,l,mid,L,R);
	if(R>mid) ans2=get_m(rson,mid+1,r,L,R);
	return max(ans1,ans2);
}

int get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return sum[x];
	int mid=(l+r)>>1,ans1=0,ans2=0;
	if(L<=mid) ans1=get(lson,l,mid,L,R);
	if(R>mid) ans2=get(rson,mid+1,r,L,R);
	return (ans1+ans2);
}

int findm(int x,int y){
	int fx=tp[x],fy=tp[y];
	int ans=-6e8;
	for(;fx!=fy;){
		if(dep[fx]>dep[fy]){
			ans=max(ans,get_m(1,1,n,id[fx],id[x]));
			x=f[fx],fx=tp[x];
		} else {
			ans=max(ans,get_m(1,1,n,id[fy],id[y]));
			y=f[fy],fy=tp[y];
		}
	}
	if(dep[x]>dep[y]) ans=max(ans,get_m(1,1,n,id[y],id[x]));
	else ans=max(ans,get_m(1,1,n,id[x],id[y]));
	return ans;
}

int find(int x,int y){
	int fx=tp[x],fy=tp[y];
	int ans=0;
	for(;fx!=fy;){
		if(dep[fx]>dep[fy]) {
			ans+=get(1,1,n,id[fx],id[x]);
			x=f[fx],fx=tp[x];
		} else {
			ans+=get(1,1,n,id[fy],id[y]);
			y=f[fy],fy=tp[y];
		}
	}
	if(id[x]>=id[y]) ans+=get(1,1,n,id[y],id[x]);
	else ans+=get(1,1,n,id[x],id[y]);
	return ans;
}

char lx[10];

int main(){
	scanf("%d",&n);
	fr(i,1,n-1){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs1(1,1),dfs2(1,1);
	fr(i,1,n) scanf("%d",&w[i]),change(1,1,n,id[i],w[i]);
	scanf("%d",&m);
	fr(i,1,m){
		int x,y;
		scanf("%s%d%d",lx+1,&x,&y);
		if(lx[4]=='X') printf("%d\n",findm(x,y));
		else if(lx[4]=='M') printf("%d\n",find(x,y));
		else change(1,1,n,id[x],y);
	}
	return 0;
}
