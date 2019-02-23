/**/
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,mod=1e9+7,MK=(1<<3);
LL dp[N][MK];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,0,2) fr(j,1,n){
		char ch;cin>>ch;
		if(ch=='.') a[i][j]=1;
		else if(ch=='O') a[i][j]=2;
		else a[i][j]=3;
	}
	return 0;
}
