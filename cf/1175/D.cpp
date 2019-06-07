#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10,LOG=20;
ll a[N],qz[N],st[N][LOG+1];
int id[N][LOG+1];

ll get(int l,int r){
	int k=(int)(log((double)(r-l+1))/log(2.0)); 
  return min(st[l][k],st[r-(1<<k)+1][k]);
}

int getid(int l,int r){
	 int k=(int)(log((double)(r-l+1))/log(2.0)); 
   if(st[l][k]>st[r-(1<<k)+1][k]) return id[r-(1<<k)+1][k];
   else return id[l][k];
}

int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	fr(i,1,n) {
		scanf("%lld",&a[i]);
		qz[i]=qz[i-1]+a[i];
	}
	fr(i,1,n) st[i][0]=qz[i],id[i][0]=i;
	fr(j,1,LOG) fr(i,1,n) {
		if(i+(1<<j)>n+1) continue;
		st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		if(st[i][j-1]<st[i+(1<<(j-1))][j-1]) id[i][j]=id[i][j-1];
		else id[i][j]=id[i+(1<<(j-1))][j-1];
	}
	ll ans=0;
	int l=1;
	fr(i,1,k-1) {
		ans+=1ll*i*(get(l,n-(k-i))-qz[l-1]);
		l=getid(l,n-(k-i))+1;
	}
	ans+=1ll*k*(qz[n]-qz[l-1]);
	printf("%lld\n",ans);
	return 0;
}