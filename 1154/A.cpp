#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5;
int a[N],d[N],c[N],vis[N];

int main(){
	fr(i,1,4) cin>>a[i];
	sort(a+1,a+1+4);
	fr(i,1,3) printf("%d ",a[4]-a[i]);
	return 0;
}