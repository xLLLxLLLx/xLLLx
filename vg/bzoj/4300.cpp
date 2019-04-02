#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=1e5+10;
int a[N],dp[31];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	int maxn=1;
	fr(i,1,n) {
		int pos=0;
		fr(j,0,30) if((a[i]>>j)&1) pos=max(pos,dp[j]); 
		fr(j,0,30) if((a[i]>>j)&1) dp[j]=max(dp[j],pos+1);
	}
	fr(i,0,30) maxn=max(maxn,dp[i]);
	cout<<maxn<<endl;
	return 0;
}