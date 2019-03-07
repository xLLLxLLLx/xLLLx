#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55;
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
int a[N][N],gg[N*N][2],GG[N*N][2],res=0,cnt=0;
int vis[N][N];
int n;

void dfs(int x,int y){
	gg[++res][0]=x,gg[res][1]=y,vis[x][y]=1;
	fr(i,0,3){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<=0||xx>n||yy<=0||yy>n||a[xx][yy]||vis[xx][yy]) continue;
		dfs(xx,yy); 
	}
}

int pf(int x){
	return x*x;
}

int main(){
	scanf("%d",&n);
	int bx,by,ex,ey;
	scanf("%d%d%d%d",&bx,&by,&ex,&ey);
	fr(i,1,n) fr(j,1,n) scanf("%1d",&a[i][j]);
	dfs(bx,by);
	fr(i,1,res) GG[i][0]=gg[i][0],GG[i][1]=gg[i][1];
	cnt=res,res=0;
	memset(vis,0,sizeof vis);
	dfs(ex,ey);
	int maxn=5000;
	fr(i,1,cnt) fr(j,1,res){
		maxn=min(maxn,pf(GG[i][0]-gg[j][0])+pf(GG[i][1]-gg[j][1]));
	}
	cout<<maxn<<endl;
	return 0;
}
