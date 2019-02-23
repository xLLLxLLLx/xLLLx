#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=110;
struct data{
	int to,nt;
}a[N<<1];
vector<int>q[N];
int cnt=0,head[N],vs[N],g[N],dep[N];

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1,g[u]=fa;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to!=fa) dfs(a[i].to,u);
	}
}

int main(){
	int n,m;read(n),read(m);
	for(int i=1,x,y;i<n;++i){
		read(x),read(y);
		add(x,y);
	}
	fr(i,1,m){
		int x,y;
		read(x),read(y);
		q[x].push_back(i);
		q[y].push_back(i);
	}
	dfs(1,1);
	int ans=0;
	fr(i,1,n) fr(j,i+1,n){
		memset(vs,0,sizeof vs);
		int tt=i,dd=j;
		while(tt!=dd){
			if(dep[tt]<dep[dd]) swap(tt,dd);
			int len=q[tt].size();
			fr(i,0,len-1) vs[q[tt][i]]++;
			tt=g[tt];
		}
		int len=q[tt].size();
		fr(i,0,len-1) vs[q[tt][i]]++;
		int flg=0;
		fr(k,1,m) if(vs[k]==2) flg=1;
		if(!flg) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
