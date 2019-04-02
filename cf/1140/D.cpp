#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	LL ans=0;
	fr(i,1,n-2){
		LL x=i+1,y=i+2;
		ans+=x*y;
	}
	cout<<ans<<endl;
	return 0;
}