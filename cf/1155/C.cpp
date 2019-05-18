#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define db double
using namespace std;
const int N=3e5+10;
ll a[N],p[N];

ll gcd(ll A,ll B){
	return B ? gcd(B,A%B) : A;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,m) scanf("%lld",&p[i]);
	ll be=a[1],gg=0;
	fr(i,2,n){
		gg=gcd(gg,a[i]-a[i-1]);
	}
	//cout<<gg<<endl;
	fr(i,1,m){
		if(gg%p[i]) continue;
		printf("YES\n");
		printf("%lld %d\n",be,i);
		return 0;
	}
	printf("NO\n");
	return 0;
}