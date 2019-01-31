#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=(1<<16)+1,M=17;
struct data{
	int x,y;
}pt[M];
int dp[N],zt[M][M];

bool check(data A,data B,data C){
	return (A.y-B.y)*(C.x-A.x)==(A.x-B.x)*(C.y-A.y);
}

void Min(int &x,int y){
	x=min(x,y);
}

int main(){
	freopen("ouy","r",stdin);
	int T;scanf("%d",&T);
	fr(o,1,T){
		memset(zt,0,sizeof zt);
		int n;scanf("%d",&n);
		memset(dp,0x3f,sizeof dp);
		int mask=(1<<n)-1;
		fr(i,0,n-1) scanf("%d%d",&pt[i].x,&pt[i].y);
		fr(i,0,n-1)
		 fr(j,0,n-1){
		 	if(i==j) {
		 		zt[i][j]=(1<<i);
		 		continue;
		 	}
		 	zt[i][j]=((1<<i)|(1<<j));
		 	fr(k,0,n-1){
		 	 if(k==i||k==j) continue;
		 	 if(check(pt[i],pt[j],pt[k])) zt[i][j]|=(1<<k);
		 	}
		 }
		dp[0]=0;
		fr(i,0,mask-1){
			int pos=0;
			fr(j,0,n-1){
				if(!((i>>j)&1)) {
					pos=j;break;
				}
			}
			fr(j,0,n-1) {
				if(dp[i|zt[pos][j]]>dp[i]+1) dp[i|zt[pos][j]]=dp[i]+1;
			}
		}
		printf("Case %d: %d\n",o,dp[mask]);
	}
	return 0;
}
