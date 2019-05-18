#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
const int N=20,MASK=2e4+10;
struct data{
	int x,y;
}c[N];
int cnt=0,FF=0;
int f[N][N][MASK],g[N],pw[N],dp[MASK];
int zy[MASK],pre[MASK],st[MASK],ed[MASK];
vector<int>g[N];

int lower(int x){
	return x&(-x);
}

void dfs(int be,int mask,int now,int num){
	int len=g[now].size();
	fr(i,0,len-1) {
		int to=g[be][i];
		if(mask&(1<<to)) continue;
		int now=mask|(1<<to);
		f[be][to][now]=num+1;
		dfs(be,now,to,num+1);
	}
}

void go(int mask,int be,int pos,int now){
	int len=g[be].size();
	if(be==pos) {
		if(mask==now) {
			fr(i,1,cnt) {
				printf("%d %d\n",c[i].x,c[i].y);
			}
			FF=1;
		} else return ;
	}
	fr(i,0,len-1) {
		int to=g[be][i];
		if(now&pw[to]||!(mask&pw[to])) continue;
		c[++cnt]=(data){be,to};
		go(mask,to,pos,now|pw[to]);
		if(FF) return ;
		cnt--;
	}
	if(FF) return ;
}

int main(){
	memset(pre,-1,sizeof pre);
	int n,m;scanf("%d%d",&n,&m);
	fr(i,0,n) ys[1<<i]=i,pw[i]=1<<i;
	fr(i,1,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		x--,y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	int tot=pw[n]-1;
	fr(i,0,n-1) {
		dfs(i,pw[i],i,0);
	}
	fr(i,0,tot) {
		if(!dp[i]) continue;
		int res=0;
		for(int j=i;j;j-=lower(j)) {
			g[++res]=ys[lower(j)];
		}
		int now=tot^i;
		for(int j=now;j;j=(j-1)&now) {
			fr(k,1,res) fr(t,k+1,res) {
				int K=g[k],T=g[t];
				if(f[K][T][j]) {
					int pos=i|j;
					if(!dp[pos]||dp[pos]>dp[i]+f[K][T][j]) {
						dp[pos]=dp[i]+f[K][T][j];
						pre[pos]=i,zy[pos]=j;
						st[pos]=K,ed[pos]=T;
					}
				}
			}
		}
	}
	printf("%lld\n",dp[tot]);
	for(int i=pre[MASK];i!=-1;i=pre[i]) {
		cnt=0,FF=0;
		go(zy[pos],st[i],ed[i],1<<st[i]);
	}
	return 0;
}