#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,mod=1e9+7;
int m;
struct data{
	LL a[N][N];
};

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
	return x*y%mod;
}

data mul(data A,data B){
	data tmp;
	fr(i,1,m) fr(j,1,m){
		tmp.a[i][j]=0;
		fr(k,1,m){
			Add(tmp.a[i][j],mul(A.a[i][k],B.a[k][j]));
		}
	}
	return tmp;
}

LL q_pow(LL y){
	data tmp,qx;
	fr(i,1,m) fr(j,1,m) tmp.a[i][j]=(i==j);
	fr(i,2,m) qx.a[i-1][i]=1;
	qx.a[m][m]=1,qx.a[m][1]=1;
	for(;y;y>>=1){
		if(y&1) tmp=mul(tmp,qx);
		qx=mul(qx,qx);
	}
	LL pos=0;
	fr(i,1,m) Add(pos,tmp.a[m][i]);
	Add(pos,tmp.a[m][m]);
	return pos; 
}

int main(){
	LL k;
	cin>>k>>m;
	if(k<m) return printf("1\n"),0;
	printf("%lld\n",q_pow(k-m));
	return 0;
}
