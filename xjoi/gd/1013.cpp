#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=55;
struct data{
	int x,y,t;
};
queue<data>q;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int a[N][N],vis[N][N];
ll d[N][N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) fr(j,1,n) scanf("%d",&a[i][j]);
	int nw=0,res=0;
	ll ans=0;
	q.push((data){1,1,1}),vis[1][1]=1,d[1][1]=1;
	while(!q.empty()){
		nw++;
		while(!q.empty()&&q.front().t==nw){
			data h=q.front();q.pop();
			fr(o,0,3){
				int xx=h.x+dx[o],yy=h.y+dy[o];
				if(xx<1||xx>n||yy<1||yy>n||a[xx][yy]) continue;
				d[xx][yy]+=d[h.x][h.y];
				if(vis[xx][yy]) continue;
				q.push((data){xx,yy,nw+1}),vis[xx][yy]=1;
			}
		}
		if(d[n][n]) {
			res=nw+1;break;
		}
	}
	if(n==1) printf("1\n1\n");
	else printf("%lld\n%d\n",d[n][n],res);
	return 0;
}