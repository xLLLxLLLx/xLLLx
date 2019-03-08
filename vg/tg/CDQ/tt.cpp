#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int id;
	int x,y,z;
}a[N],c[N];
int tr[N],d[N],g[N];

int lowerbit(int x){ return x&(-x); }

void UPD(int x,int y){
	for(;x<N;x+=lowerbit(x)) tr[x]+=y;
}

void Qk(int x){
	for(;x<N;x+=lowerbit(x)) tr[x]=0;
}

int Get(int x){
	int ans=0;
	for(;x;x-=lowerbit(x)) ans+=tr[x];
	return ans;
}

bool cmp(data xx,data yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	if(xx.y!=yy.y) return xx.y<yy.y;
	if(xx.z!=yy.z) return xx.z<yy.z;
}

bool check(data xx,data yy){
	return xx.y<=yy.y;
}

void CDQ(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	int lt=l-1,nw=l;
	fr(i,mid+1,r){
		int flg=0;
		fr(j,lt+1,mid){
			if(!check(a[j],a[i])){
				flg=1;
				lt=j-1;
				break;
			} else {
				UPD(a[j].z,1);
				c[nw++]=a[j];
			}
		}
		if(!flg) lt=mid;
		d[a[i].id]+=Get(a[i].z);
		c[nw++]=a[i];
	}
	fr(i,lt+1,mid) c[nw++]=a[i];
	fr(i,l,lt) Qk(a[i].z);
	fr(i,l,r) {
		a[i]=c[i];
	}
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		memset(d,0,sizeof d);
		int n;scanf("%d",&n);
		fr(i,1,n) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),a[i].id=i;
		sort(a+1,a+1+n,cmp);
		CDQ(1,n);
		int lt=1;
		rf(i,n-1,1){
			if(a[i].x!=a[i+1].x||a[i].y!=a[i+1].y||a[i].z!=a[i+1].z){
				lt=1;
			} else lt++;
			d[a[i].id]+=lt-1;
		}
		fr(i,1,n) printf("%d\n",d[i]);
	}
	return 0;
}
