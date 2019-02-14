#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
map<int,int>mp[N];

int main(){
	int n;cin>>n;
	mp[1][2]=1,mp[1][3]=1;
	fr(i,1,n) mp[i].clear();
	return 0;
}
