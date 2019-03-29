#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define F(x) tree[x].fa
#define LC(x) tree[x].child[0]
#define RC(x) tree[x].child[1]
#define REV(x) tree[x].rev
#define Size 300010
using namespace std;
inline int read(){
	int sum=0,fg=1;char c=getchar();
	while(c<'0' || c>'9'){if(c=='-')fg=-1;c=getchar();}
	while(c>='0' && c<='9'){sum=sum*10+c-'0';c=getchar();}
	return sum*fg;
}
struct lct{
	int fa,child[2],rev,add;
	int v,MAX;
}tree[Size];
int be[Size],ne[Size],to[Size],e;
struct link_cut_tree{
	inline bool isroot(int x){
		return LC(F(x))!=x && RC(F(x))!=x;
	}
	inline void pushup(int x){
		tree[x].MAX=max(tree[LC(x)].MAX,tree[RC(x)].MAX);
		tree[x].MAX=max(tree[x].MAX,tree[x].v);
	}
	inline void pushdown(int x){
		if(REV(x)){
			REV(x)^=1;REV(LC(x))^=1;REV(RC(x))^=1;
			swap(LC(x),RC(x));
		}
	}
	void Pushdown(int x){
		if(!isroot(x))Pushdown(F(x));
		pushdown(x);
	}
	inline void rotate(int x){
		int A=F(x),B=F(A);bool w=(RC(A)==x);
		if(!isroot(A)){
			if(LC(B)==A)LC(B)=x;
			else if(RC(B)==A)RC(B)=x;
		}
		F(tree[x].child[w^1])=A;F(A)=x;F(x)=B;
		tree[A].child[w]=tree[x].child[w^1];tree[x].child[w^1]=A;
		pushup(A);pushup(x);
	}
	inline void splay(int x){
		Pushdown(x);
		while(!isroot(x)){
			if(!isroot(F(x)))rotate(x);
			rotate(x);
		}
	}
	inline void access(int x){
		for(int i=0;x;i=x,x=F(x))splay(x),RC(x)=i,pushup(x);
	}
	/*inline int find_root(int x){
		access(x);splay(x);
		while(LC(x))x=LC(x);
		return x;
	}*/
	inline void reverse(int x){
		access(x);splay(x);REV(x)^=1;
	}
	/*inline void link(int x,int y,int k){
		reverse(x);F(x)=y;tree[y].v=k;
	}
	inline void cut(int x,int y){
		reverse(x);access(y);splay(y);
		F(LC(y))=0;LC(y)=0;
	}*/
	inline void update(int x,int w){
		access(x);splay(x);tree[x].v=w;
		pushup(x);
	}
	inline int query(int x,int y){
		reverse(x);access(y);splay(y);
		return tree[y].MAX;
	}
}LCT;
void add(int x,int y){to[++e]=y;ne[e]=be[x];be[x]=e;}
void dfs(int x,int fa){
	for(int i=be[x];i;i=ne[i]){
		int v=to[i];
		if(v!=fa){
			tree[v].fa=x;
			dfs(v,x);
		}
	}
}
void init(){
	memset(be,0,sizeof(be));e=0;
	memset(tree,0,sizeof(tree));
}
struct node{
	int x,y,v;
}a[Size];
int main(){
	int Case=read();
	while(Case--){
		init();
		int n=read();
		for(int i=1;i<n;i++){
			int x=read(),y=read(),val=read();
			a[i].x=x,a[i].y=y;a[i].v=val;
			add(i+n,x);add(x,i+n);add(i+n,y);add(y,i+n);
		}
		char tp[10];
		dfs(1,1);
		for(int i=1;i<n;i++)
			LCT.update(i+n,a[i].v);
		while(1){
			scanf("%s",tp);
			if(tp[0]=='D')break;
			else if(tp[0]=='C'){
				int x=read(),val=read();
				LCT.update(x+n,val);
			}
			else{
				int x=read(),y=read();
				printf("%d\n",LCT.query(x,y));
			}
		}
	}
	return 0;
}
