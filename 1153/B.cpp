#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int c[N],r[N],a[N][N],nc[N],nr[N];

int main(){
	int n,m,h;cin>>n>>m>>h;
	fr(i,1,m) scanf("%d",&c[i]);
	fr(i,1,n) scanf("%d",&r[i]);
	fr(i,1,n) fr(j,1,m) scanf("%d",&a[i][j]);
	fr(i,1,n) fr(j,1,m){
		if(!a[i][j]) continue;
		a[i][j]=min(r[i],c[j]);
	}
	fr(i,1,n){
		fr(j,1,m) printf("%d ",a[i][j]);
		puts("");
	}
	return 0;
}