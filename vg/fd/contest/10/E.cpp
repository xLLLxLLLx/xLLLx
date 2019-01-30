#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=25,M=(1<<20)+1;
char lx[N][N];
int zt[N][N];
LL a[N][N],val[N][N],dp[M],c[N][N];

int lowerbit(int x){
	return x&(-x);
}

void Min(LL &x,LL y){
	x=min(x,y);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,0,n-1) scanf("%s",lx[i]+1);
	fr(i,0,n-1) fr(j,1,m) scanf("%lld",&a[i][j]);
	fr(i,0,n-1) fr(j,1,m) {
		LL maxn=0;
		fr(k,0,n-1){
			if(lx[i][j]!=lx[k][j]) continue;
			zt[i][j]|=(1<<k),val[i][j]+=a[k][j];
			maxn=max(maxn,a[k][j]);
		}
		if(zt[i][j]!=(1<<i)) c[i][j]=a[i][j];
		val[i][j]-=maxn;
		//printf("%d %d %d %lld\n",i,j,zt[i][j],val[i][j]);
	}
	int mask=(1<<n)-1;
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	fr(o,0,mask-1) {
		int pos;
		fr(i,0,n-1) {
			if(!((o>>i)&1)) {pos=i;break;}
		}
		fr(i,1,m) {
			Min(dp[o|zt[pos][i]],dp[o]+val[pos][i]);
			Min(dp[o|(1<<pos)],dp[o]+c[pos][i]);
		}
	}
	//fr(o,0,mask-1) printf("%d %lld\n",o,dp[o]);
	printf("%lld\n",dp[mask]);
	return 0;
}
