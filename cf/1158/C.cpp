#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define ls (x<<1)
#define rs (x<<1|1)
using namespace std;
const int N=5e5+10,M=N*6;
struct data{
	int nt,to;
}a[N*12];
int head[M],id[M],ys[M],mk[N],val[M],v[M],d[M],vis[M];
int n,n2,mx=0,cnt=0;

void add(int x,int y){
	d[y]++;
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

void build(int x,int l,int r) {
	id[x]=++n2;
	if(l==r) {ys[l]=n2,v[n2]=1;return ;}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	add(id[x],id[ls]),add(id[x],id[rs]);
}

void Add(int x,int l,int r,int L,int R,int be){
	if(L>R) return ;
	if(L<=l&&r<=R) {
		add(id[x],be);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) Add(ls,l,mid,L,R,be);
	if(R>mid) Add(rs,mid+1,r,L,R,be);
}

void dfs(int x){
	vis[x]=1;
	if(v[x]) {
		val[x]++;
		val[x]=max(val[x],mx+1);
		mk[val[x]]=1;
	}
	mx=max(mx,val[x]);
	int pos=val[x];
	for(int i=head[x];i;i=a[i].nt) {
		int to=a[i].to;
		d[to]--;
		val[to]=max(val[to],pos);
		if(!d[to]) dfs(to);
	}
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T) {
		scanf("%d",&n),n2=n;
		build(1,1,n);
		fr(i,1,n) {
			int x;
			scanf("%d",&x);
			if(x!=-1) {
				Add(1,1,n,i+1,x-1,ys[i]);
				if(x!=n+1) Add(1,1,n,i,i,ys[x]);
			}
		}
		fr(i,n+1,n2) {
			if(!d[i]&&!vis[i]) {
				val[i]=mx;
				dfs(i);
			}
		}
		int flg=1;
		fr(i,1,n)
			if(!vis[ys[i]]||!mk[i]) flg=0;
		if(!flg) {
			printf("-1\n");
		} else {
			fr(i,1,n) printf("%d ",val[ys[i]]);
			puts("");
		}
		fr(i,1,n) mk[i]=0;
		fr(i,1,n*5) head[i]=d[i]=v[i]=vis[i]=val[i]=0;
		cnt=mx=0;
	}
	return 0;
}