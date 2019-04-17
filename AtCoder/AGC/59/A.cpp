#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	int maxn=1e9;
	fr(i,-100,100){
		int pos=0;
		fr(j,1,n){
			pos+=(a[j]-i)*(a[j]-i);
		}
		maxn=min(maxn,pos);
	}
	cout<<maxn<<endl;
	return 0;
}