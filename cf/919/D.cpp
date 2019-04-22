#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10,M=30;
struct data{
	int nt,to;
}a[N<<1];
queue<int>q;
char lx[N];
int f[N][M],head[N],vis[N],c[N],d[N],cnt=0;

void add(int x,int y){
	d[y]++;
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	scanf("%s",lx+1);
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	fr(i,1,n) if(!d[i]) q.push(i),f[i][lx[i]-'a'+1]=1;
	int tot=n;
	while(!q.empty()){
		int nw=q.front();q.pop();
		tot--;
		for(int i=head[nw];i;i=a[i].nt){
			int to=a[i].to;
			d[to]--;
			fr(j,1,26) 
				if(f[to][j]<f[nw][j]+(lx[to]-'a'+1==j)) f[to][j]=f[nw][j]+(lx[to]-'a'+1==j);
			if(!d[to]) q.push(to);
		}
	}
	if(tot) return printf("-1\n"),0;
	int maxn=0;
	fr(i,1,n) fr(j,1,26) maxn=max(maxn,f[i][j]);
	cout<<maxn<<endl;
	return 0;
}