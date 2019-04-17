#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
struct data{
	LL a,b,k;
}w[N];
LL f[N][N];

bool cmp(data A,data B){
	return A.b>B.b;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld%lld%lld",&w[i].a,&w[i].b,&w[i].k);
	LL maxn=0;
	sort(w+1,w+1+n,cmp);
	fr(i,1,n) fr(j,0,i){
		if(j) f[i][j]=max(f[i-1][j-1]+w[i].a-(j-1)*1LL*w[i].b,f[i][j]);
		f[i][j]=max(f[i][j],f[i-1][j]+max(w[i].a-w[i].k*w[i].b,0LL));
		maxn=max(maxn,f[i][j]);
	}
	printf("%lld\n",maxn);
	return 0;
}