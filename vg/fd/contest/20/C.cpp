#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=25;
int a[N][N];

int main(){
	int t;scanf("%d",&t);
	fr(o,1,t){
		int n,k;scanf("%d%d",&n,&k);
		memset(a,0,sizeof a);
		fr(i,1,5) fr(j,i+1,5) a[i][j]=a[j][i]=1;
		fr(i,6,n) a[i][1]=a[1][i]=1,a[i][2]=a[2][i]=1;
		fr(i,1,n) fr(j,1,n){
			if(i==j) continue;
			if(!k) break;
			if(!a[i][j]) a[i][j]=a[j][i]=1,k--;
		}
		fr(i,1,n) fr(j,i+1,n) if(a[i][j]) printf("%d %d\n",i,j);
	}
	return 0;
}
