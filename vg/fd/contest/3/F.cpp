#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const int N=55;
struct data{
	db a,b;
}qx[N];

bool cmp(data xx,data yy){
	return xx.x>yy.x;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lf",&qx[i].a);
	fr(i,1,n) scanf("%lf",&qx[i].b);
	sort(qx+1,qx+1+n,cmp);
	db l=0,r=1e18;
	while(l<=r
	return 0;
}
