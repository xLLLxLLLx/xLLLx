#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
struct data{
	int x,y;
}a[5];
int mu[N],sum[N],mk[N],yz[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void init(){
	mu[1]=sum[1]=1;
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
		sum[i]=sum[i-1]+mu[i];
	}
}

ll cal(int x,int y){
	if(x>y) swap(x,y);
	ll ans=0;
	for(int i=1,sz=1;i<=x;i=sz+1){
		sz=min(x/(x/i),y/(y/i));
		ans+=(sum[sz]-sum[i-1])*1ll*(x/i)*1ll*(y/i);
	}
	return ans;
}

bool cmp(data A,data B){
	return A.x<B.x;
}

int main(){
	int T;read(T);
	init();
	fr(o,1,T){
		fr(i,0,1) scanf("%d%d",&a[i].x,&a[i].y);
		sort(a,a+2,cmp);
		ll ans=0;
		fr(i,0,1) a[i].x--;
		int k;scanf("%d",&k);
		if(k){
			fr(i,0,1) a[i].x/=k,a[i].y/=k;
			ans=cal(a[0].y,a[1].y)-cal(a[0].x,a[1].y)-cal(a[0].y,a[1].x)+cal(a[0].x,a[1].x);
			//printf("%lld\n",ans);
			if(a[0].y>=a[1].x) {
				int l=a[1].x,r=min(a[0].y,a[1].y);
				ll pos=(cal(r,r)-cal(l,r)*2ll+cal(l,l))/2ll;
				ans-=pos;
			}
		}
		printf("Case %d: %lld\n",o,ans);
	}
	return 0;
}