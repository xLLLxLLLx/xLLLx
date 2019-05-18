#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
int a[N];

void fail(){
	printf("Infinite\n");
	exit(0);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	int ans=0;
	fr(i,2,n){
		if(a[i]+a[i-1]==5) fail();
		ans+=max(a[i],a[i-1])+1;
		if(i>=3&&a[i-2]==3&&a[i-1]==1&&a[i]==2) ans--;
	}
	printf("Finite\n");
	printf("%d\n",ans);
	return 0;
}