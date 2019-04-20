#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
priority_queue<int,vector<int>,greater<int> >q;
int a[N],n,T;

bool check(int x){
	int nw=0,maxn=0;
	fr(i,1,n){
		if(i>x) nw=q.top(),q.pop();
		q.push(nw+x);
		maxn=max(maxn,nw+x);
	}
	return maxn<=T;
}

int main(){
	scanf("%d%d",&n,&T);
	fr(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	reverse(a+1,a+1+n);
	int l=1,r=n,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}