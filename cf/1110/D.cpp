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
const int N=1e6+10;
int a[N];
int f[N][3][3];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) {
		int x;scanf("%d",&x);
		a[x]++;	
	}
	memset(f,-1,sizeof f);
	f[0][0][0]=0;
	fr(i,1,m) fr(j,0,2) fr(k,0,2) {
		if(f[i-1][j][k]==-1) continue;
		fr(l,0,2) {
			if(j+k+l>a[i]) break;
			f[i][k][l]=max(f[i][k][l],f[i-1][j][k]+l+(a[i]-l-k-j)/3);
		}
	}
	printf("%d\n",f[m][0][0]);
	return 0;
}