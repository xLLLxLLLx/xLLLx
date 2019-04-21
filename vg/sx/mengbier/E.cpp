#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2010,mod=1073741824;
int pr[N],mk[N],mu[N],g[N][N];

void init(){
	mu[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) mu[i]=-1,pr[++pr[0]]=i;
		fr(j,1,pr[0]){
			if(i*pr[j]>=N) break;
			mk[i*pr[j]]=1;
			if(i%pr[j]) mu[i*pr[j]]=-mu[i];
			 else {mu[i*pr[j]]=0;break;}
		}
	}
}

int gcd(int a,int b){
	if(!b) return a;
	if(g[a][b]) return g[a][b];
	return g[a][b]=g[b][a]=gcd(b,a%b);
}

ll work(int x,int d,int k){
	ll ans=0;
	fr(i,1,x){
		if(gcd(d*i,k)==1) ans+=x/i;
		ans%=mod;
	}
	return ans;
}

int main(){
	int a,b,c;
	init();
	scanf("%d%d%d",&a,&b,&c);
	ll ans=0;
	fr(i,1,a){
		ll tmp=0;
		fr(j,1,b){
			tmp+=mu[j]*work(b/j,j,i)*work(c/j,j,i)%mod;
			tmp%=mod;
		}
		ans=(ans+tmp*(a/i)%mod)%mod;
	}
	ans=(ans+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}