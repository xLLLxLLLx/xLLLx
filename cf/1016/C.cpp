#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=3e5+10;
LL a[3][N],qz[N],tot[3][N],h[3][N];

int main(){
	int n;scanf("%d",&n);
	fr(i,0,1) fr(j,1,n) scanf("%lld",&a[i][j]);
	LL maxn=0,res=0,sum=0;
	fr(i,1,n) qz[i]=qz[i-1]+a[0][i]+a[1][i];
	fr(i,0,0) fr(j,1,n){
		tot[i][j]=res*a[i][j];
		res++;
		sum+=tot[i][j];
	}
	fr(i,1,1) rf(j,n,1){
		tot[i][j]=res*a[i][j];
		res++;
		sum+=tot[i][j];
	}
	fr(i,1,n) h[0][i]=sum,sum-=tot[0][i]+tot[1][i];
	res=0,sum=0;
	fr(i,1,1) fr(j,1,n){
		tot[i][j]=res*a[i][j];
		res++;
		sum+=tot[i][j];
	}
	fr(i,0,0) rf(j,n,1){
		tot[i][j]=res*a[i][j];
		res++;
		sum+=tot[i][j];
	}
	fr(i,1,n) h[1][i]=sum,sum-=tot[0][i]+tot[1][i];
	//fr(i,0,1) fr(j,1,n) printf("h[%d][%d]=%lld\n",i,j,h[i][j]);
	LL pos=0;res=0;
	int nw=0;
	maxn=h[0][1];
	fr(i,1,n){
		pos+=res*a[nw][i]+(res+1)*a[nw^1][i];
		res+=2,nw^=1;
		maxn=max(maxn,pos+h[nw][i+1]+(qz[n]-qz[i])*(res-i));
	}
	cout<<maxn<<endl;
	return 0;
}