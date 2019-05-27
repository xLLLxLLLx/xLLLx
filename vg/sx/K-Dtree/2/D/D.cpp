#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
struct data{
	int a[2];
}s[N],down[N],up[N],q;
struct node{
	int nt,to;
}g[N];
int cnt=0,res=0,ans=0;
int ch[N][2],ed[N],lz[N],st[N],dep[N],col[N],head[N],pd;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
	g[++cnt].to=y,g[cnt].nt=head[x],head[x]=cnt;
}

void Min(int &x,int y){
	x=min(x,y);
}

void Max(int &x,int y){
	x=max(x,y);
}

void dfs(int u){
	st[u]=++res;
	for(int i=head[u];i;i=g[i].nt) {
		int to=g[i].to;
		dep[to]=dep[u]+1;
		dfs(to);
	}
	ed[u]=res;
}

#define ls ch[x][0]
#define rs ch[x][1]

bool cmp(data A,data B){
	return A.a[pd]<B.a[pd] || (A.a[pd]==B.a[pd]&&A.a[pd^1]<B.a[pd^1]);
}

void upd(int x){
	if(ls) {
		fr(i,0,1) {
			Min(down[x].a[i],down[ls].a[i]);
			Max(up[x].a[i],up[ls].a[i]);
		}
	}
	if(rs) {
		fr(i,0,1) {
			Min(down[x].a[i],down[rs].a[i]);
			Max(up[x].a[i],up[rs].a[i]);
		}
	}
}

int build(int l,int r,int pos){
	int mid=(l+r)>>1;
	pd=pos,nth_element(s+l,s+mid,s+r+1,cmp);
	if(l<mid) {
		ch[mid][0]=build(l,mid-1,pos^1);
	} else ch[mid][0]=0;
	if(mid<r) {
		ch[mid][1]=build(mid+1,r,pos^1);
	} else ch[mid][1]=0;
	up[mid]=down[mid]=s[mid];
	upd(mid),lz[mid]=0;
	// printf("mid=%d %d %d\n",mid,s[mid].a[0],s[mid].a[1]);
	return mid;
}

bool check(int x,int y){
	fr(i,0,1) 
		if(s[x].a[i]!=s[y].a[i]) {
			return false;
		}
	return true;
}

void find(int x,int pos){
	// printf("now=%d x=%d pos=%d\n",now,x,pos);
	if(lz[x]) {
		col[x]=lz[x];
		col[ls]=lz[ls]=lz[x];
		col[rs]=lz[rs]=lz[x];
		lz[x]=0;
	}
	if(q.a[0]==s[x].a[0]&&q.a[1]==s[x].a[1]) {
		ans=col[x];
		return ;
	}
	if(q.a[pos]<s[x].a[pos]) {
		find(ls,pos^1);
	} else if(q.a[pos]>s[x].a[pos]){
		find(rs,pos^1);
	} else {
		if(q.a[pos^1]<s[x].a[pos^1]){
			find(ls,pos^1);
		} else {
			find(rs,pos^1);
		}
	}
}

void go(int x,int l,int r,int L,int R,int z){
	// printf("x=%d l=%d r=%d L=%d R=%d z=%d\n",x,l,r,L,R,z);
	if(lz[x]) {
		col[x]=lz[x];
		col[ls]=lz[ls]=lz[x];
		col[rs]=lz[rs]=lz[x];
		lz[x]=0;
	}
	if(l<=s[x].a[0]&&s[x].a[0]<=r)
		if(L<=s[x].a[1]&&s[x].a[1]<=R) {
			col[x]=z;
		}
	if(l<=down[x].a[0]&&up[x].a[0]<=r)
		if(L<=down[x].a[1]&&up[x].a[1]<=R) {
			lz[x]=z;
			return ;
		}
	if(ls) {
		// printf("ls=%d\n",ls);
		if(down[ls].a[0]>r||up[ls].a[0]<l||down[ls].a[1]>R||up[ls].a[1]<L) 2333;
		else go(ls,l,r,L,R,z);
	}
	if(rs) {
		// printf("rs=%d %d\n",rs);
		if(down[rs].a[0]>r||up[rs].a[0]<l||down[rs].a[1]>R||up[rs].a[1]<L) 2333;
		else go(rs,l,r,L,R,z);
	}
}

int main(){
	int T;read(T);
	fr(i,1,N-1) col[i]=1;
	fr(o,1,T) {
		int n,c,m;
		cnt=res=0;
		read(n),read(c),read(m);
		fr(i,2,n) {
			int x;
			read(x);
			add(x,i);
		}
		dep[1]=1,dfs(1);
		fr(i,1,n) {
			s[i].a[0]=st[i],s[i].a[1]=dep[i];
		}
		// fr(i,1,n) {
		// 	printf("i=%d %d %d %d\n",i,s[i].a[0],s[i].a[1],ed[i]);
		// }
		int root=build(1,n,0);
		// fr(x,1,n) {
		// 	printf("x=%d ls=%d rs=%d a[0]=[%d,%d] a[1]=[%d,%d]\n",x,ls,rs,down[x].a[0],up[x].a[0],down[x].a[1],up[x].a[1]);
		// }
		ll sum=0;
		fr(i,1,m) {
			int x,y,z;
			read(x),read(y),read(z);
			if(!z) {
				q.a[0]=st[x],q.a[1]=dep[x];
				find(root,0);
				// printf("%d\n",ans);
				sum+=1ll*ans*i%mod;
				sum%=mod;
			} else {
				go(root,st[x],ed[x],dep[x],dep[x]+y,z);
			}
		}
		printf("%lld\n",sum);
		fr(i,1,n) col[i]=1,head[i]=0;
	}
	return 0;
}
