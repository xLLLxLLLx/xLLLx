#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=4010,mod=998244353;
LL jc[N]={1},ny[N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y+mod)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

LL q_pow(LL x,int y=mod-2){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

LL C(int x,int y){
	if(x==y||!y) return 1;
	LL pos=mul(jc[x],mul(ny[y],ny[x-y]));
	//printf("%d %d %lld\n",x,y,pos);
	return pos;
}

int main(){
	int n,k;scanf("%d%d",&k,&n);
	fr(i,1,n+k) jc[i]=jc[i-1]*1LL*i%mod,ny[i]=q_pow(jc[i]);
	fr(i,2,2*k){
		int gg=i/2;
		if(i-i/2>k) gg=0;
		else if(i>k+1) gg-=(i-k-1);
		LL ans=0;
		//printf("zz%d %d\n",i,gg);
		fr(j,0,gg) {
			if(j*2>n) break;
			//printf("j=%d gg=%d n-2*j+k-1=%d k-1=%d\n",j,gg,n-2*j+k-1,k-1);
			LL pos=mul(C(gg,j),C(n-2*j+k-1,k-1));
			//printf("%lld\n",pos);
			if(j&1) Add(ans,-pos);
			else Add(ans,pos);
		}
		printf("%lld\n",ans);
	}
	return 0;
}