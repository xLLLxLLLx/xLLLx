#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=2e5+10;
struct data{
	int nt,to;
}a[N<<2];
int cnt=0,res=0;
int num=0;
int v[N<<2];
int w[N],dep[N],id[N],ed[N],head[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]^1;
	id[u]=++res;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dfs(a[i].to,u);
	}
	ed[u]=res;
}

void change(int x,int l,int r,int L,int R,int k){
	if(L<=l&&r<=R) {v[x]+=k;return ;}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,R,k);
	if(R>mid) change(rson,mid+1,r,L,R,k);
}

void find(int x,int l,int r,int L){
	num+=v[x];
	if(l==r&&l==L) return ;
	int mid=(l+r)>>1;
	if(L<=mid) find(lson,l,mid,L);
	else find(rson,mid+1,r,L);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%d",&w[i]);
	fr(i,1,n-1){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,1);
	fr(i,1,m){
		int tp,y,z;
		scanf("%d",&tp);
		if(tp==2) {
			scanf("%d",&y);
			num=0;
			find(1,1,n,id[y]);
			if(dep[y]) printf("%d\n",w[y]+num);
			else printf("%d\n",w[y]-num);
		} else {
			scanf("%d%d",&y,&z);
			if(dep[y]) change(1,1,n,id[y],ed[y],z);
			else change(1,1,n,id[y],ed[y],-z);
		}
	}
	return 0;
}
