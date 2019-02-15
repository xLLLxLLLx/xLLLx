#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int x,y;cin>>x>>y;
	int ans=0,yu=0;
	while(x){
		ans+=x;
		int pos=(x+yu)/y;
		yu=(x+yu)%y;
		x=pos;
	}
	printf("%d\n",ans);
	return 0;
}
