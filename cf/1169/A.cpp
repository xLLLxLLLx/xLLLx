#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n,a,x,b,y;
	cin>>n>>a>>x>>b>>y;
	for(;;) {
		a++,b--;
		if(a==n+1) a=1;
		if(!b) b=n;
		if(a==b) return printf("Yes\n"),0;
		if(a==x) break;
		if(b==y) break;
	}
	printf("NO\n");
	return 0;
}