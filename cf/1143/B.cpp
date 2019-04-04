#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=20;
int a[N],b[N];

int main(){
	LL n,ans=1,maxn=0;
	cin>>n;
	for(;n;n/=10) b[++b[0]]=n%10;
	fr(i,1,b[0]) a[i]=b[b[0]-i+1];
	a[0]=b[0];
	fr(i,1,a[0]){
		if(a[i]) {
			LL pos=ans*(a[i]-1);
			if(!pos) pos=1;
			fr(j,i+1,a[0]) pos*=9;
			maxn=max(maxn,pos);
		}
		ans*=a[i];
	}
	maxn=max(maxn,ans);
	cout<<maxn<<endl;
	return 0;
}