#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
int yz[N],mu[N],mk[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void init(){
	mu[1]=1;
	fr(i,2,N-1){
		if(!mk[i]) mu[i]=-1,yz[++yz[0]]=i;
		fr(j,1,yz[0]){
			if(i*yz[j]>=N) break;
			mk[i*yz[j]]=1;
			if(i%yz[j]) mu[i*yz[j]]=-mu[i];
			else {
				mu[i*yz[j]]=0;
				break;
			}
		}
	}
}

int main(){
	init();
	int T;read(T);
	fr(o,1,T){
		int n;read(n);
		ll ans=3;
		fr(i,1,n) ans+=mu[i]*1ll*(n/i)*1ll*(n/i)*1ll*(n/i+3)*1ll;
		printf("%lld\n",ans);
	}
}