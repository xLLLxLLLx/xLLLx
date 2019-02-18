#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	LL w;
	bool operator < (const data &C) const{
		return w>C.w;
	}
};
priority_queue<data>qj,qs;
LL a[N],qz[N],d[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,n-1) d[i]=abs(a[i+1]-a[i]);
	fr(i,1,n-1){
		qz[i]=qz[i-1];
		if(i&1) qz[i]+=d[i];
		else qz[i]-=d[i];
	}
	LL maxn=0;
	qj.push((data){0});qs.push((data){0});
	fr(i,1,n-1){
		LL pos=qj.top().w,tmp=qs.top().w;
	//	printf("%lld %lld\n",pos,tmp);
		maxn=max(maxn,qz[i]-pos);
		maxn=max(maxn,-qz[i]-tmp);
		if(i&1) qs.push((data){-qz[i]});
		else qj.push((data){qz[i]});
	}
	cout<<maxn<<endl;
	return 0;
}
