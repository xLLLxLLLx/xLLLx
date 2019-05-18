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
const int N=1e5+10,LOG=30;
struct data{
	int nt,to,w;
}a[N<<1];
int cnt=0;
int head[N],d[N],qx[LOG];

void add(int x,int y,int w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void insert(int x){
	// printf("xxx=%d\n",x);
	rf(i,29,0) {
		if(x&(1<<i)) {
			if(qx[i]==-1) {
				qx[i]=x;
				break;
			} else x^=qx[i];
		}
	}
}

void dfs(int x){
	// printf("x=%d\n",x);
	for(int i=head[x];i;i=a[i].nt) {
		int to=a[i].to;
		if(d[to]==-1) {
			d[to]=d[x]^a[i].w;
			dfs(to);
		} else {
			// if(to==1&&x==3) printf("%d %d %d\n",d[x],d[to],a[i].w);
			insert((d[x]^d[to])^a[i].w);
		}
	}
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,m) {
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w);
	}
	memset(d,-1,sizeof d),
	memset(qx,-1,sizeof qx);
	d[n]=0;
	dfs(n);
	if(d[n]==-1) return printf("-1\n"),0;
	int ans=d[1];
	// fr(i,0,29) {
	// 	if(qx[i]!=-1) printf("%d %d\n",i,qx[i]);
	// }
	rf(i,29,0) {
		if(ans&(1<<i)) {
			if(qx[i]!=-1) ans^=qx[i];
		}
	}
	printf("%d\n",ans);
	return 0;
}