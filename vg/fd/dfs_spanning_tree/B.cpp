#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=3e5+10;
const LL MAXN=1e18;
struct data{
	int x,y;
}h[M];
int cnt=-1,n,m;
LL w[M<<1],v[N];
int Next[M<<1],head[N],pp[M<<1],to[M<<1],p[M<<1],g[N],vis[N],dep[N];

void add(int x,int y){
	to[++cnt]=y,pp[cnt]=x,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,pp[cnt]=y,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	g[u]=fa,dep[u]=dep[fa]+1,vis[u]=1;
	for(int i=head[u];i!=-1;i=Next[i]){
		if(vis[to[i]]) continue;
		p[i]=1,dfs(to[i],u);
	}
}

void ang(int u,int fa){
	for(int i=head[u];i!=-1;i=Next[i]){
		if(!p[i]) continue;
		ang(to[i],u);
		v[u]^=v[to[i]];
		w[i/2]=
	}
}

int main(){
	srand(time(NULL));
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof head);
	fr(i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	int res=0;
	fr(i,0,m-1){
		int nw=i*2;
		if(p[nw]||p[nw+1]) continue;
		h[++res].x=to[nw],h[res].y=pp[nw];
		if(dep[h[res].x]<dep[h[res].y]) swap(h[res].x,h[res].y);
		LL pos=rand()%MAXN+9979;
		cout<<pos<<endl;
		v[h[res].x]^=pos,v[f[h[res].y]]^=pos;
		w[i*2]=w[i*2+1]=pos;
	}
	agn(1,0);
	sort(w,w+m);
	LL zz=0;
	fr(i,0,m-1) if(!w[i]) zz++; else break;
	LL lt=0;
	fr(i,1,m-1){
		if(w[i]!=w[i-1]){
			LL pos=i-lt;
			zz+=(pos-1)*pos/2;
			lt=i;
		}
	}
	ans+=zz*(m-zz);
	printf("%lld\n",ans);
	return 0;
}