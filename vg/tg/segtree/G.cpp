#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls (x<<1)
#define rs (x<<1|1)
#define ll long long
using namespace std;
const int N=5e4+10;
struct data{
	int nt,to;
}a[N];
int b[N],ys[N],c[N],d[N],f[N],st[N],ed[N];
int head[N],cnt=0,res=0;

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
}

bool cmp(int x,int y){
	return b[x]>b[y];
}

void dfs(int u){
	st[u]=++res,sy[res]=u;
	for(int i=head[u];i;i=a[i].nt)
		dfs(a[i].to);
	ed[u]=res;
}

void change(int x,int l,int r,int L,int v){
	if(l==r){
		tr[x]=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(ls,l,mid,L,v);
	else change(rs,mid+1,r,L,v);
	tr[x]=max(tr[ls],tr[rs]);
}

void find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) {
		mx=max(mx,tr[x]);
		return ;
	}
	int mid=(l+r)>>1;
	if(R<=mid) find(ls,l,mid,L,R);
	else if(L>mid) find(rs,mid+1,r,L,R);
	else find(ls,l,mid,L,R),find(rs,mid+1,r,L,R);
}

int main(){
	int T;read(T);
	fr(o,1,T){
		int n,m;read(n),read(m);
		fr(i,2,n){
			int p;read(p);
			p++,add(p,i);
			read(b[i]),read(c[i]);
		}
		dfs(1);
		fr(i,1,n) f[i]=i;
		sort(f+1,f+1+n,cmp);
		int flg=0;
		for(int i=1,j;i<=n;i=j){
			for(j=i+1;j<=n;++j)
				if(b[f[j]]!=b[f[i]]) break;
			fr(k,i,j-1) d[f[k]]=find(1,1,n,st[f[k]],ed[f[k]]).id;
			fr(k,i,j-1) change(1,1,n,st[f[k]],c[f[k]]);
		}
		fr(i,1,m){
			int x;read(x);
			printf("%d\n",d[x+1]-1);
		}
		res=cnt=0;
		fr(i,1,n) head[i]=0,d[i]=1;
		fr(i,1,n*4) tr[i]=(node){0,0};
	}
	return 0;
}