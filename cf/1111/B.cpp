#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
db a[N];

int main(){
	int n;
	db k,m;scanf("%d%lf%lf",&n,&k,&m);
	db sum=0;
	fr(i,1,n) scanf("%lf",&a[i]),sum+=a[i];
	sort(a+1,a+1+n);
	db pos=min(m,n*k);
	db ans=(sum+pos)/double(n);
	fr(i,1,n-1){
		if(!m) break;
		m--;
		sum-=a[i];
		db add=min(m,(n-i)*k);
		ans=max(ans,(add+sum)/double(n-i));
	} 
	printf("%.12f\n",ans);
	return 0;
}
