#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1510;
struct data{
	int nt,to;
}a[N<<1];
struct node{
	db x,y;
	int rk;
}c[N][N],zz;
int head[N],sz[N],id[N],cnt=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	sz[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		dfs(to,u);
		sz[u]+=sz[to];
	}
}

bool comp(node xx,node yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	return xx.y<yy.y;
}

bool cmp(node xx,node yy){
	if(xx.x==zz.x) return 0;
	if(yy.x==zz.x) return 1;
	db pos=(xx.y-zz.y)/(xx.x-zz.x);
	db tmp=(yy.y-zz.y)/(yy.x-zz.x);
	return pos<tmp;
}

void Get(int u,int fa){
	sort(c[u]+1,c[u]+1+sz[u],comp);
	id[c[u][1].rk]=u;
	if(sz[u]>1) zz=c[u][1],sort(c[u]+2,c[u]+1+sz[u],cmp);
	int pos=1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(to==fa) continue;
		fr(j,pos+1,pos+sz[to]) c[to][j-pos]=c[u][j];
		Get(to,u);
		pos+=sz[to];
	}
}

int main(){
	int n;scanf("%d",&n);
	for(int i=1,x,y;i<n;++i) scanf("%d%d",&x,&y),add(x,y);
	dfs(1,0);
	fr(i,1,n) scanf("%lf%lf",&c[1][i].x,&c[1][i].y),c[1][i].rk=i;
	Get(1,0);
	fr(i,1,n) printf("%d ",id[i]);
	return 0;
}
