#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
	LL t,w;
}a[N];

priority_queue<int, vector<int>, greater<int> > q;

bool cmp(data xx,data yy){
	return xx.w>yy.w;
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	LL ans=0,sum=0;
	fr(i,1,n) scanf("%lld%lld",&a[i].t,&a[i].w);
	sort(a+1,a+1+n,cmp);
	fr(i,1,k) q.push(a[i].t),sum+=a[i].t,ans=max(ans,sum*a[i].w);
	fr(i,k+1,n){
		LL h=q.top();
		if(h>=a[i].t) continue;
		q.pop(),q.push(a[i].t);
		sum-=h,sum+=a[i].t;
		ans=max(ans,sum*a[i].w);
	}
	printf("%lld\n",ans);
	return 0;
}