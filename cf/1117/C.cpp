#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define Fr(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
char lx[N];
int nx[N],ny[N];
int n,bx,by,ex,ey;

bool check(LL x){
	LL pos=abs(nx[n]*(x/n)+nx[x%n]+bx-ex)+abs(ny[n]*(x/n)+ny[x%n]+by-ey);
	return pos<=x;
}

int main(){
	cin>>bx>>by>>ex>>ey;
	cin>>n;
	scanf("%s",lx+1);
	fr(i,1,n){
		ny[i]=ny[i-1],nx[i]=nx[i-1];
		if(lx[i]=='U') ny[i]++;
		if(lx[i]=='D') ny[i]--;
		if(lx[i]=='L') nx[i]--;
		if(lx[i]=='R') nx[i]++;
	}
	LL l=0,r=1e18,ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}
