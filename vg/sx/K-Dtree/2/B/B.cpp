#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
const int inf=1e9;
struct data{
	int a[3],c[2];
}s[N<<1],down[N<<1],up[N<<1],q;
int pd,ans;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void Min(int &x,int y){
	x=min(x,y);
}

void Max(int &x,int y){
	x=max(x,y);
}

bool cmp(data A,data B){
	return A.a[pd]<B.a[pd] || (A.a[pd]==B.a[pd]&&A.a[pd^1]<B.a[pd^1]);
}

#define ls s[x].c[0]
#define rs s[x].c[1] 

void upd(int x){
	if(ls) {
		Min(down[x].a[0],down[ls].a[0]);
		Min(down[x].a[1],down[ls].a[1]);
		Max(up[x].a[0],up[ls].a[0]);
		Max(up[x].a[1],up[ls].a[1]);
	}
	if(rs) {
		Min(down[x].a[0],down[rs].a[0]);
		Min(down[x].a[1],down[rs].a[1]);
		Max(up[x].a[0],up[rs].a[0]);
		Max(up[x].a[1],up[rs].a[1]);
	}
}

inline int build(int l,int r,int pos){
	int mid=(l+r)>>1;
	pd=pos,nth_element(s+l+1,s+mid+1,s+r+1,cmp);
	if(l<mid) {
		s[mid].c[0]=build(l,mid-1,pos^1);
	} else s[mid].c[0]=0;
	if(r>mid) {
		s[mid].c[1]=build(mid+1,r,pos^1);
	} else s[mid].c[1]=0;
	up[mid]=down[mid]=s[mid];
	upd(mid);
	return mid;
}

inline int Dist(int x){
	int res=0;
	fr(i,0,1) {
		if(q.a[i]<down[x].a[i]) res+=down[x].a[i]-q.a[i];
		if(q.a[i]>up[x].a[i]) res+=q.a[i]-up[x].a[i];
	}
	return res;
}

void work(int x) {
	Min(ans,abs(s[x].a[0]-q.a[0])+abs(s[x].a[1]-q.a[1]));
	int pos=ls ? Dist(ls) : inf;
	int tmp=rs ? Dist(rs) : inf;
	if(pos<tmp) {
		if(pos<ans) work(ls);
		if(tmp<ans) work(rs);
	} else {
		if(tmp<ans) work(rs);
		if(pos<ans) work(ls);
	}
}

void insert(int x,int rt){
	int cur=0;
	for(;;) {
		Min(down[rt].a[0],down[x].a[0]);
		Min(down[rt].a[1],down[x].a[1]);
		Max(up[rt].a[0],up[x].a[0]);
		Max(up[rt].a[1],up[x].a[1]);
		if(s[x].a[cur]<s[rt].a[cur]) {
			if(s[rt].c[0]) rt=s[rt].c[0];
			else {
				s[rt].c[0]=x;
				return ;
			}
		} else {
			if(s[rt].c[1]) rt=s[rt].c[1];
			else {
				s[rt].c[1]=x;
				return ;
			}
		}
		cur^=1;
	}
}

int main(){
	int n,m;
	read(n),read(m);
	fr(i,1,n) fr(j,0,1) {
		read(s[i].a[j]);
	}
	int now=build(1,n,0);
	fr(i,1,m) {
		int t,x,y;
		read(t),read(x),read(y);
		if(t==1) {
			++n;
			up[n].a[0]=down[n].a[0]=s[n].a[0]=x;
			up[n].a[1]=down[n].a[1]=s[n].a[1]=y;
			insert(n,now);
		} else {
			ans=inf;
			q.a[0]=x,q.a[1]=y;
			work(now);
			printf("%d\n",ans);
		}
	}
	return 0;
}