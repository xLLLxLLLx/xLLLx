#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
int pr[N],mk[N],mu[N],sum[N];

void init(){
	mu[1]=sum[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) pr[++pr[0]]=i,mu[i]=-1;
		fr(j,1,pr[0]){
			if(i*pr[j]>=N) break;
			mk[i*pr[j]]=1;
			if(i%pr[j]) mu[i*pr[j]]=-mu[i];
			 else {mu[i*pr[j]]=0;break;}
		}
		sum[i]=sum[i-1]+mu[i];
	}
}

ll cal(int a,int b,int c){
	int x=min(a,min(b,c));
	ll ans=0;
	for(int i=1,sz;i<=x;i=sz+1){
		sz=min(a/(a/i),min(b/(b/i),c/(c/i)));
		ans+=(sum[sz]-sum[i-1])*1ll*(a/i)*1ll*(b/i)*1ll*(c/i);
	}
	return ans;
}

ll cal(int a,int b){
	if(a>b) swap(a,b);
	ll ans=0;
	for(int i=1,sz;i<=a;i=sz+1){
		sz=min(a/(a/i),b/(b/i));
		ans+=(sum[sz]-sum[i-1])*1ll*(a/i)*1ll*(b/i);
	}
	return ans;
}

int main(){
	init();
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c)==3){
		ll ans=3;
		a--,b--,c--;
		ans+=cal(a,b,c);
		ans+=cal(a,b)+cal(b,c)+cal(a,c);
		printf("%lld\n",ans);
	}
	return 0;
}