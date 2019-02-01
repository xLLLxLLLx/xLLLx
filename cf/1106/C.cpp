#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int p[N],vis[N];
vector<int>qx[N];

void dfs(int u){
	vis[u]=1;
	int len=qx[u].size();
	fr(i,0,len-1){
		if()
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		qx[x].push_back(y);
		qx[y].push_back(x);
	}
	fr(i,1,n) sort(qx[i].begin(),qx[i].end());
	dfs(1,1);
	fr(i,1,n) printf("%d ",p[i]);
	return 0;
}
