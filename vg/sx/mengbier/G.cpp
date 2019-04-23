#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10,LOG=19;
int nm[N],mk[N],mu[N],yz[N],f[N][LOG+1];

void init(){
	mu[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) yz[++yz[0]]=i,mu[i]=-1,nm[i]=1;
		fr(j,1,yz[0]){
			if(i*yz[j]>=N) break;
			mk[i*yz[j]]=1,nm[i*yz[j]]=nm[i]+1;
			if(i%yz[j]) mu[i*yz[j]]=-mu[i];
			 else { mu[i*yz[j]]=0;break; }
		}
	}
	fr(i,1,N-1) for(int j=i;j<N;j+=i) f[j][nm[i]]+=mu[j/i];
	fr(i,1,N-1) fr(j,1,LOG) f[i][j]+=f[i][j-1];
	fr(i,1,N-1) fr(j,0,LOG) f[i][j]+=f[i-1][j];
}

int main(){
	init();
	int T;scanf("%d",&T);
	fr(o,1,T){
		int n,m,p;scanf("%d%d%d",&n,&m,&p);
		if(p>=19) printf("%lld\n",n*1ll*m);
		else {
			if(n>m) swap(n,m);
			ll ans=0;
			for(int i=1,sz;i<=n;i=sz+1){
				sz=min(n/(n/i),m/(m/i));
				ans+=(f[sz][p]-f[i-1][p])*1ll*(n/i)*1ll*(m/i);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}