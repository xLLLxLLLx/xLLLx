#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson (x<<1)
#define rson (x<<1|1)
using namespace std;
const int N=2e5+10;
struct data{
	int l,r,t,rk;
	bool operator < (const data &C) const {
		if(l!=C.l) return l<C.l;
		else return rk<C.rk;
	}
}a[N<<1];
int n,m;
int v[N<<2],id[N<<2],all[N<<1],c[N];

void change(int x,int l,int r,int R,int k,int zz){
	if(l==r&&l==R) {
		v[x]=k,id[x]=zz;
		return ;
	}
	int mid=(l+r)>>1;
	if(R<=mid) change(lson,l,mid,R,k,zz);
	else change(rson,mid+1,r,R,k,zz);
	v[x]=max(v[lson],v[rson]);
}

int find(int x,int l,int r,int R,int lmt){
//	printf("x=%d l=%d r=%d R=%d lmt=%d %d\n",x,l,r,R,lmt,id[x]);
	if(v[x]<lmt) return -1;
	if(l==r) return id[x];
	int mid=(l+r)>>1;
	if(R<=mid) {
		int ans=find(lson,l,mid,R,lmt);
		if(ans>0) return ans;
	}
	return find(rson,mid+1,r,R,lmt);
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,n+m){
		int x,y,z;
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].t);
		a[i].rk=i;
		all[i]=a[i].t;
	}
	sort(all+1,all+1+n+m);
	int tot=unique(all+1,all+1+n+m)-all-1;
	sort(a+1,a+1+n+m);
	fr(i,1,n+m){
		//printf("zz%d %d %d\n",a[i].l,a[i].r,a[i].rk);
		int pos=lower_bound(all+1,all+1+tot,a[i].t)-all;
		if(a[i].rk<=n) change(1,1,tot,pos,a[i].r,a[i].rk);
		else c[a[i].rk-n]=find(1,1,tot,pos,a[i].r);
	}
	fr(i,1,m) printf("%d ",c[i]);
	return 0;
}
