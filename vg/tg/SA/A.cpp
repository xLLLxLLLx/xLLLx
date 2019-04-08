#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=2e4+10;
int h[N],sa[N],rk[N],id[N],a[N],all[N],nm[N],n;

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,n) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int height=0;
	fr(i,1,n){
		if(height) height--;
		int j=sa[rk[i]-1];
		while(a[i+height]==a[j+height]) height++;
		h[rk[i]]=height;
	}
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

bool check(int x){
	int l=n,r=0,k=0;
	fr(i,2,n){
		if(h[i]<x) {
			k=max(k,r-l);
			l=n,r=0;
		} else {
			l=min(sa[i],l),r=max(sa[i],r);
			l=min(sa[i-1],l),r=max(sa[i-1],r);
		}
	}
	if(r) {
		if(r==l) 
		k=max(k,r-l);
	}
	return k>=x;
}

int main(){
	while(scanf("%d",&n)==1&&n){
		fr(i,1,n) scanf("%d",&all[i]);
		fr(i,2,n) a[i-1]=all[i]-all[i-1];
		n--;
		fr(i,1,n) all[i]=a[i];
		sort(all+1,all+1+n);
		int m=unique(all+1,all+1+n)-all-1;
		fr(i,1,n) a[i]=lower_bound(all+1,all+1+m,a[i])-all;
		fr(i,1,n) id[i]=i,rk[i]=a[i];
		Sort();
		for(int j=1,p=0;p<n;j<<=1){
			p=0;
			fr(i,n-j+1,n) id[++p]=i;
			fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
			Sort(),swap(rk,id);
			p=0;
			fr(i,1,n) rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
		}
		Geth();
		int l=0,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		ans++;
		//printf("ans=%d\n", ans);
		if(ans>=5) printf("%d\n",ans);
		else printf("0\n");
	}
	return 0;
}