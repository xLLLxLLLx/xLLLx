#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=2e5+10;
int a[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	int yu=0;
	fr(i,1,n) {
		scanf("%d",&a[i]);
		yu+=a[i];
		printf("%d ",yu/m);
		yu%=m;
	} 
	return 0;
}