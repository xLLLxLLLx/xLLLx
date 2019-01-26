#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=1e5+10,M=1e6+10;
struct data{
	int nt,to;
	LL w;
}a[N<<1];
LL v[M<<2],Ti,dp[N],f[N];
int head[N],cnt=0,n,w[M<<2],nm[N],s[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void read(LL &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,LL w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].w=w,a[cnt].nt=head[y],head[y]=cnt;
}

void pushdown(int x){
	
}

int find(int x,int l,int r,LL T){
	int mid=(l+r)>>1;
	if(v[x]<T) return w[index];
	pushdown(x);
	if(v[lson]>T) return find(lson,l,mid,T);
	else return w[lson]+find(rson,mid+1,r,T-v[lson]);
}

void change(int x,int l,int r,int L,int k){
	if(l<=L&&L<=R) {
		w[
		pushup(x);
	}
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=a[i].nt){
		
	}
}

int main(){
	read(n),read(Ti);
	fr(i,1,n) read(nm[i]);
	fr(i,1,n) read(s[i]);
	fr(i,2,n){
		int x;LL w;
		read(x),read(w);
		add(x,i,w);
	}
	dfs(1,0);
	printf("%lld\n",dp[1]);
	return 0;
}
