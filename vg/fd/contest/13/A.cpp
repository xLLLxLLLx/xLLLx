#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int x,y,z;cin>>x>>y>>z;
	int minn=min(x,y);
	if(minn>=2*z) printf("First\n");
	else printf("Second\n");
	return 0;
}
