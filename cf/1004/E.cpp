#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
struct data{
	int nt,to,w;
}a[N<<1];
int head[N],pre[N],c[N],vis[N],d[N],dis[N],q[N];
int mx=0,cnt=0;

void add(int x,int y,int w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	pre[u]=fa;
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(to==fa) continue;
		dis[to]=dis[u]+a[i].w;
		dfs(to,u);
	}
}

void go(int u,int now){
	// printf("u=%d now=%d\n",u,now);
	vis[u]=1,mx=max(mx,now);
	for(int i=head[u];i;i=a[i].nt) {
		int to=a[i].to;
		if(vis[to]) continue;
		go(to,now+a[i].w);
	}
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,2,n) {
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
	}
	dfs(1,0);
	int be=-1,maxn=0;
	fr(i,1,n) {
		if(maxn<dis[i]) {
			be=i,maxn=dis[i];
		}
	}
	memset(dis,0,sizeof dis);
	memset(pre,0,sizeof pre);
	dfs(be,0);
	int st=-1;
	maxn=0;
	fr(i,1,n) {
		if(maxn<dis[i]) {
			st=i,maxn=dis[i];
		}
	}
	// printf("%d %d\n",be,st);
	for(;st;st=pre[st]) {
		c[++c[0]]=st,vis[st]=1;
	}
	reverse(c+1,c+1+c[0]);
	fr(i,1,c[0]){
		mx=0;
		go(c[i],0);
		d[i]=mx;
	}
	// fr(i,1,c[0]){
	// 	printf("%d %d %d\n",c[i],d[i],dis[c[i]]);
	// }
	k=min(k,c[0]);
	int ans=1e9;
	int head=1,tail=0;
	fr(i,1,c[0]){
		while(head<=tail&&d[q[tail]]<=d[i]) tail--;
		q[++tail]=i;
		while(head<=tail&&q[head]<=i-k) head++; 
		if(i>=k) {
			int pos=max(dis[c[i-k+1]],dis[c[c[0]]]-dis[c[i]]);
			// printf("%d %d\n",c[i],pos);
			ans=min(ans,max(pos,d[q[head]]));
		}
	}
	printf("%d\n",ans);
	return 0;
}