#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
	int nt,to;
}a[N<<1];
int head[N],dp[N],b[N];
int cnt=0,tot=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void dfs(int u,int fa){
	if(!head[u]){
		dp[u]=1;
		tot++;
		return ;
	}
	if(b[u]) dp[u]=1000000;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to==fa) continue;
		dfs(a[i].to,u);
		if(b[u]) dp[u]=min(dp[u],dp[a[i].to]);
		else dp[u]+=dp[a[i].to];
	}
	//printf("xx%d %d\n",u,dp[u]);
}

int main(){
	int n;read(n);
	fr(i,1,n) read(b[i]);
	for(int i=2,y;i<=n;++i) read(y),add(y,i);
	dfs(1,0);
	printf("%d\n",tot-dp[1]+1);
	return 0;
}