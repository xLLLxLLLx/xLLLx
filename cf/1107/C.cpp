#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
char lx[N];
LL a[N],b[N];

bool cmp(LL x,LL y){
	return x>y;
}

int main(){
	LL sum=0;
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) scanf("%lld",&a[i]);
	scanf("%s",lx+1);
	int res=0;b[++res]=a[1];
	fr(i,2,n){
		if(lx[i]!=lx[i-1]){
			sort(b+1,b+1+res,cmp);
			fr(j,1,min(k,res)) sum+=b[j];
			res=0;
		}
		b[++res]=a[i];
	}
	sort(b+1,b+1+res,cmp);
	fr(j,1,min(k,res)) sum+=b[j];
	printf("%lld\n",sum);
	return 0;
}