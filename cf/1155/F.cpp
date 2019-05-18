#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=20,M=2e4+10;
struct data{
	int x,y;
}c[M];
vector<int>g[N];
int cnt=0,F=0;
int f[N][N][M],dp[M],pw[N]={1},ys[M],s[N],nm[M];
int pre[M],st[M],ed[M];

int lower(int x){
	return x&(-x);
}

void dfs(int mask,int now,int zd,int mk){
	if(F) return ;
	int len=g[now].size();
	fr(i,0,len-1){
		int to=g[now][i];
		if(to==zd&&mk==mask) {
			c[++cnt]=(data){now,to};
			fr(j,1,cnt) {
				printf("%d %d\n",c[j].x+1,c[j].y+1);
			}
			F=1;
			return ;
		}
		if(mk&pw[to]||(mask&pw[to])==0) continue;
		c[++cnt]=(data){now,to};
		dfs(mask,to,zd,mk|pw[to]);
		cnt--;
		if(F) return ;
	}
	if(F) return ;
}

int main(){
	memset(dp,-1,sizeof dp);
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) pw[i]=pw[i-1]*2,ys[pw[i]]=i;
	int tot=pw[n]-1;
	fr(i,1,tot) nm[i]=nm[i-lower(i)]+1;
	fr(i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		x--,y--;
		g[x].push_back(y),
		g[y].push_back(x);
		f[x][y][0]=1,f[y][x][0]=1;
	}
	fr(k,0,tot) {
		fr(i,0,n-1) fr(j,0,n-1) {
			if(!f[i][j][k]||(i==j)) continue;
			int len=g[j].size();
			fr(t,0,len-1) {
				int to=g[j][t];
				if(k&pw[to]) continue;
				if(to==i&&!k) continue;
				f[i][to][k|pw[j]]=1;
			} 
		}
	}
	fr(i,0,n-1) dp[pw[i]]=0;
	fr(i,0,tot) {
		if(dp[i]==-1) continue;
		s[0]=0;
		for(int j=i;j;j-=lower(j)) {
			s[++s[0]]=ys[lower(j)];
		}
		int now=tot^i;
		for(int j=now;j;j=(j-1)&now) {
			fr(k,1,s[0]) fr(t,k,s[0]) {
				int K=s[k],T=s[t];
				if(!f[K][T][j]) continue;
				int nmk=j|i;
				if(dp[nmk]==-1||dp[nmk]>dp[i]+nm[j]+1) {
					pre[nmk]=i,st[nmk]=K,ed[nmk]=T;
					dp[nmk]=dp[i]+nm[j]+1;
				}
			}
		}
	}
	printf("%d\n",dp[tot]);
	for(int i=tot;nm[i]!=1;i=pre[i]) {
		cnt=0,F=0;
		// printf("%d %d %d %d\n",i,pre[i],st[i],ed[i]);
		dfs(i^pre[i],st[i],ed[i],0);
	}
	return 0;
}