#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010;
struct data{
	int x,y;
}a[N*10];
int to[N<<1],Next[N<<1],head[N];
int dp[N][N],dep[N],lmt[N],f[N];
int cnt=0;

void add(int x,int y){
	to[++cnt]=y,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;f[u]=fa;
	for(int i=head[u];i;i=Next[i]){
		if(to[i]==fa) continue;
		dfs(to[i],u);
	}
}

void Dfs(int u){
	fr(i,lmt[u],dep[u]) dp[u][i]=0;
	for(int i=head[u];i;i=Next[i]){
		if(to[i]==f[u]) continue;
		Dfs(to[i]);
		int tmp=dp[to[i]][dep[to[i]]];
		fr(k,0,dep[u]){
			tmp=(dp[to[i]][k]==-1?tmp:min(tmp,dp[to[i]][k]));
			if(k>=lmt[u]) dp[u][k]+=tmp;
		}
	}
	if(u) dp[u][dep[u]]++;
}

int main(){
	int n,m;
	for(;scanf("%d%d",&n,&m)==2&&(n||m);){
		cnt=0,memset(head,0,sizeof head);
		memset(dp,-1,sizeof dp);
		memset(lmt,0,sizeof lmt);
		fr(i,1,n-1){
			int x,y;
			scanf("%d%d",&x,&y);
			x--,y--;
			add(x,y);
		}
		dep[0]=0;
		dfs(0,0);
		int zz=m-n+1;
		fr(i,1,zz){
			scanf("%d%d",&a[i].x,&a[i].y);
			a[i].x--,a[i].y--;
			if(dep[a[i].x]<dep[a[i].y]) swap(a[i].x,a[i].y);
			lmt[a[i].x]=max(lmt[a[i].x],dep[a[i].y]+1);
		}
		Dfs(0);
		printf("%d\n",dp[0][0]);
	//	fr(i,0,n-1) printf("lmt%d=%d\n",i,lmt[i]);
	//	fr(i,0,n-1) fr(j,0,n-1) printf("u=%d dep=%d %d\n",i,j,dp[i][j]);
	}
	return 0;
}
