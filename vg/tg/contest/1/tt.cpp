#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const db pi=acos(-1);

int main(){
	db x,y;cin>>x>>y;
	cout<<atan(y/x)/pi*180.0<<endl;
	return 0;
}
