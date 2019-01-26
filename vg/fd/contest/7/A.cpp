#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x) cout<<#x<<"="<<x<<endl;
#define LL long long
using namespace std;
const int N=310;
int a[N];

int main(){
	int n,p;cin>>p>>n;
	fr(i,1,n) {
		int x;cin>>x;
		int pos=x%p;
		if(a[pos]) return printf("%d\n",i),0;
		else a[pos]=1;
	}
	printf("-1\n");
	return 0;
}
