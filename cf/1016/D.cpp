#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=110;
int a[N][N],r[N],c[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	int res=0;
	fr(i,1,n) scanf("%d",&r[i]),res^=r[i];
	fr(i,1,m) scanf("%d",&c[i]),res^=c[i];
	if(res) return printf("NO\n"),0;
	fr(i,1,n-1) a[i][m]=r[i],res^=r[i];
	fr(i,1,m-1) a[n][i]=c[i]; 
	a[n][m]=res^c[m];
	printf("YES\n");
	fr(i,1,n){
		fr(j,1,m) printf("%d ",a[i][j]);
		puts("");
	}
	return 0;
}