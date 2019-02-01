#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55;
int bx[4]={1,0,-1,0};
int by[4]={0,-1,0,1};
int a[N][N],vis[N][N],flg,n,m;

void dfs(int fx,int fy,int x,int y,int o){
	if(vis[x][y]) {flg=1;return ;}
	vis[x][y]=1;
	fr(i,0,3){
		int xx=x+bx[i],yy=y+by[i];
		if(xx<0||xx>n||yy<0||yy>m) continue;
		if(xx==fx&&yy==fy) continue;
		if(a[xx][yy]!=o) continue;
		if(flg) return ;
		dfs(x,y,xx,yy,o);
	}
	if(flg) return ;
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n) fr(j,1,m){
		char ch;cin>>ch;
		int pos=ch-'A'+1;
		a[i][j]=pos;
	}
	fr(o,1,26) {
		fr(i,1,n) fr(j,1,m){
			if(!vis[i][j]&&a[i][j]==o) dfs(i,j,i,j,o);
			if(flg) return printf("Yes\n"),0;
		}
	}
	printf("No\n");
	return 0;
}
