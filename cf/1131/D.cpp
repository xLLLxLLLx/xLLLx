#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e3+10;
struct data{
	int nt,to;
}a[N*N],zz[N*N];
int head[N<<1],vis[N<<1],mx[N<<1],d[N<<1],as[N<<1],f[N<<1];
int cnt=0;

void add(int x,int y){
	d[y]++;
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

int find(int k){
	return f[k]==k?f[k]:f[k]=find(f[k]);
}

void fail(){
	printf("No\n");
	exit(0);
}

void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		if(vis[a[i].to]) continue;
		d[a[i].to]--,mx[a[i].to]=max(mx[a[i].to],as[u]);
		if(!d[a[i].to]){
			as[a[i].to]=mx[a[i].to]+1;
			dfs(a[i].to);
		}
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	int res=0;
	fr(i,1,n+m) f[i]=i;
	fr(i,1,n) fr(j,1,m){
		char ch;cin>>ch;
		if(ch=='>') zz[++res]=(data){j+n,i};
		if(ch=='<') zz[++res]=(data){i,j+n};
		if(ch=='='){
			int fx=find(j+n),fy=find(i);
			f[fx]=fy;
		}
	}
	fr(i,1,n+m) find(i); 
	fr(i,1,res) add(f[zz[i].nt],f[zz[i].to]);
	fr(i,1,n+m){
		if(vis[f[i]]) continue;
		if(!d[f[i]]) vis[f[i]]=1,as[f[i]]=1,dfs(f[i]);
	}
	fr(i,1,n+m) if(!vis[f[i]]) fail();
	printf("Yes\n");
	fr(i,1,n) printf("%d ",as[f[i]]);
	puts("");
	fr(i,1,m) printf("%d ",as[f[i+n]]);
	return 0;
}
