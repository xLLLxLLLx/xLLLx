#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int bx=-1,by=-1;
	int n;cin>>n;
	fr(i,1,n){
		int x;
		cin>>x;
		if(x) bx=i;
		else by=i;
	}
	printf("%d\n",min(bx,by));
	return 0;
}