#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e7+10;
int mk[N],mu[N],sum[N],yz[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void init(){
	sum[1]=1,mu[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) yz[++yz[0]]=i,mu[i]=-1;
		for(int j=1;j<=yz[0];++j){
			if(i*yz[j]>=N) break;
			if(i%yz[j]) mu[i*yz[j]]=-mu[i],mk[i*yz[j]]=1;
			 else {
			 	mu[i*yz[j]]=0,mk[i*yz[j]]=1;
			 	break;
			 }
		}
		sum[i]=sum[i-1]+mu[i];
	}
}

ll cal(int x,int y){
	if(x>y) swap(x,y);
	ll ans=0;
	for(int i=1,sz=1;i<=x;i=sz+1){
		sz=min(x/(x/i),y/(y/i));
		ans+=(sum[sz]-sum[i-1])*1ll*((x/i)*1ll*(y/i))*1ll;
	}
	return ans;
}

int main(){
	init();
	int T;read(T);
	fr(o,1,T){
		int a,b;
		read(a),read(b);
		ll ans=0;
		fr(i,1,yz[0]){
			if(yz[i]>a||yz[i]>b) break;
			ans+=cal(a/yz[i],b/yz[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}