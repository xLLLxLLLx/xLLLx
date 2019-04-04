#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+1;
struct data{
	int nt,to,w;
}a[N<<1],q[N<<1];
struct gg{
	int x,y,lca,v;
}b[N];
int cnt=0,n,m,res=0,maxn=0;
int f[N],kk=0;
int head[N],headq[N],vis[N],c[N],dis[N];

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,int w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void addq(int x,int y){
	q[++kk].to=y,q[kk].nt=headq[x],headq[x]=kk;
	q[++kk].to=x,q[kk].nt=headq[y],headq[y]=kk;
}

void Dfs(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		Dfs(to,u);
		if(c[to]==res&&a[i].w>maxn) maxn=a[i].w;
		c[u]+=c[to];
	}
}

bool cmp(gg xx,gg yy){
	return xx.v>yy.v;
}

int find(int k){
	return f[k]==k ? k : f[k]=find(f[k]);
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		dis[to]=dis[u]+a[i].w;
		dfs(to,u);
		int fx=find(u),fy=find(to);
		if(fx!=fy) f[fy]=fx;
		vis[to]=1;
	}
	//printf("zz%d %d\n",u,fa);
	for(int i=headq[u];i;i=q[i].nt){
		if(vis[q[i].to]){
			int z=(i+1)>>1;
			b[z].x=u,b[z].y=q[i].to;
			b[z].lca=find(q[i].to);
			b[z].v=dis[u]+dis[q[i].to]-2*dis[b[z].lca];
		}
	}
}

bool check(int x){
	int ff=0;res=0,maxn=0;
	memset(c,0,sizeof c);
	fr(i,1,m)
		if(b[i].v>x) ff=1,res++,c[b[i].x]++,c[b[i].y]++,c[b[i].lca]-=2;
		else break;
	Dfs(1,0);
	return b[ff].v-maxn<=x;
}

int main(){
	//freopen("in","r",stdin);
	read(n),read(m);
	fr(i,1,n) f[i]=i;
	fr(i,2,n){
		int x,y;LL w;
		read(x),read(y),read(w);
		add(x,y,w);
	}
	fr(i,1,m){
		int x,y;read(x),read(y);
		addq(x,y);
	}
	dfs(1,0);
	sort(b+1,b+1+m,cmp);
	//fr(i,1,m) printf("%d %d %d\n",b[i].x,b[i].y,b[i].v);
	int l=0,r=b[1].v,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}