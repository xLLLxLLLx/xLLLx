#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
double L[N],R[N],qz[N];
int n,q;

int Get(double x){
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(L[mid]<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

int main(){
	double s,a,b;
	scanf("%lf%lf%lf",&s,&a,&b);
	scanf("%d",&n);
	fr(i,1,n) scanf("%lf%lf",&L[i],&R[i]);
	fr(i,1,n) qz[i]=qz[i-1]+R[i]-L[i];
	scanf("%d",&q);
	fr(o,1,q){
		double x,y;scanf("%lf%lf",&x,&y);
		double t1=(a*y-s*x)/(y-s);
		double t2=(b*y-s*x)/(y-s);
	//	printf("%lf %lf\n",t1,t2);
		if(t2<=L[1]||t1>=R[n]){
			printf("0\n");
			continue;
		}
		int l=Get(t1),r=Get(t2);
		double ans=0;
		ans+=min(t2,R[r])-L[r]+qz[r-1];
		ans-=min(t1,R[l])-L[l]+qz[l-1];
	//	printf("ans=%lf\n",ans);
		printf("%.10f\n",ans*(y-s)/y);
	}
	return 0;
}