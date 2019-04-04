#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
LL a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	LL ans=0,lmt=1e10;
	rf(i,n,1){
		if(lmt>a[i]) ans+=a[i],lmt=a[i];
		else {
			if(lmt-1<=0) break;
			ans+=lmt-1;
			lmt--;
		}
	}
	cout<<ans<<endl;
	return 0;
}