#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
multiset<int>q[N][N];
int b[N];
int a[N][N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) fr(j,1,n) scanf("%d",&a[i][j]);
	fr(i,1,n) scanf("%d",&b[i]);
	LL sum=0;
	fr(k,1,n) fr(i,1,n) fr(j,1,n) {
		q[i][j].insert(a[i][k]+a[k][j]);
	}
	fr(i,1,n) fr(j,1,n) a[i][j]=*(q[i][j].begin()),sum+=a[i][j];
	printf("%lld ",sum);
	puts("");
	fr(o,1,n-1){
		int pos=b[o];
		fr(i,1,n) sum-=a[i][pos]+a[pos][i],a[pos][i]=a[i][pos]=0;
		fr(i,1,n) fr(j,1,n) {
			if(i==pos||j==pos) continue;
			sum-=a[i][j];
			q[i][j].erase(*(q[i][j].find(a[i][pos]+a[pos][j])));
			printf("%d %d %d\n",i,j,a[i][j]);
			a[i][j]=*(q[i][j].begin());
			printf("XG%d\n",a[i][j]);
			sum+=a[i][j];
		}
		if(o==1) fr(i,1,n) fr(j,1,n) {
			printf("%d %d %d\n",i,j,a[i][j]);
		}
		printf("%lld ",sum);
	}
	return 0;
}
