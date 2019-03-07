#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N];

int main(){
	int n;scanf("%d",&n);
	int ans1=0,ans2=0;
	fr(i,1,n) {
		scanf("%d",&a[i]);
		if(a[i]>0) ans1++;
		if(a[i]<0) ans2++;
	}
	int pos=n/2;
	if(n&1) pos++;
	if(ans1>=pos) printf("1\n");
	else if(ans2>=pos) printf("-1\n");
	else printf("0\n");
	return 0;
}
