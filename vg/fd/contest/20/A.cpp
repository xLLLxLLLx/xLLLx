#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int k,a,b,v;
	cin>>k>>a>>b>>v;
	int pos=b/(k-1),yu=b%(k-1),x=a/(k*v),sx=a%(k*v);
	if(sx) x++;
	int maxn=pos*k*v;
	if(yu) pos++,maxn+=(yu+1)*v;
	if(maxn>=a) printf("%d\n",x);
	else {
		int zz=a-maxn;
		int X=zz/v,Y=zz%v;
		if(Y) X++;
		printf("%d\n",pos+X);
	}
	return 0;
}
