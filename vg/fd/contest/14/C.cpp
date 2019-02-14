#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
LL a[N],b[N],c[N];

int main(){
	int n;LL k;cin>>n>>k;
	fr(i,1,n) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	int res=0;
	b[++res]=1,c[res]=a[1];
	fr(i,2,n){
		if(a[i]==a[i-1]) b[res]++;
		else b[++res]=1,c[res]=a[i];
	}
	fr(i,1,res){
		LL tmp=b[i]*(n*1LL);
		if(k<=tmp){
			LL x=k/b[i],y=k%b[i];
			if(y) x++;
			return printf("%lld %lld\n",c[i],a[x]),0;
		}
		k-=tmp;
	}
	return 0;
}
