#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
struct data{
	int nt,to;
}a[N<<1];
LL nm[N],ans=0,tot;
int n,k;
int cnt=0,res=0,vis[N],head[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u){
	nm[res]++;vis[u]=1;
	for(int i=head[u];i;i=a[i].nt){
		int to=a[i].to;
		if(!vis[a[i].to]) dfs(a[i].to);
	}
}


int main(){
	scanf("%d%d",&n,&k);
	tot=n;
	for(int i=1,x,y,c;i<n;++i){
		scanf("%d%d%d",&x,&y,&c);
		if(!c) add(x,y);
	}
	fr(i,1,n) if(!vis[i]) res++,dfs(i);
	LL ans=1;
	fr(i,1,k) ans=ans*n%mod;
	fr(i,1,res){
		LL pos=1;
		fr(j,1,k) pos=pos*nm[i]%mod;
		ans=(ans-pos+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}