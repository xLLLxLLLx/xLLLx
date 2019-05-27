#include<iostream>
#include<cstdio>
#include<algorithm>
#define C ch=getchar()
#define S 0.75
#define INF 0x3f3f3f3f
#define N 500010
using namespace std;

int n,m,mx,sta[N],top,rt,nw,id,tt,ans;
char ch;
struct Dn
{
	int num[2];
} tmp[N],t;
struct Node
{
	int fa,ls,rs,size,mn[2],mx[2];
	bool ws;
	Dn it;
} node[1001000];

bool operator < (const Dn &u,const Dn &v)
{
	return u.num[nw]<v.num[nw];
}

inline void Min(int &u,int v)
{
	if(v<u) u=v;
}
inline void Max(int &u,int v)
{
	if(v>u) u=v;
}
inline int newn()
{
	return top?sta[top--]:++mx;
}
inline int len(int u)
{
	return abs(node[u].it.num[0]-t.num[0])+abs(node[u].it.num[1]-t.num[1]);
}
inline int gd(int now)
{
	int res=0,i;
	for(i=0;i<2;i++)
		res+=max(0,t.num[i]-node[now].mx[i])+max(0,node[now].mn[i]-t.num[i]);
	return res;
}
inline int read()
{
	static int res;
	for(C; ch<'0'; C);
	for(res=ch-'0',C; ch>='0'; res=res*10+ch-'0',C);
	return res;
}
inline void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

inline void up(int now)
{
	int i,L=node[now].ls,R=node[now].rs;
	for(i=0; i<2; i++)
	{
		node[now].mn[i]=node[now].mx[i]=node[now].it.num[i];
		if(L) Max(node[now].mx[i],node[L].mx[i]),Min(node[now].mn[i],node[L].mn[i]);
		if(R) Max(node[now].mx[i],node[R].mx[i]),Min(node[now].mn[i],node[R].mn[i]);
	}
	node[now].size=node[L].size+node[R].size+1;
}

int build(int l,int r,int last)
{
	if(l>r) return 0;
	int now=newn(),mid=((l+r)>>1);
	nw=node[now].ws=node[last].ws^1;
	node[now].fa=last;
	nth_element(tmp+l,tmp+mid,tmp+r+1);
	node[now].it=tmp[mid];
	node[now].ls=build(l,mid-1,now);
	node[now].rs=build(mid+1,r,now);
	up(now);
	return now;
}

void add(int &now,int last)
{
	if(!now)
	{
		now=newn();
		node[now].ws=node[last].ws^1;
		node[now].fa=last;
		node[now].it=t;
		up(now);
		return;
	}
	nw=node[now].ws;
	if(t<node[now].it)
		add(node[now].ls,now);
	else
		add(node[now].rs,now);
	up(now);
	if(max(node[node[now].ls].size,node[node[now].rs].size)>node[now].size*S) id=now;
}

void dfs(int now)
{
	if(!now) return;
	sta[++top]=now;
	tmp[++tt]=node[now].it;
	dfs(node[now].ls),dfs(node[now].rs);
}

inline void rb(int now)
{
	int t2=node[now].fa;
	tt=0;
	dfs(now);
	node[now].fa=t2;
	t2?node[t2].ls==now?node[t2].ls=build(1,tt,t2):node[t2].rs=build(1,tt,t2):rt=build(1,tt,0);
}

void ask(int now)
{
	if(!now) return;
	nw=node[now].ws;
	Min(ans,len(now));
	if(t<node[now].it)
	{
		ask(node[now].ls);
		nw=node[now].ws;
		if(gd(node[now].rs)<ans) ask(node[now].rs);
	}
	else
	{
		ask(node[now].rs);
		nw=node[now].ws;
		if(gd(node[now].ls)<ans) ask(node[now].ls);
	}
}

int main()
{
	int i,j,o;
	cin>>n>>m;
	for(i=1; i<=n; i++)
		tmp[i].num[0]=read(),tmp[i].num[1]=read();
	rt=build(1,n,0);
	for(i=1; i<=m; i++)
	{
		if(read()==1)
		{
			t.num[0]=read(),t.num[1]=read();
			id=0;
			add(rt,0);
			if(id) rb(id);
		}
		else ans=INF,t.num[0]=read(),t.num[1]=read(),ask(rt),write(ans),puts("");
	}
}