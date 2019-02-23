#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	int ans=1,a=0,b=0;
	fr(i,1,n){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==a&&y==b) continue;
		ans+=max(0,min(x,y)-max(a,b)+1);
		if(a==b) ans--;
		a=x,b=y;
	}
	cout<<ans<<endl;
	return 0;
}
