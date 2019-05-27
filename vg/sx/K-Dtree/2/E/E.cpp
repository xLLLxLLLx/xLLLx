#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
struct data{
	int a[2];
}s[N],up[N],down[N];
int ch[N][2],pd;
priority_queue<ll,vector<ll>,greater<ll> >q;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

#define ls ch[x][0]
#define rs ch[x][1]

bool cmp(data A,data B){
	return A.a[pd]<B.a[pd] || (A.a[pd]==B.a[pd] && A.a[pd^1]<B.a[pd^1]);
}

void Min(int &x,int y){
	x=min(x,y);
}

void Max(int &x,int y){
	x=max(x,y);
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
	int x=(l+r)>>1;
	pd=pos,nth_element(s+l,s+x,s+r+1,cmp);
	if(l<x) {
		ls=build(l,x-1,pos^1);
	} else ls=0;
	if(r>x) {
		rs=build(x+1,r,pos^1);
	} else rs=0;
	down[x]=up[x]=s[x];
	upd(x);
	return x;
}

ll pf(ll x){
	return x*x;
}

ll Dist(int x,int now){
	ll ans=0;
	fr(i,0,1) {
		ans+=max(pf(down[x].a[i]-s[now].a[i]),pf(up[x].a[i]-s[now].a[i]));
	}
	return ans;
}

ll get(int x,int y){
	ll ans=0;
	fr(i,0,1) {
		ans+=pf(s[x].a[i]-s[y].a[i]);
	}
	return ans;
}

void work(int now,int x){
	ll dis=get(now,x);
	if(dis>q.top()) {
		q.pop();
		q.push(dis);
	}
	ll tmp=ls ? Dist(ls,now) : 0;
	ll pos=rs ? Dist(rs,now) : 0;
	if(tmp>pos) {
		if(tmp>q.top()) work(now,ls);
		if(pos>q.top()) work(now,rs);
	} else {
		if(pos>q.top()) work(now,rs);
		if(tmp>q.top()) work(now,ls);
	}
}

int main(){
	int n,k;
	read(n),read(k);
	fr(i,1,n) fr(j,0,1) {
		read(s[i].a[j]);
	}
	int now=build(1,n,0);
	fr(i,1,k*2) q.push(0);
	fr(i,1,n) {
		work(i,now);
	}
	printf("%lld\n",q.top());
	return 0;
}