#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	long double l,r,k;cin>>l>>r>>k;
	long double pos=1;
	int res=0;
	for(;;){
		if(pos>r) break;
		if(pos>=l&&pos<=r){
			res++;LL tmp=pos;
			cout<<tmp<<" ";
		}
		pos*=k;
	}
	if(!res) printf("-1\n");
	return 0;
}
