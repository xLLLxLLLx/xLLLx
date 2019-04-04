#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010*2;
struct node{
	int v,s;
}b[N];
struct data{
	int nt,to;
}a[N<<1];
int cnt=0,head[N],q[N],ans[N],mx[N],mk[N],vis[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	//printf("%d %d\n",x,y);
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

bool dfs(int x){
	for(int i=head[x];i;i=a[i].nt){
		int to=a[i].to;
		if(vis[to]) continue;
		vis[to]=1;
		if(!mx[to]||dfs(mx[to])){
			mx[to]=x;
			return true;
		}
	}
	return false;
}

int main(){
	int n,m;read(n),read(m);
	int maxn=0;
	fr(i,1,n) read(b[i].v),b[i].v++,maxn=max(maxn,b[i].v);
	fr(i,1,n) read(b[i].s);
	int d;read(d);
	fr(i,1,d) read(q[i]),mk[q[i]]=1;
	fr(i,1,n) if(!mk[i]) add(b[i].v,b[i].s+maxn);
	memset(ans,-1,sizeof ans);
	fr(i,1,maxn) {
		memset(vis,0,sizeof vis);
		if(!dfs(i)) {ans[d]=i-1;break;}
	}
	if(ans[d]==-1) ans[d]=maxn;
	rf(i,d-1,1){
		add(b[q[i+1]].v,b[q[i+1]].s+maxn);
		fr(j,ans[i+1]+1,maxn){
			memset(vis,0,sizeof vis);
			if(!dfs(j)) {ans[i]=j-1;break;}
		}
		if(ans[i]==-1) ans[i]=maxn;
	}
	fr(i,1,d) printf("%d\n",ans[i]);
	return 0;
}