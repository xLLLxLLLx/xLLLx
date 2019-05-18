#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
vector<int>d[N];
int n,m;
ll nm[N],q[N],sum=0;

bool check(ll x){
	memset(q,0,sizeof q);
	fr(i,1,n){
		int len=d[i].size();
		rf(j,len-1,0){
			if(d[i][j]<=x){
				q[d[i][j]]+=nm[i];
				break;
			}
		}
	}
	ll res=0,cnt=0;
	fr(i,1,x){
		cnt++;
		ll pos=min(q[i],cnt);
		res+=pos;
		cnt-=pos;
	}
	ll tmp=sum*2ll-res;
	return tmp<=x;
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%lld",&nm[i]),sum+=nm[i];
	fr(i,1,m) {
		int x,y;scanf("%d%d",&x,&y);
		d[y].push_back(x);
	}
	fr(i,1,n) {
		if(d[i].size()) {
			sort(d[i].begin(),d[i].end());
		}
	}
	ll l=sum,r=sum*2,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}