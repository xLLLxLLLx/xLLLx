#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define pb push_back
#define LL long long
using namespace std;
const int N=1e5+10;
int n,m;
int vis[N];
bitset<N>C[N];
vector<int>A[N],B[N];

void dfs(int u,int fa){
	
}

int main(){
	while(scanf("%d%d",&n,&m)==2&&(n||m)){
		memset(vis,0,sizeof vis);
		fr(i,1,n-1){
			int x,y;
			scanf("%d%d",&x,&y);
			A[x].pb(y),A[y].pb(x);
		}
		fr(i,n,m){
			int x,y;
			scanf("%d%d",&x,&y);
			B[x].pb(y),B[y].pb(x);
		}
		int ans=0;
		dfs(1,-1);
		printf("%d\n",ans);
	}
	return 0;
}
