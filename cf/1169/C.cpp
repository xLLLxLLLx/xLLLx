#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
int n,k;
int a[N],b[N];

bool check(int x){
	fr(i,1,n) b[i]=a[i];
	fr(i,1,n) {
		int pos=(b[i-1]-b[i]+k)%k;
		if(pos<=x) b[i]=b[i-1];
		else if(b[i]<b[i-1]) return false;
	}
	return true;
}

int main(){
	scanf("%d%d",&n,&k);
	int flg=1;
	fr(i,1,n) {
		scanf("%d",&a[i]);
	}
	int l=0,r=k-1,ans=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}