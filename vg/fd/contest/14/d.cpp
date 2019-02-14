#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=1e5+10;
struct data{
	int fr,to,w,rk;
	bool operator < (const data &C) const{
		return w<C.w;
	}
}a[N];
int cnt=0,m,n;
int K[N],c[N],d[N],f[N];
int B[N],head[N],to[N<<1],Next[N<<1],id[N<<1],Fa[N],G[N],vis[N];

int find(int k){
	return f[k]==k?f[k]:f[k]=find(f[k]);
}

void add(int x,int y,int zz){
//	printf("zz%d %d %d\n",x,y,zz);
	to[++cnt]=y,id[cnt]=zz,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,id[cnt]=zz,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	//printf("u=%d fa=%d\n",u,fa);
	vis[u]=1;
	for(int i=head[u];i;i=Next[i]){
		if(to[i]==fa) {
			if(G[u]!=id[i]) d[G[u]]=1,d[id[i]]=1;
			continue;
		}
		if(!vis[to[i]]) G[to[i]]=id[i],Fa[to[i]]=u,dfs(to[i],u);
		if(vis[to[i]]==1){
			int tt=u,dd=to[i];
			for(;tt!=dd;) d[G[tt]]=1,tt=Fa[tt];
			d[id[i]]=1;
		}
	}
	vis[u]=-1;
}

void Add(int x,int y){
	int fx=find(x),fy=find(y);
	f[fx]=fy;
}

void luangao(){
	int lt=1;
	fr(i,1,m+1){
		if(i>1&&a[i].w!=a[i-1].w){
			fr(j,1,c[0]) if(!vis[j]) dfs(j,-1);
			fr(j,1,K[0]) if(!d[K[j]]) d[K[j]]=2;
		//	fr(j,1,K[0]) printf("dedao%d %d\n",K[j],d[K[j]]);
			fr(j,1,c[0]) head[j]=0,B[c[j]]=0,vis[j]=0;
			fr(j,lt,i-1) Add(a[j].fr,a[j].to);
		//	printf("%d %d\n",c[0],K[0]);
		//	printf("xxxxxxxxxxxxx\n");
			cnt=0,c[0]=0,K[0]=0;
			lt=i;
		}
		int fx=find(a[i].fr),fy=find(a[i].to);
		//printf("i=%d fx=%d fy=%d\n",i,fx,fy);
		if(fx==fy) continue;
		if(fx>fy) swap(fx,fy);
		K[++K[0]]=a[i].rk;
		int flg=0;
		if(!B[fx]) flg++,c[++c[0]]=fx,B[fx]=c[0];
		if(!B[fy]) flg++,c[++c[0]]=fy,B[fy]=c[0];
		add(B[fx],B[fy],a[i].rk);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n) f[i]=i;
	fr(i,1,m){
		scanf("%d%d%d",&a[i].fr,&a[i].to,&a[i].w);
		a[i].rk=i;
	}
	sort(a+1,a+1+m);
	luangao();
	fr(i,1,m){
		if(!d[i]) printf("none\n");
		else if(d[i]==1) printf("at least one\n");
		else printf("any\n");
	}
	return 0;
}
