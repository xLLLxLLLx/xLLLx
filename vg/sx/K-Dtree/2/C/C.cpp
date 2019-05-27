#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
const ll inf=1e18;
struct data{
	int a[2];
}s[N],up[N],down[N];
int ch[N][2],pd;
ll dis[N],len[N];

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
	return A.a[pd]<B.a[pd] || (A.a[pd]==B.a[pd] && A.a[pd^1]<B.a[pd^1]);
}

#define ls ch[x][0]
#define rs ch[x][1]

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
	pd=pos,nth_element(s+l+1,s+mid+1,s+r+1,cmp);
	if(l<mid) {
		ch[mid][0]=build(l,mid-1,pos^1);
	} else ch[mid][0]=0;
	if(r>mid) {
		ch[mid][1]=build(mid+1,r,pos^1);
	} else ch[mid][1]=0;
	down[mid]=up[mid]=s[mid];
	upd(mid);
	return mid;
}

ll get(int x,int y){
	return abs(s[x].a[0]-s[y].a[0])+abs(s[x].a[1]-s[y].a[1]);
}

ll Len(int x,int now){
	ll ans=0;
	fr(i,0,1){
		if(down[x].a[i]>s[now].a[i]) ans+=down[x].a[i]-s[now].a[i];
		if(s[now].a[i]>up[x].a[i]) ans+=s[now].a[i]-up[x].a[i];
	}
	return ans;
}

ll Dist(int x,int now){
	ll ans=0;
	fr(i,0,1){
		ans+=max(abs(down[x].a[i]-s[now].a[i]),abs(up[x].a[i]-s[now].a[i]));
	}
	return ans;
}

void work(int now,int x,int cur){
	dis[now]=max(dis[now],get(now,x));
	ll tmp=ls ? Dist(ls,now) : 0;
	ll pos=rs ? Dist(rs,now) : 0;
	if(tmp>pos) {
		if(tmp>dis[now]) work(now,ls,cur^1);
		if(pos>dis[now]) work(now,rs,cur^1);
	} else {
		if(pos>dis[now]) work(now,rs,cur^1);
		if(tmp>dis[now]) work(now,ls,cur^1);
	}
}

void solve(int now,int x,int cur){
	if(now!=x) len[now]=min(len[now],get(now,x));
	ll tmp=ls ? Len(ls,now) : inf;
	ll pos=rs ? Len(rs,now) : inf;
	if(tmp<pos) {
		if(tmp<len[now]) solve(now,ls,cur^1);
		if(pos<len[now]) solve(now,rs,cur^1);
	} else {
		if(pos<len[now]) solve(now,rs,cur^1);
		if(tmp<len[now]) solve(now,ls,cur^1);
	}
}

int main(){
	int n;
	read(n);
	memset(len,0x3f,sizeof len);
	fr(i,1,n) fr(j,0,1) {
		read(s[i].a[j]);
	}
	int root=build(1,n,0);
	ll ans=1e18;
	fr(i,1,n) {
		work(i,root,0);
		solve(i,root,0);
		// printf("%lld %lld\n",dis[i],len[i]);
		ans=min(ans,dis[i]-len[i]);
	}
	printf("%lld\n",ans);
	return 0;
}