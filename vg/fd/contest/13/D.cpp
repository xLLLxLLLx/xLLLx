#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define Fr(i,x,y) for(int i=x;i<y;++i)
#define Rf(i,x,y) for(int i=x;i>y;--i)
#define LL long long
using namespace std;
const int N=1510;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int n,m;
int vis[N][N][3],a[N][N];

void dfs(int x,int y,int px,int py){
	vis[x][y][0]=1,vis[x][y][1]=px,vis[x][y][2]=py;
	fr(i,0,3){
		int xx=(x+dx[i]+n)%n,yy=(y+dy[i]+m)%m;
		int pp=px+dx[i],qq=py+dy[i];
		if(a[xx][yy]) continue;
		if(!vis[xx][yy][0]) dfs(xx,yy,pp,qq);
		else if(vis[xx][yy][1]!=pp||vis[xx][yy][2]!=qq) {
		//	printf("%d %d\n",xx,yy);
			printf("Yes\n");
			exit(0);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	int bx=-1,by=-1;
	Fr(i,0,n) Fr(j,0,m) {
		char ch;cin>>ch;
		if(ch=='#') a[i][j]=1;
		else if(ch=='S') bx=i,by=j;
	} 
	dfs(bx,by,bx,by);
	printf("No\n");
	return 0;
}
