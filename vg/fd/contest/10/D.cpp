#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3010,M=1e6+10;
struct data{
	int nt,to;
}a[M<<1];
int dis[N][N],vis[N],head[N],cnt=0;
queue<int>q;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void spfa(int x){
	memset(dis[x],0x3f,sizeof dis[x]);
	dis[x][x]=0;
	q.push(x);vis[x]=1;
	while(!q.empty()){
		int h=q.front();q.pop();
		vis[h]=0;
		for(int i=head[h];i;i=a[i].nt){
			if(dis[x][h]+1<dis[x][a[i].to]) {
				dis[x][a[i].to]=dis[x][h]+1;
				if(!vis[a[i].to]) q.push(a[i].to);
				vis[a[i].to]=1;
			}
		}
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int s1,t1,l1,s2,t2,l2;
	scanf("%d%d%d%d%d%d",&s1,&t1,&l1,&s2,&t2,&l2);
	fr(i,1,n) spfa(i);
	if(l1<dis[s1][t1]||l2<dis[s2][t2]) return printf("-1\n"),0;
	int ans=dis[s1][t1]+dis[s2][t2];
	fr(i,1,n)
	 fr(j,1,n){
	 	int pos=dis[s1][i]+dis[i][j]+dis[j][t1];
	 	if(pos>l1) continue;
	 	int tmp=dis[s2][i]+dis[i][j]+dis[j][t2];
	 	if(tmp<=l2) ans=min(ans,tmp+pos-dis[i][j]);
	 	tmp=dis[t2][i]+dis[i][j]+dis[j][s2];
	 	if(tmp<=l2) ans=min(ans,tmp+pos-dis[i][j]);
	 }
	printf("%d\n",m-ans);
	return 0;
}
