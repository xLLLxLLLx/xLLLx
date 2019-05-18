#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N];

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int lt=1;
	fr(i,1,n){
		while(a[lt]<i&&lt<=n) lt++;
		if(a[lt]<i) return printf("%d\n",i-1),0;
		lt++;
	}
	printf("%d\n",n);
	return 0;
}