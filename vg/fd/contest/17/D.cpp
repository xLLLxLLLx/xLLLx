#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson (x<<1)
#define rson (x<<1|1)
#define LL long long
#define db double
using namespace std;
const int N=2e5+10;
struct data{
	LL val;int fg;
};
LL v[N<<2],flg[N<<2],w[N<<1],Val[N],INF=1e18;
int head[N],Next[N<<1],to[N<<1],sz[N],dep[N],tp[N],s[N],id[N],f[N],ys[N];
int cnt=0,res=0,n,m;

db mul(db x,db y){
	return x*y;
}

bool check(db x,db y,db z){
	db pos=mul(x,y);
	return pos<=z;
}

void add(int x,int y,LL W){
	to[++cnt]=y,w[cnt]=W,Next[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,w[cnt]=W,Next[cnt]=head[y],head[y]=cnt;
}

void dfs1(int u,int fa){
	f[u]=fa,dep[u]=dep[fa]+1,sz[u]=1;
	for(int i=head[u];i;i=Next[i]){
		if(to[i]==fa) continue;
		Val[to[i]]=w[i],dfs1(to[i],u);
		ys[(i+1)/2]=to[i];
		sz[u]+=sz[to[i]];
		if(sz[s[u]]<sz[to[i]]) s[u]=to[i];
	}
}

void dfs2(int u,int v){
	id[u]=++res;tp[u]=v;
	if(s[u]) dfs2(s[u],v);
	else return ;
	for(int i=head[u];i;i=Next[i])
		if(!tp[to[i]]) dfs2(to[i],to[i]);
}

void change(int x,int l,int r,int L,LL k){
	if(l==r&&l==L){
		v[x]=k;flg[x]=(k>INF);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	flg[x]=(flg[lson]|flg[rson]);
	if(!flg[x]){
		if(check(v[lson],v[rson],INF)) v[x]=v[lson]*v[rson];
		else flg[x]=1;
	}
}

data find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return (data){v[x],flg[x]};
	int mid=(l+r)>>1;
	if(R<=mid) return find(lson,l,mid,L,R);
	else if(L>mid) return find(rson,mid+1,r,L,R);
	else {
		data zz=find(lson,l,mid,L,R),xx=find(rson,mid+1,r,L,R);
		if(zz.fg||xx.fg) return (data){0,1};
		else {
			if(check(zz.val,xx.val,INF)) return (data){zz.val*xx.val,0};
			else return (data){0,1};
		}
	}
}

LL Get(int x,int y,LL pos){
	int F=0,fx=tp[x],fy=tp[y];
	LL tmp=1;
	for(;fx!=fy;){
		if(dep[fx]>dep[fy]){
			data zz=find(1,1,n,id[fx],id[x]);
			if(zz.fg){F=1;break;}
			if(check(tmp,zz.val,pos)) tmp*=zz.val;
			else {F=1;break;}
			x=f[fx],fx=tp[x];
		} else {
			data zz=find(1,1,n,id[fy],id[y]);
			if(zz.fg){F=1;break;}
			if(check(tmp,zz.val,pos)) tmp*=zz.val;
			else {F=1;break;}
			y=f[fy],fy=tp[y];	
		}
	}
	if(!F){
		if(dep[x]>dep[y]){
			data zz=find(1,1,n,id[y]+1,id[x]);
			if(zz.fg) F=1;
			else if(check(tmp,zz.val,pos)) tmp*=zz.val;
			else F=1;
		}
		else if(dep[x]<dep[y]){
			data zz=find(1,1,n,id[x]+1,id[y]);
			if(zz.fg) F=1;
			else if(check(tmp,zz.val,pos)) tmp*=zz.val;
			else F=1;
		}
	}
	if(F) return 0LL;
	else return pos/tmp;
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n-1){
		int x,y;LL W;
		scanf("%d%d%lld",&x,&y,&W);
		add(x,y,W);
	}
	dfs1(1,1),dfs2(1,1);
	fr(i,1,n*4) v[i]=1;
	fr(i,2,n) change(1,1,n,id[i],Val[i]);
	fr(i,1,m){
		int tp,x,y;LL W;
		scanf("%d",&tp);
		if(tp==1){
			scanf("%d%d%lld",&x,&y,&W);
			printf("%lld\n",Get(x,y,W));
		} else {
			scanf("%d%lld",&x,&W);
			change(1,1,n,id[ys[x]],W);
		}
	}
	return 0;
}
