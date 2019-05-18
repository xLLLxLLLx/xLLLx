#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
ll a[N];
int mk[N];

int main(){
	int T;cin>>T;
	fr(o,1,T){
		int n;scanf("%d",&n);
		fr(i,1,n) scanf("%lld",&a[i]),mk[a[i]]=1;
		sort(a+1,a+1+n);
		ll pos=a[1]*a[n];
		int flg=0;
		fr(i,1,n){
			int r=n-i+1;
			if(a[i]*a[r]!=pos) flg=1;
		}
		if(!flg){
			int len=sqrt(pos);
			fr(i,2,len){
				if(pos%i) continue;
				if(!mk[i]||!mk[pos/i]) {flg=1;break;}
			}
		}
		fr(i,1,n) mk[a[i]]=0;
		if(flg) printf("-1\n");
		else printf("%lld\n",pos);
	}
	return 0;
}