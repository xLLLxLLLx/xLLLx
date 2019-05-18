#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
int a[N][N],c[N];

void fail(){
	printf("NIE\n");
	exit(0);
}

int main(){
	int n,m;cin>>n>>m;
	fr(i,1,n) fr(j,1,m) cin>>a[i][j];
	int flg=0,tmp=0,res=0;
	fr(i,1,n){
		res^=a[i][1];
		fr(j,1,m) if(a[i][j]!=a[i][1]) flg=i,tmp=j;
	}
	if(!flg) {
		if(!res) fail();
		else {
			printf("TAK\n");
			fr(i,1,n) printf("1 ");
			return 0;
		}
	}
	res=0;
	fr(i,1,n) if(i!=flg) c[i]=1,res^=a[i][1];
	if(res^a[flg][tmp]) c[flg]=tmp;
	else c[flg]=1;
	printf("TAK\n");
	fr(i,1,n) printf("%d ",c[i]);
	return 0;
}