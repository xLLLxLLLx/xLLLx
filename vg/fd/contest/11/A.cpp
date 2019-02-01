#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55;
int a[N][N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n){
		if(i&1) fr(j,1,m) a[i][j]=1;
		else {
			if(i%4==0) a[i][1]=1;
			else a[i][m]=1;
		}
	}
	fr(i,1,n) {
		fr(j,1,m){
			if(a[i][j]) cout<<"#";
			else cout<<".";
		}
		cout<<endl;
	}
	return 0;
}
