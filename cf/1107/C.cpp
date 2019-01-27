#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int c[N];
LL a[N],w[N];

bool cmp(LL x,LL y){
	return x>y;
}

int main(){
	int n,k;cin>>n>>k;
	fr(i,1,n) cin>>w[i];
	fr(i,1,n) {
		char ch;cin>>ch;
		c[i]=ch-'a'+1;
	}
	LL ans=0;
	a[++a[0]]=w[1];
	fr(i,2,n){
		if(c[i]==c[i-1]) a[++a[0]]=w[i];
		else {
			sort(a+1,a+1+a[0],cmp);
			fr(j,1,min(a[0],k*1LL)) ans+=a[j];
			a[0]=0;
			a[++a[0]]=w[i];
		}
	}
	sort(a+1,a+1+a[0],cmp);
	fr(j,1,min(a[0],k*1LL)) ans+=a[j];
	cout<<ans<<endl;
	return 0;
}
