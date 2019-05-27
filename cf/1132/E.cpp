#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=10,M=13450;
int f[M][N];
ll a[N];

int main(){
	int haha=840;
	ll m;
	scanf("%lld",&m);
	ll yu=0,sum=0;
	fr(i,1,8) {
		scanf("%lld",&a[i]);
		sum+=i*1ll*a[i];
		ll pos=a[i]/(haha/i);
		a[i]-=pos*(haha/i);
		if(pos) pos--,a[i]+=haha/i;
		yu+=pos*840;
	}
	if(sum<=m) return printf("%lld\n",sum),0;
	ll gg=m-yu;
	if(gg<0){
		ll tmp=gg/haha;
		tmp=-tmp;
		tmp++;
		gg+=tmp*haha;
	}
	f[0][0]=1;
	fr(i,0,gg) {
		fr(j,1,8) {
			if(!f[i][j-1]) continue;
			fr(k,0,a[j]) {
				if(i+k*j>gg) break;
				f[i+k*j][j]=1;
			}
		}
	}
	rf(i,gg,0) {
		if(f[i][8]) {
			printf("%lld\n",m-(gg-i));
			return 0;
		}
	}
	return 0;
}