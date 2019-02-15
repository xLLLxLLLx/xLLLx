#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define Fr(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const int N=310,M=1e6;
int n,k;
db A[M+10],y[N];

int main(){
	scanf("%d%d",&n,&k);
	int m=M/k;
	fr(i,1,n){
		db y1,y2,ans=0;
		scanf("%lf",&y1);
		Fr(j,0,k){
			scanf("%lf",&y2);
			Fr(t,0,m){
				double pos=double(m-t)/double(m);
				db tmp=y2+(y1-y2)*pos;
			//	printf("%d %d %lf\n",j,t,tmp);
				if(tmp>A[j*m+t]){
					ans+=tmp-A[j*m+t];
					A[j*m+t]=tmp;
				}
			}
			y1=y2;
		}
		ans/=m;
		printf("%.12f\n",ans);
	}
	return 0;
}
