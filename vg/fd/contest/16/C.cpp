#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
LL a[N],b[N],v[N];

int main(){
	int n;LL k;
	scanf("%d%lld",&n,&k);
	fr(i,1,n) scanf("%lld",&a[i]);
	LL sum=0,res=0;
	fr(i,1,n){
		LL pos=sum-(n-i)*a[i]*res;
	//	printf("%lld %lld\n",pos,res);
		if(pos<k){
			printf("%d\n",i);
			continue;
		} else {
			res++;
			sum+=(res-1)*1LL*a[i];
		}
	}
	return 0;
}
