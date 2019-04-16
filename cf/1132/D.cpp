#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	LL a,b,t;
	bool operator < (const data &C ) const {
		return t>C.t;
	}
}w[N];
int n,k;
priority_queue<data>q;

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void fail(){
	puts("-1");
	exit(0);
}

bool check(LL x){
	q=priority_queue<data>();
	fr(i,1,n) q.push(w[i]);
	fr(i,1,k){
		data h=q.top();q.pop();
		if(h.t<(i-1)) return false;
		h.a+=x,h.t+=h.a/h.b;
		h.a-=(h.a/h.b)*h.b;
		q.push(h);
	}
	return true;
}

int main(){
	read(n),read(k);
	fr(i,1,n) read(w[i].a);
	fr(i,1,n) read(w[i].b),w[i].t=w[i].a/w[i].b,w[i].a%=w[i].b;
	LL l=0,r=1e13,ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}