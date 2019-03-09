#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int mod=1e6+3;
LL ans=0;

int main(){
	int n;scanf("%d",&n);
	LL ans=1;
	fr(i,1,n-1) ans=ans*3%mod;
	cout<<ans<<endl;
	return 0;
}
