#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n,m,r;
	cin>>n>>m>>r;
	int maxn=1000;
	fr(i,1,n){
		int x;cin>>x;
		maxn=min(maxn,x);
	}
	int maxm=0;
	fr(i,1,m){
		int x;cin>>x;
		maxm=max(maxm,x);
	}
	if(maxm<=maxn) printf("%d\n",r);
	else {
		int pos=r/maxn;
		r+=pos*(maxm-maxn);
		printf("%d\n",r);
	}
	return 0;
}