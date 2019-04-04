#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	LL x,y;
}a[N];
int q[N];

bool cmp(data xx,data yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	else return xx.y>yy.y;
}

int cross(int A,int B,int C){
	data pp=(data){a[B].x-a[C].x,a[B].y-a[C].y};
	data qq=(data){a[A].x-a[C].x,a[A].y-a[C].y};
	LL pos=qq.x*pp.y-qq.y*pp.x;
	if(pos<=0) return true;
	else return false;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		LL x,y;scanf("%lld%lld",&x,&y);
		a[i].x=x,a[i].y=y-x*x;
	}
	sort(a+1,a+1+n,cmp);
	//fr(i,1,n) printf("%lld %lld\n",a[i].x,a[i].y);
	int head=1,tail=1;q[tail]=1;
	fr(i,2,n){
		if(a[i].x==a[i-1].x) continue;
		while(head+1<=tail&&cross(q[tail],q[tail-1],i)) tail--;
		q[++tail]=i;
	}
	//fr(i,head,tail) printf("%d ",q[i]);
	printf("%d\n",tail-head);
	return 0;
}