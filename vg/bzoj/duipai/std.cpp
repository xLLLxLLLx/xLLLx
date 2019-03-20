#include<cstdio>
#include<iostream>
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,m,sz;
int root[200005],ls[2000005],rs[2000005],v[2000005],deep[2000005];
void build(int &k,int l,int r)
{
	k=++sz;
	if(l==r){v[k]=l;return;}
	int mid=(l+r)>>1;
	build(ls[k],l,mid);
	build(rs[k],mid+1,r);
}
void modify(int l,int r,int x,int &y,int pos,int val)
{
	y=++sz;
	if(l==r){v[y]=val;deep[y]=deep[x];return;}
	ls[y]=ls[x];rs[y]=rs[x];
	int mid=(l+r)>>1;
	if(pos<=mid)
		modify(l,mid,ls[x],ls[y],pos,val);
	else modify(mid+1,r,rs[x],rs[y],pos,val);
}
int query(int k,int l,int r,int pos)
{
	if(l==r)return k;
	int mid=(l+r)>>1;
	if(pos<=mid)return query(ls[k],l,mid,pos);
	else return query(rs[k],mid+1,r,pos);
}
void add(int old,int &nw,int l,int r,int pos)
{
  nw=++sz;ls[nw]=ls[old],rs[nw]=rs[old];
	if(l==r){deep[nw]=deep[old]+1,v[nw]=v[old];return;}
	int mid=(l+r)>>1;
	if(pos<=mid)add(ls[nw],ls[nw],l,mid,pos);
	else add(rs[nw],rs[nw],mid+1,r,pos);
}
int find(int k,int x)
{
    int p=query(k,1,n,x);
	if(x==v[p])return p;
    return find(k,v[p]);
}
int main()
{
	n=read();m=read();
	build(root[0],1,n);
	int f,k,a,b;
	for(int i=1;i<=m;i++)
	{
		f=read();
		if(f==1)
		{
			root[i]=root[i-1];
			a=read();b=read();
			int p=find(root[i],a),q=find(root[i],b);
			if(v[p]==v[q])continue;
			if(deep[p]>deep[q])swap(p,q);
			modify(1,n,root[i],root[i],v[p],v[q]);
			if(deep[p]==deep[q])add(root[i],root[i],1,n,v[q]);
		}
		if(f==2)
		{k=read();root[i]=root[k];}
		if(f==3)
		{
			root[i]=root[i-1];
			a=read();b=read();
		    int p=find(root[i],a),q=find(root[i],b);
			if(v[p]==v[q])puts("1");
			else puts("0");
		}
	}
	return 0;
}
