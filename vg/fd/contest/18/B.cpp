#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
struct data{
	int nt,fr,to;
}a[N<<1],b[N];
LL ans=0;
int cnt=-1,n,m;
int head[N],p[N<<1],vis[N],f[N],dep[N];
LL son[N],g[N];

void add(int x,int y){
	a[++cnt].fr=x,a[cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].fr=y,a[cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int x,int fa){
	vis[x]=1;f[x]=fa,dep[x]=dep[fa]+1;
	for(int i=head[x];i!=-1;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]) continue;
		p[i]=1,dfs(to,x);
		son[x]++;
	}
}

void Dfs(int u,int fa){
	ans+=son[u]*(son[u]-1LL)/2;
	for(int i=head[u];i!=-1;i=a[i].nt){
		if(!p[i]) continue;
		ans+=son[a[i].to];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof head);
	fr(i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,1);
	fr(i,1,n) if(!vis[i]) return printf("0\n"),0;
	LL res=0;
	fr(i,1,m){
		int nw=i*2-1,nm=i*2-2;
		if(!p[nw]&&!p[nm]) {
			b[++res].fr=a[nw].fr,b[res].to=a[nw].to;
			if(dep[b[res].fr]<dep[b[res].to]) swap(b[res].fr,b[res].to);
			if(b[res].fr!=b[res].to) g[b[res].fr]++,g[b[res].to]++;
		}
	}
	Dfs(1,1);
	fr(i,1,res){
		if(b[i].fr==b[i].to) {
			ans+=son[b[i].fr];
			if(b[i].fr!=1) ans++;
		}
		else {
			ans+=son[b[i].fr]+son[b[i].to];
			if(b[i].to!=1) ans+=2;
			else ans++;
		}
	}
	fr(i,1,n) ans+=g[i]*(g[i]-1)/2;
	cout<<ans<<endl;
	return 0;
}
