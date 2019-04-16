#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define se second
#define mp make_pair
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;
const int N=2e5+10,inf=1e9;
pair<int,int>a[N];
int root=0;
int tag[N],val[N],cal[N],d[N],rd[N],ch[N][2];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void down(int x){
	if(tag[x]){
		if(ls) tag[ls]+=tag[x],val[ls]+=tag[x];
		if(rs) tag[rs]+=tag[x],val[rs]+=tag[x];
		tag[x]=0;
	}
	if(cal[x]){
		if(ls) cal[ls]+=cal[x],d[ls]+=cal[x];
		if(rs) cal[rs]+=cal[x],d[rs]+=cal[x];
		cal[x]=0;
	}
}

void pushdown(int x){
	down(x);
	if(ls) pushdown(ls);
	if(rs) pushdown(rs);
}

void split(int rt,int &x,int &y,int v){
	if(!rt) { x=y=0; return ;}
	down(rt);
	if(val[rt]<v)
		x=rt,split(ch[x][1],ch[x][1],y,v);
	else 
		y=rt,split(ch[y][0],x,ch[y][0],v);
}

int merge(int x,int y){
	if(!x||!y) return x^y;
	if(rd[x]>rd[y]){
		down(x);
		ch[x][1]=merge(ch[x][1],y);
		return x;
	} else {
		down(y);
		ch[y][0]=merge(x,ch[y][0]);
		return y;
	}
}

int insert(int x,int y){
	int r1=0,r2=0;
	split(x,r1,r2,val[y]);
	r1=merge(r1,y);
	r1=merge(r1,r2);
	return r1;
}

int dfs(int x,int y){
	if(!x) return y;
	down(x);
	y=dfs(ls,y);
	y=dfs(rs,y);
	ls=rs=0;
	return insert(y,x);
}

void print(int x){
	if(!x) return ;
	if(ls) print(ls);
	printf("x=%d val=%d\n",x,val[x]);
	if(rs) print(rs);
}

int main(){
	int n;read(n);
	fr(i,1,n) {
		int q,c;read(c),read(q);
		a[i]=mp(-q,c);
	}
	sort(a+1,a+1+n);
	int m;read(m);
	fr(i,1,m){
		read(val[i]);
		rd[i]=rand()%inf;
		root=insert(root,i);
	}
	fr(i,1,n){
		int r1=0,r2=0,r3=0,r4=0;
		//print(root);
		//printf("?%d\n",a[i].se);
		split(root,r1,r2,a[i].se);
		val[r2]-=a[i].se,tag[r2]-=a[i].se;
		d[r2]++,cal[r2]++;
		split(r2,r3,r4,a[i].se-1);
		//printf("%d %d %d %d\n",r1,r2,r3,r4);
		r1=dfs(r3,r1);
		root=merge(r1,r4);
	}
	pushdown(root);
	fr(i,1,m) printf("%d ",d[i]);
	return 0;
}