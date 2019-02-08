#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int n,k;
LL A,B;
int a[N];

LL find(int l,int r){
	int mid=(l+r)>>1;
	int num=upper_bound(a+1,a+1+k,r)-lower_bound(a+1,a+1+k,l);
	if(!num) return A;
	LL sum=B*1LL*num*1LL*(r-l+1);
//	printf("%d %d %d %lld\n",num,l,r,sum);
	if(l==r) return sum;
	LL pos=min(sum,find(l,mid)+find(mid+1,r));
//	printf("%d %d %lld\n",l,r,pos);
	return pos;
}

int main(){
	scanf("%d%d%lld%lld",&n,&k,&A,&B);
	fr(i,1,k) scanf("%d",&a[i]);
	sort(a+1,a+1+k);
	printf("%lld\n",find(1,1<<n));
	return 0;
}