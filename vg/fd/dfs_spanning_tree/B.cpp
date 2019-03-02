#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10,M=6e5+10;
const LL MAXN=1e18;
int cnt=-1,n,m;
LL w[M],v[N];
int Next[M<<1],head[N],pp[M<<1],to[M<<1],p[M<<1],vis[N];

void add(int x,int y){
	to[++cnt]=y,pp[cnt]=x,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,pp[cnt]=y,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	vis[u]=1;
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
		w[i/2]=v[to[i]];
	}
}

LL js(LL x){
	return (x-1)*x/2;
}

LL RAD(){
	return (1ll*rand())^(1ll*rand())<<15^(1ll*rand())<<30^(1ll*rand())<<45^(1ll*rand())<<60;
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
		int x=to[nw],y=pp[nw];
		LL pos=RAD();
		v[x]^=pos,v[y]^=pos;
		w[i]=pos;
	}
	ang(1,0);
	sort(w,w+m);
	LL zz=0,ans=0;
	fr(i,0,m-1) if(!w[i]) zz++; else break;
	LL lt=0;
	fr(i,1,m-1){
		if(w[i]!=w[i-1]){
			ans+=js(i-lt);
			lt=i;
		}
	}
	ans+=js(m-lt);
	ans+=zz*(m-zz);
	printf("%lld\n",ans);
	return 0;
}
