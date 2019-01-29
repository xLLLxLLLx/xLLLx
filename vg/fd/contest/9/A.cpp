#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int l,r;
	LL w;
}b[N];
LL a[N],d[N],c[N],qz[N];

int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,m) scanf("%d%d%lld",&b[i].l,&b[i].r,&b[i].w);
	fr(i,1,k){
		int x,y;scanf("%d%d",&x,&y);
		c[x]++,c[y+1]--;
	}
	fr(i,1,m) c[i]+=c[i-1];
	fr(i,1,m){
		d[b[i].l]+=c[i]*b[i].w;
		d[b[i].r+1]-=c[i]*b[i].w;
	}
	fr(i,1,n) d[i]+=d[i-1],a[i]+=d[i];
	fr(i,1,n) printf("%lld ",a[i]);
	return 0;
}
