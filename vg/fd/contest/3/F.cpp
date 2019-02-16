#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
#define LL long long
using namespace std;
const int N=55;
struct data{
	LL a,b;
}qx[N];
LL f[N][N];
int n;

bool cmp(data xx,data yy){
	if(xx.a!=yy.a) return xx.a>yy.a;
	else return xx.b<yy.b;
}

LL Min(LL &x,LL y){
	x=min(x,y);
}

bool check(LL x){
	int lt=1;
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	fr(i,1,n){
		lt=i;
		while(lt+1<=n&&qx[i].a==qx[lt+1].a) lt++;
		fr(k,0,i-1) fr(t,0,min(lt-i+1,k)){
			fr(j,i,i+t-1) Min(f[j][k-(j-i+1)],f[i-1][k]);
			LL sum=0;
			fr(j,i+t,lt){
				sum+=qx[j].a-x*qx[j].b;
				int pos=k-t+(j-(i+t)+1);
//				if(j==5&&pos==1) cout<<"sum="<<sum<<endl;
				Min(f[j][pos],f[i-1][k]+sum);
			}
		}
		i=lt;
	}
//	fr(i,1,n) fr(j,0,i) printf("f[%d][%d]=%lf\n",i,j,f[i][j]);
	fr(i,0,n) if(f[n][i]<=0) return 1;
	return 0;
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&qx[i].a),qx[i].a*=1000;
	fr(i,1,n) scanf("%lld",&qx[i].b),qx[i].b;
	sort(qx+1,qx+1+n,cmp);
//	fr(i,1,n) cout<<qx[i].a<<" "<<qx[i].b<<endl;
	LL l=0,r=1e13,ans=-1;
	while(l<=r){
		db mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}
