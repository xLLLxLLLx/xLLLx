#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N];

bool cmp(int x,int y){
	return x>y;
}

int main(){
	int n;scanf("%d",&n);
	int sum=0;
	fr(i,1,n) scanf("%d",&a[i]),sum+=a[i];
	sort(a+1,a+1+n,cmp);
	sum=sum/2+1;
	int ans=0;
	fr(i,1,n) {
		if(sum<=0) break;
		sum-=a[i];
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
