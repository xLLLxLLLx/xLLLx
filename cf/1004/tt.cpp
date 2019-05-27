#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e6+10;
int t,a[N],b[N];

int main(){
	scanf("%d",&t);
	int mx=0;
	fr(i,1,t) {
		int x;
		scanf("%d",&x);
		a[x]++;
		mx=max(mx,x);
	}
	int x=0;
	fr(i,1,t) {
		if(a[i]!=i*4) {
			x=i;
			break;
		}
	}
	fr(i,1,t) {
		if(t%i) continue;
		int n=i,m=t/i;
		int y=n+m-mx-x;
		if(abs(n-x)+abs(m-y)!=mx) continue;
		memset(b,0,sizeof b);
		fr(j,1,n) fr(k,1,m) {
			b[abs(j-x)+abs(k-y)]++;
		}
		int flg=1;
		fr(j,0,n+m) 
			if(a[j]!=b[j]) {
				flg=0;
			}
		if(flg) {
			printf("%d %d\n",n,m);
			printf("%d %d\n",x,y);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}