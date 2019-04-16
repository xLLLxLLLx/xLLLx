#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;
const int N=1e5+10,inf=1e9;
int ch[N][2],rt[N],val[N],f[N],sz[N],rd[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int find(int k){ return f[k]==k ? f[k] : f[k]=find(f[k]); }

void up(int x){
	if(!x) return ;
	sz[x]=sz[ls]+sz[rs]+1;
}

void split(int r,int &x,int &y,int v){
	if(!r){ x=y=0; return ;}
	if(val[r]<v)
		x=r,split(ch[x][1],ch[x][1],y,v),up(x);
	else
		y=r,split(ch[y][0],x,ch[y][0],v),up(y);
}

int merge(int x,int y){
	if(!x||!y) return x^y;
	if(rd[x]>rd[y]){
		ch[x][1]=merge(ch[x][1],y);
		up(x);
		return x;
	} else {
		ch[y][0]=merge(x,ch[y][0]);
		up(y);
		return y;
	}
}

int insert(int x,int y){
	int r1=0,r2=0;
	split(x,r1,r2,val[y]);
	r1=merge(r1,y);
	x=merge(r1,r2);
	up(x);
	return x;
}

int dfs(int x,int y){
	if(!x) return y;
	y=dfs(ls,y);
	y=dfs(rs,y);
	ls=rs=0;
	return insert(y,x);
}

char lx[2];

void Merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(sz[rt[fx]]<sz[rt[fy]]) swap(fx,fy);
	rt[fx]=dfs(rt[fy],rt[fx]);
	f[fy]=fx;
	up(fx);
}

int Getkth(int x,int k){
	if(sz[ls]+1==k) return x;
	else if(sz[ls]>=k) return Getkth(ls,k);
	else return Getkth(rs,k-sz[ls]-1);
}

void print(int x){
	if(ls) print(ls);
	printf("%d %d sz=%d\n",x,val[x],sz[x]);
	if(rs) print(rs);
}

int main(){
	srand(time(NULL));
	int n,m;read(n),read(m);
	fr(i,1,n) f[i]=i,rt[i]=i,sz[i]=1;
	fr(i,1,n) read(val[i]),rd[i]=rand()%inf;
	fr(i,1,m){
		int x,y;
		read(x),read(y);
		Merge(x,y);
	}
	int q;read(q);
	fr(i,1,q){
		scanf("%s",lx+1);
		int x,y;read(x),read(y);
		if(lx[1]=='B') Merge(x,y);
		else {
			int fx=find(x);
			fx=rt[fx];
		//	printf("now%d %d\n",fx,sz[fx]);
		//	print(fx);
			if(sz[fx]<y) printf("-1\n");
			else printf("%d\n",Getkth(fx,y));
		}
	}
	return 0;
}