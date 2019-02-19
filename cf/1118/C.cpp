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
using namespace std;
const int N=2e5+10;
int a[N];

int main(){
	int n,m;cin>>n>>m;
	fr(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	rf(i,n,1){
		int nw=n-i;
		int pos=max(0,a[i]-nw);
		printf("%d\n",pos);
		m-=pos;
		if(m<=0) return printf("%d\n",nw+1),0;
	}
	printf("-1\n");
	return 0;
}