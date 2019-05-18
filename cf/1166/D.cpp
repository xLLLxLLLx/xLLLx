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
const int N=55;
ll d[N],pw[N]={1},c[N];

long double mul(long double x,long double y){
	return x*y;
}

int main(){
	int T;scanf("%d",&T);
	fr(i,1,50) pw[i]=pw[i-1]*2;
	fr(o,1,T){
		ll a,b,m;scanf("%lld%lld%lld",&a,&b,&m);
		if(a==b){
			printf("1 %lld\n",a);
		} else {
			int flg=0;
			fr(i,2,50){
				long double pos=mul(pw[i-2],a);
				long double mm=1,mx=m;
				mm+=pos,mx+=pos;
				fr(j,1,i-2) {
					mm=mm+mul(pw[i-2-j],1);
					mx=mx+mul(pw[i-2-j],m);
				}
				//cout<<mm<<" "<<mx<<endl;
				if(mm>b) break;
				else if(mm<=b&&b<=mx) {
					ll gg=pw[i-2]*a;
					ll mn=1+gg;
					fr(j,1,i-2){
						mn+=pw[i-2-j];
					}
					ll yu=b-mn,now=0;
					d[1]=a,d[i]=b;
					fr(j,2,i-1){
						c[j]=min(yu/pw[i-1-j],m-1)+1;
						yu-=(c[j]-1)*pw[i-1-j];
					}
					fr(j,2,i-1){
						d[j]=pw[j-2]*a+(now+c[j]);
						now=(now*2ll+c[j]);
					}
					printf("%d ",i);
					fr(j,1,i) printf("%lld ",d[j]);
					puts("");
					flg=1;
					break;
				}
			}
			if(!flg) printf("-1\n");
		}
	}
	return 0;
}