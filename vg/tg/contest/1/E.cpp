#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;++i)
#define LL long long
using namespace std;
const int N=210;
int dp[N][N],ans[N],d[N][N],w[N],f[N];
int n,k;

void dfs(int u,int fa){
	fr(s,1,n) if(d[u][s]==1&&s!=fa) dfs(s,u);
	fr(i,1,n){
		int pos=w[d[u][i]]+k;
		fr(s,1,n){
			if(d[u][s]==1&&s!=fa){
				pos+=min(dp[s][i]-k,dp[s][ans[s]]);
			}
		}
		dp[u][i]=pos;
	}
	ans[u]=1;
	fr(i,2,n) if(dp[u][ans[u]]>dp[u][i]) ans[u]=i;
}

void sc(int u,int fa){
	if(dp[u][ans[u]]<=dp[u][f[fa]]-k) f[u]=ans[u];
	else f[u]=f[fa];
	fr(i,1,n)
		if(d[u][i]==1&&i!=fa) sc(i,u);
}

int main(){
	scanf("%d%d",&n,&k);
	fr(i,1,n-1) scanf("%d",&w[i]);
	memset(d,0x3f,sizeof d);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		d[x][y]=1,d[y][x]=1;
	}
	fr(i,1,n) d[i][i]=0;
	fr(k,1,n) fr(i,1,n) fr(j,1,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	dfs(1,0);
	cout<<dp[1][ans[1]]<<endl;
	f[1]=ans[1];
	fr(i,1,n) if(d[i][1]==1) sc(i,1);
	fr(i,1,n) printf("%d ",f[i]);
	return 0;
}
