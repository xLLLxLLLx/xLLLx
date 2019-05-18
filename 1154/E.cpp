#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define ls x<<1
#define rs x<<1|1
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int a[N],d[N],bf[N],nt[N];
int v[N<<2],id[N<<2];

void up(int x){
	v[x]=max(v[ls],v[rs]);
	if(v[ls]>v[rs]) id[x]=id[ls];
	else id[x]=id[rs];
}

void insert(int x,int l,int r,int w,int L,int k){
	if(l==r){
		if(k) v[x]=w,id[x]=l;
		else v[x]=id[x]=0;
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) insert(ls,l,mid,w,L,k);
	else insert(rs,mid+1,r,w,L,k);
	up(x);
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) scanf("%d",&a[i]),insert(1,1,n,a[i],i,1);
	nt[0]=1;
	fr(i,1,n) bf[i]=i-1,nt[i]=i+1;
	//nt[n]=0;
	for(;;){
		int flg=0;
		fr(o,1,2){
			int s=id[1];
			d[s]=o;
			for(int i=bf[s],j=1;i&&j<=k;i=bf[i],++j){
				insert(1,1,n,a[i],i,0);
				d[i]=o;
				bf[nt[i]]=bf[i],nt[bf[i]]=nt[i];
			}
			for(int i=nt[s],j=1;i!=n+1&&j<=k;i=nt[i],++j){
				insert(1,1,n,a[i],i,0);
				d[i]=o;
				bf[nt[i]]=bf[i],nt[bf[i]]=nt[i];
			}
			insert(1,1,n,a[s],s,0);
			bf[nt[s]]=bf[s],nt[bf[s]]=nt[s];
			if(nt[0]==n+1) break;
		}
		if(nt[0]==n+1) break;
	}
	fr(i,1,n) printf("%d",d[i]);
	return 0;
}