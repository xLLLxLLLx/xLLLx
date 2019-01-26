#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x) cout<<#x<<"="<<x<<endl;
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int l,r;
}qx[N];
int a[N];

int main(){
	int n;cin>>n;
	fr(i,1,n) cin>>a[i];
	int cnt=0,l=1;
	fr(i,2,n){
		if(a[i]<=a[i-1]) {
			qx[++cnt].l=l,qx[cnt].r=i-1;
			l=i;
		}
	}
	qx[++cnt].l=l,qx[cnt].r=n;
	int maxn=0;
	fr(i,1,cnt-1){
		if(qx[i].r>qx[i].l){
			if(a[qx[i].r+1]-a[qx[i].r-1]>=2) maxn=max(maxn,qx[i+1].r-qx[i].l+1);
			if(a[qx[i+1].l+1]-a[qx[i].r]>=2) maxn=max(maxn,qx[i+1].r-qx[i].l+1);
		}
	}
	fr(i,1,cnt) {
		maxn=max(maxn,qx[i].r-qx[i].l+1);
		if(qx[i].l>1||qx[i].r<n) maxn=max(maxn,qx[i].r-qx[i].l+2);
	}
	cout<<maxn<<endl;
	return 0;
}
