#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1e6+10;
char lx[N];
int n,k;
int a[N],id[N],sa[N],nm[N],rk[N],h[N];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,27)) nm[i]+=nm[i-1]; 
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) H--;
		int j=sa[rk[i]-1];
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
	/*fr(i,1,n) printf("%d ",sa[i]);
	puts("");
	fr(i,2,n) printf("H%d ",h[i]);
	puts("");*/
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

bool check(int x){
	int flg1=0,flg2=0;
	fr(i,2,n){
		if(h[i]<x){
			if(flg1&&flg2) return true;
			flg1=0,flg2=0;
		} else {
			if(sa[i]>=k||sa[i-1]>=k) flg2=1;
			if(sa[i]<=k-2||sa[i-1]<=k-2) flg1=1;
		}
	}
	return flg1&&flg2;
}

int main(){
	scanf("%s",lx+1);
	int len=strlen(lx+1);
	fr(i,1,len) a[i]=lx[i]-'a'+1;
	a[len+1]=27;
	scanf("%s",lx+1);
	k=len+2;
	len=strlen(lx+1);
	fr(i,1,len) a[k+i-1]=lx[i]-'a'+1;
	n=k+len-1;
	fr(i,1,n) id[i]=i,rk[i]=a[i];//,printf("%d ",a[i]);
	//puts("");
	Sort();
	for(int j=1,p=0;p<n;j<<=1){
		p=0;
		fr(i,n-j+1,n) id[++p]=i;
		fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
		Sort(),swap(id,rk);
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
	printf("%d\n",ans);
	return 0;
}