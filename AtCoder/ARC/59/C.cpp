#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=410,mod=1e9+7;
int a[N],b[N];
LL f[N][N],jc[N],qz[N][N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

LL add(LL x,LL y){
	return (x+y+mod)%mod;
}

int main(){
	int n,c;scanf("%d%d",&n,&c);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n) scanf("%d",&b[i]);
	fr(i,1,N-1) jc[i]=1,qz[0][i]=qz[0][i-1]+1;
	fr(i,1,c)
		fr(j,1,N-1) Mul(jc[j],j),qz[i][j]=add(qz[i][j-1],jc[j]);
	f[0][0]=1;
	fr(i,1,n) fr(j,0,c){
		fr(k,0,j) Add(f[i][j],mul(f[i-1][j-k],add(qz[k][b[i]],-qz[k][a[i]-1])));
	}
	printf("%lld\n",f[n][c]);
	return 0;
}