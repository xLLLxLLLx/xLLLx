#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n<<1){
		char ch;
		cin>>ch;
		a[i]=ch-'0';
	}
	sort(a+1,a+1+n),sort(a+1+n,a+1+n*2);
	if(a[1]<a[n+1]) {
		fr(i,1,n){
			if(a[i]>=a[i+n]) return printf("NO\n"),0;
		}
		printf("YES\n");
	}
	else if(a[1]>a[n+1]) {
		fr(i,1,n){
			if(a[i]<=a[i+n]) return printf("NO\n"),0;
		}
		printf("YES\n");
	}
	else printf("NO\n");
	return 0;
}
