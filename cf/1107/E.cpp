#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
char lx[N];
int qz[N];
LL a[N],f[N][N][N];

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,n) fr(j,1,i) a[i]=max(a[i],a[i-j]+a[j]);
	//fr(i,1,n) printf("a[%d]=%lld\n",i,a[i]);
	fr(i,1,n) fr(j,i+1,n) qz[i]+=(lx[i]==lx[j]);
	rf(i,n,1) fr(j,i,n) {
		fr(k,i,j-1){
			if(lx[k]!=lx[j]) continue;
			fr(t,0,qz[j]) f[i][j][t]=max(f[i][j][t],f[k+1][j-1][0]+f[i][k][t+1]);
		}
		fr(k,0,qz[j]) f[i][j][k]=max(f[i][j][k],f[i][j-1][0]+a[k+1]);
	}
	printf("%lld\n",f[1][n][0]);
	return 0;
}