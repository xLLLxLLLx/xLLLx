#include<bits/stdc++.h>
#define rep(X,A,B) for(int X=A;X<=B;X++)
#define tep(X,A,B) for(int X=A;X>=B;X--)
#define LL long long
const int N=10010;
const int M=20010;
using namespace std;

char em[20];
int n,m,tot=0,dfn[N],rt[N],hlp[N];
int fa[N],mx[N],val[N],son[N][2];
int edge[M],lst[N],nxt[M],id[M],wei[M],t=0;

void ADD(int x,int y,int z,int idd){
	edge[++t]=y;nxt[t]=lst[x];lst[x]=t;wei[t]=z;id[t]=idd;
}

int APL(int v){
	tot++;
	rt[tot]=1;
	val[tot]=mx[tot]=v;
	son[tot][0]=son[tot][1]=fa[tot]=0;
}

void CHK(int x){
	mx[x]=val[x];
	if(son[x][0]) mx[x]=max(mx[x],mx[son[x][0]]);
	if(son[x][1]) mx[x]=max(mx[x],mx[son[x][1]]);
	return;
}

void SEARCH(int x,int dad){
	fa[hlp[x]]=hlp[dad];
	for(int r=lst[x];r;r=nxt[r]){
		if(edge[r]==dad)continue;
		hlp[edge[r]]=dfn[id[r]]=APL(wei[r]);
		SEARCH(edge[r],x);
	}
}

int get(int x){
	return x==son[fa[x][1]];
}

void RTT(int x){
	int y=fa[x],z=fa[y],d=get(x);
	int pd=get(y);
	if(son[x][d^1])son[y][d]=son[x][d^1],fa[son[x][d^1]]=y;
		else son[y][d]=0;
	son[x][d^1]=y;fa[y]=x;
	fa[x]=z;
	if(rt[y])rt[x]=1,rt[y]=0;else son[z][pd]=x;
	CHK(y);CHK(x);
}

void SPL(int x){
	while(!rt[x]){
		if(!rt[fa[x]])RTT(get(x)==get(fa[x])?fa[x]:x);
		RTT(x);
	}
}

void ACSS(int x){
	int las=0,now=x;
	while(now){
		SPL(now);
		rt[son[now][1]]=1;
		rt[las]=0;
		son[now][1]=las;
		CHK(now);
		las=now;
		now=fa[now];
	}
	return;
}

int GET(int x,int y){
	ACSS(x);
	int las=0,now=y;
	while(now){
		SPL(now);
		if(fa[now]==0)break;
		rt[son[now][1]]=1;
		rt[las]=0;
		son[now][1]=las;
		CHK(now);
		las=now;
		now=fa[now];
	}
	int res;
	res=max(mx[las],mx[son[now][1]]);
	return res;
}

void SSOLVE(){
	int u,v,w;
	t=tot=0;
	memset(lst,0,sizeof(lst));
	memset(son,0,sizeof(son));
	memset(rt,1,sizeof(rt));
	scanf("%d",&n);
	rep(i,1,n-1){
		scanf("%d%d%d",&u,&v,&w);
		ADD(u,v,w,i);
		ADD(v,u,w,i);
	}
	hlp[1]=APL(0);
	SEARCH(1,0);
	while(1){
		scanf("%s",em+1);
		if(em[1]=='D')break;
		if(em[1]=='C'){
			scanf("%d%d",&u,&w);
			SPL(dfn[u]);
			val[dfn[u]]=w;
			CHK(dfn[u]);
		}
		else{
			scanf("%d%d",&u,&v);
      if(u==v) printf("0\n");
			else printf("%d\n",GET(hlp[u],hlp[v]));
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--)SSOLVE();
	return 0;
}
