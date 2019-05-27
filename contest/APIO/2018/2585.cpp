#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5010;
struct data{
	int id;
	ll x,y,r;
}a[N];
int mk[N];

bool cmp(data A,data B){
	if(A.r!=B.r) return A.r>B.r;
	else return A.id<B.id;
}

ll pf(ll x){
	return x*x;
}

bool check(int i,int j){
	return pf(a[i].x-a[j].x)+pf(a[i].y-a[j].y)<=pf(a[i].r+a[j].r);
}

int main(){
	int n;
	scanf("%d",&n);
	fr(i,1,n) {
		a[i].id=i;
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].r);
	}
	sort(a+1,a+1+n,cmp);
	fr(i,1,n) {
		if(mk[a[i].id]) continue;
		mk[a[i].id]=a[i].id;
		fr(j,1,n) {
			if(mk[a[j].id]) continue;
			if(check(i,j)) mk[a[j].id]=a[i].id;
		}
	}
	fr(i,1,n) {
		printf("%d ",mk[i]);
	}
	return 0;
}