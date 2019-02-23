#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
LL a[N],b[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	fr(i,1,n){
		if(i&1) b[i/2+1]=a[i];
		else b[n-(i/2)+1]=a[i];
	}
	fr(i,1,n) cout<<b[i]<<" ";
	return 0;
}
