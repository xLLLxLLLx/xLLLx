#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
LL a[N];

int main(){
	int n,k,m;cin>>n>>m>>k;
	fr(i,1,n) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	LL x=m/(k+1),yu=m%(k+1);
	LL ans=x*(k*a[n]+a[n-1])+yu*a[n];
	cout<<ans<<endl;
	return 0;
}
