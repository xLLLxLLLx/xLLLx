#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int to[N<<1],Next[N<<1],head[N],dep[N],f[N],fa[N];
LL w[N<<1],dis[N],p[N];
int cnt=0;

void add(int x,int y,LL v){
	to[++cnt]=y,w[cnt]=v,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,w[cnt]=v,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int v){
	fa[u]=v,dep[u]=dep[v]+1;
	for(int i=head[u];i;i=Next[i]){
		if(to[i]==v) continue;
		p[(i+1)/2]=to[i];
		dis[to[i]]=w[i];
		dfs(to[i],u);
	}
}

int find(int k){
	return f[k]==k?k:f[k]=find(f[k]);
}

LL Go(int x,int y,LL z){
	for(;x!=y;){
		if(dep[x]<dep[y]) swap(x,y);
		if(dis[x]==1) x=find(x);
		else {
			z/=dis[x];
			x=fa[x];
			if(!z) return z;
		}
	}
	return z;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n-1){
		int x,y;LL v;
		scanf("%d%d%lld",&x,&y,&v);
		add(x,y,v);
	}
	fr(i,1,n) f[i]=i;
	dfs(1,0);
	dis[1]=1;
	fr(i,1,n){
		if(dis[i]==1) f[i]=find(fa[i]);
	}
//	fr(i,1,n) cout<<dis[i]<<endl;
	fr(i,1,m){
		int tp,x,y;LL z;
		scanf("%d",&tp);
		if(tp==1) {
			scanf("%d%d%lld",&x,&y,&z);
			printf("%lld\n",Go(x,y,z));
		}
		else {
			scanf("%d%lld",&y,&z);
			dis[p[y]]=z;
			if(z==1){
				f[p[y]]=find(fa[p[y]]);
			}
		}
	}
	return 0;
}
