#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10,mod=998244353;
char lx[N];

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	ll ans=0;
	fr(i,1,26){
		int l=n+1,r=-1;
		fr(j,1,n){
			int pos=lx[j]-'a'+1;
			if(pos!=i) l=min(l,j),r=max(r,j);
		}
		if(l==n+1){
			printf("%lld\n",n*1ll*(n+1)/2%mod);
			return 0;
		}
		ans+=l*1ll*(n-r+1);
		ans--;
	}
	ans++;
	printf("%lld\n",ans%mod);
	return 0;
}