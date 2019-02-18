#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
struct data{
	int nt,to;
}a[N<<1];
int head[N],vis[N],gg[N],cnt=0;
LL g[N],f[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		if(!vis[a[i].to]) dfs(a[i].to);
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	LL tot=m;
	fr(i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		gg[x]=1,gg[y]=1;
		add(x,y);
		if(x==y) f[x]++,--tot;
		else g[x]++,g[y]++;
	}
	fr(i,1,n) {
		if(gg[i]) {dfs(i);break;}
	}
	fr(i,1,n) if(!vis[i]&&gg[i]) return printf("0\n"),0;
	LL ans=0;
	fr(i,1,n) ans+=g[i]*(g[i]-1)/2;
	if(tot) ans+=tot*(m-tot)+(m-tot)*(m-tot-1)/2;
	cout<<ans<<endl;
	return 0;
}
