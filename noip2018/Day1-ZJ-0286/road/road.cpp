#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1e5+10;
LL a[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

LL Abs(LL x){
	if(x<0) return -x;
	else return x;
}

void rd(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
}

int main(){
	rd();
	int n;read(n);
	fr(i,1,n) scanf("%lld",&a[i]);
	LL sum=0;
	fr(i,1,n+1) sum+=Abs(a[i]-a[i-1]);
	printf("%lld\n",sum/2);
	return 0;
}
