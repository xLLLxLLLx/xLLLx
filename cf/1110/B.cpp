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
LL b[N],a[N];

bool cmp(LL x,LL y){
	return x>y;
}

int main(){
	int n,m,k;cin>>n>>m>>k;
	fr(i,1,n) scanf("%lld",&a[i]);
	if(k>=n) return printf("%d\n",n),0;
	fr(i,1,n-1) b[i]=a[i+1]-a[i]-1;
	sort(b+1,b+n,cmp);
	LL ans=a[n]-a[1]+1;
	fr(i,1,k-1) ans-=b[i];
	printf("%lld\n",ans);
	return 0;
}