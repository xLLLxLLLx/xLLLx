#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10,K=110;
int n,k;
int a[N],lx[N],rx[N];
long long f[N][K],dp[N][K];

void work(int l,int r){
	if(l==r) {
		f[l][1]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	work(l,mid),work(mid+1,r);
	lx[mid+1]=0;
	for(int i=mid;i>=l;--i) {
		lx[i]=max(a[i],lx[i+1]);
	}
	rx[mid]=0;
	for(int i=mid+1;i<=r;++i) {
		rx[i]=max(a[i],rx[i-1]);
	}
	
	for(int i=mid+1;i<=r;++i) 
	 for(int j=1;j<=k;++j) {
	 	f[i][j]=dp[i][j];
	 }
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	work(1,n);
	printf("%lld\n",f[n][k]);
	return 0;
}