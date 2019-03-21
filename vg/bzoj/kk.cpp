#include<iostream>
#include<cstdio>
#define N 300100
using namespace std;

int n,m,tt,dn[N],fa[N],son[N][2],xo[N];
bool fz[N];

inline bool as(int u){return son[fa[u]][1]==u;}
inline bool ar(int u){return son[fa[u]][0]!=u && son[fa[u]][1]!=u;}
inline void up(int u){if(u) xo[u]=xo[son[u][0]]^xo[son[u][1]]^dn[u];}
inline void down(int u)
{
	if(fz[u])
	{
		swap(son[u][0],son[u][1]);
		fz[son[u][0]]^=1;
		fz[son[u][1]]^=1;
		fz[u]=0;
	}
}

inline void rot(int u)
{
	down(fa[u]),down(u);
	int p=fa[u],d=as(u);
	if(!ar(p))
	{
		son[fa[p]][as(p)]=u;
	}
	fa[u]=fa[p];
	fa[p]=u;
	fa[son[u][!d]]=p;
	son[p][d]=son[u][!d];
	son[u][!d]=p;
	up(p),up(u);
}

inline void splay(int u)
{
	int p;
	for(; !ar(u);)
	{
		p=fa[u];
		if(!ar(p))
			as(u)==as(p)?rot(p):rot(u);
		rot(u);
	}
}

inline void acc(int u)
{
	int p,q;
	for(p=u,q=0; p; q=p,p=fa[p])
	{
		splay(p);
		down(p);
		son[p][1]=q;
		up(p);
	}
}

inline void make_root(int u)
{
	acc(u);
	splay(u);
	fz[u]^=1;
}

inline int find_root(int u)
{
	acc(u),splay(u),down(u);
	for(; son[u][0]; u=son[u][0],down(u));
	return u;
}

inline void spl(int u,int v)
{
	make_root(u);
	acc(v),splay(v);
}

inline void link(int u,int v)
{
	if(find_root(u)==find_root(v)) return;
	make_root(u),fa[u]=v;
}

inline void cut(int u,int v)
{
	spl(u,v);
	down(v),down(u);
	if(son[v][0]!=u || son[u][1]) return;
	fa[u]=son[v][0]=0;
	up(v);
}

int main()
{
	int i,j,o,p,q;
	cin>>n>>m;
	for(i=1; i<=n; i++)
	{
		scanf("%d",&dn[i]);
		xo[i]=dn[i];
	}
	for(i=1; i<=m; i++)
	{
		scanf("%d%d%d",&o,&p,&q);
		if(!o) spl(p,q),printf("%d\n",xo[q]);
		else if(o==1) link(p,q);
		else if(o==2) cut(p,q);
		else acc(p),splay(p),dn[p]=q,up(p);
	}
}

