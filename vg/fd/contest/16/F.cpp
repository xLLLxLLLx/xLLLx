#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
struct data{
	LL x,y;
}a[N];
LL Lm[N],Ln[N],Rm[N],Rn[N];
int n;

bool cmp(data xx,data yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	else return xx.y<yy.y;
}

bool check(LL dis){
	int lt=1;
	fr(i,1,n){
		while(lt+1<=n&&a[lt+1].x<=dis+a[i].x) lt++;
		LL maxn=-2000000000,minn=2000000000;
		if(i!=1) maxn=Lm[i],minn=Ln[i];
		if(lt!=n) maxn=max(maxn,Rm[lt]),minn=min(minn,Rn[lt]);
		if(i==1&&lt==n) maxn=0,minn=0;
		if(maxn-minn<=dis) return true;
	}
	return false;
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) {
		LL x,y;
		scanf("%lld%lld",&x,&y);
		a[i].x=x-y,a[i].y=x+y;
	}
	sort(a+1,a+1+n,cmp);
	LL maxn=-2000000000,minn=2000000000;
	fr(i,1,n){
		Lm[i]=maxn,Ln[i]=minn;
		minn=min(a[i].y,minn);
		maxn=max(a[i].y,maxn);
	}
	maxn=-2000000000,minn=2000000000;
	rf(i,n,1){
		Rm[i]=maxn,Rn[i]=minn;
		minn=min(a[i].y,minn);
		maxn=max(a[i].y,maxn);
	}
	LL ans=-1,l=0,r=2000000000;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
//	printf("z%d\n",check(171568073));
	printf("%.12f\n",double(ans)/(2.0));
	return 0;
}
