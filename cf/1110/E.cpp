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
LL a[N],b[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,n) scanf("%lld",&b[i]);
	rf(i,n,1) a[i]-=a[i-1],b[i]-=b[i-1];
	sort(a+1,a+1+n),sort(b+1,b+1+n);
	fr(i,1,n) if(a[i]!=b[i]) return printf("No\n"),0;
	printf("Yes\n");
	return 0;
}