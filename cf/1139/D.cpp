#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
LL dp[N],ny[N];
vector<int> v[N],yz[N];
int m,nm[N],flg[N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL q_pow(LL x,int y){
	LL ans=1;
	for(;y;y>>=1){
		if(y&1) Mul(ans,x);
		Mul(x,x);
	}
	return ans;
}

void init(){
	fr(i,2,m){
		if(flg[i]) continue;
		for(int j=i;j<=m;j+=i)
			flg[j]=1,v[j].push_back(i);
	}
	fr(i,1,m) for(int j=i*2;j<=m;j+=i)
		yz[j].push_back(i);
}

LL js(int x){
	LL pos=x*x;
	fr(i,2,x){
		int len=v[i].size(),mk=(1<<len);
		fr(j,1,mk){
			int res=0,tmp=1;
			fr(k,0,len-1)
				if((j>>k)&1) res++,tmp*=v[i][k];
			if(res&1) pos-=x/tmp;
			else pos+=x/tmp;
		}
	}
	return pos;
}

int main(){
	cin>>m;
	LL t=q_pow(m,mod-2);
	fr(i,1,m) ny[i]=q_pow(i,mod-2);
	fr(i,1,m) nm[i]=m;
	init();
	dp[1]=1;
	fr(i,2,m){
		int len=yz[i].size();
		LL gg=mul(i,ny[i-1]);
		Add(dp[i],gg);
		fr(j,0,len-1){
			Add(dp[i],mul(gg,mul(dp[yz[i][j]],mul(t,js(m/yz[i][j])))));
		}
	}
	LL ans=0;
	fr(i,1,m) Add(ans,mul(dp[i],t));
	cout<<ans<<endl;
	return 0;
}