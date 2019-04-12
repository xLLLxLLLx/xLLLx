#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=5010;
vector<int>qx[N];
int vis[N],pa[N],dep[N],is_h[N],h[N],g[N];
int n,m,cnt=0,res=0,now=0,nx=-1,ny=-1,WOC=0;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void rd(){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
}

void dfs(int u,int fa){
	if(u==nx&&fa==ny) return ;
	if(u==ny&&fa==nx) return ;
	pa[++res]=u;
	sort(qx[u].begin(),qx[u].end());
	int len=qx[u].size();
	fr(i,0,len-1){
		if(qx[u][i]!=fa) dfs(qx[u][i],u);
	}
}

void gao(){
	int fa=h[now];
	if(h[1]<h[now-1]) {
		int flg=0;
		fr(i,2,now-2){
			if(h[i]>h[now-1]) {
				nx=h[i],ny=h[i-1],flg=1;
				break;
			}
		}
		if(!flg) nx=fa,ny=h[now-1];
	} else {
		int flg=0;
		rf(i,now-2,2){
			if(h[i]>h[1]) {
				nx=h[i],ny=h[i+1],flg=1;
				break;
			}
		}
		if(!flg) nx=fa,ny=h[1];
	}
//	printf("%d %d\n",nx,ny);
}

void Get_h(int u,int fa){
	if(WOC) return ;
	int len=qx[u].size();
	vis[u]=1,dep[u]=dep[fa]+1,g[u]=fa;
	fr(i,0,len-1){
		if(qx[u][i]!=fa) {
			if(!vis[qx[u][i]]) Get_h(qx[u][i],u);
			else {
				int pos,tt;
				if(dep[qx[u][i]]>dep[u]) pos=qx[u][i],tt=u;
				else pos=u,tt=qx[u][i];
				for(;pos!=tt;pos=g[pos]) h[++now]=pos;
				h[++now]=pos;
				WOC=1;
				return ;
			}
		}
		if(WOC) return ;
	}
}

int main(){
	rd();
	read(n),read(m);
	for(int i=1,x,y;i<=m;++i){
		read(x),read(y);
		qx[x].push_back(y),qx[y].push_back(x);
	}
	if(n==m) Get_h(1,0),gao();
	dfs(1,0);
	fr(i,1,n) printf("%d ",pa[i]);
	return 0;
}
