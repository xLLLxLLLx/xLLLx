#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=2010;
struct data{
	int nt,to;
}qx[N<<1];
LL w[N],dp[N][2];
char lx[10];
int cnt=0,head[N],a[N][N],vis[N];
int n,m;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void read(LL &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void rd(){
	freopen("defense.in","r",stdin);
	freopen("defense.out","w",stdout);
}

void add(int x,int y){
	qx[++cnt].to=y,qx[cnt].nt=head[x],head[x]=cnt;
	qx[++cnt].to=x,qx[cnt].nt=head[y],head[y]=cnt;
}

LL Min(LL x,LL y){
	if(x==-1) return y;
	if(y==-1) return x;
	return min(x,y);
}

void dfs(int u,int fa){
	LL pos=0,tmp=0;
	for(int i=head[u];i;i=qx[i].nt){
		int to=qx[i].to;
		if(to==fa) continue;
		dfs(to,u);
		if(vis[to]==-1) tmp+=Min(dp[to][0],dp[to][1]),pos+=dp[to][1];
		else {
			if(!vis[to]) dp[u][0]=-1,tmp+=dp[to][0]; 
			else pos+=dp[to][1],tmp+=dp[to][1];
		}
	}
	if(dp[u][0]!=-1) dp[u][0]=pos;
	dp[u][1]=tmp+w[u];
}

int main(){
	rd();
	read(n),read(m),scanf("%s",lx+1);
	fr(i,1,n) read(w[i]);
	for(int i=1,x,y;i<n;++i){
		read(x),read(y);
		add(x,y);
		a[x][y]=a[y][x]=1;
	}
	memset(vis,-1,sizeof vis);
	fr(o,1,m){
		int x,is_x,y,is_y;
		read(x),read(is_x),read(y),read(is_y);
		vis[x]=is_x,vis[y]=is_y;
		if(a[x][y]&&(!is_x&&!is_y)) { vis[x]=-1,vis[y]=-1;printf("-1\n"); continue; }
		memset(dp,0x3f,sizeof dp);
		dfs(1,0);
		if(!vis[1]) printf("%lld\n",dp[1][0]);
		else if(vis[1]==1) printf("%lld\n",dp[1][1]);
		else printf("%lld\n",Min(dp[1][0],dp[1][1]));
		vis[x]=-1,vis[y]=-1;
	}
	return 0;
}
