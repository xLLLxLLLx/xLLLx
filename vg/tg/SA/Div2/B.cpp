#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=2e4+10;
int h[N],sa[N],rk[N],id[N],a[N],all[N],st[N][20],nm[N];
int n,k;

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
	/*fr(i,1,n) printf("%d ",h[i]);
	puts("");*/
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int Get(int l,int r){
	//printf("%d %d\n",l,r);
	if(r>n) return 0;
	int t=log(double(r-l+1))/log(2.0);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}

void rmq(){
	fr(i,1,n) st[i][0]=h[i];
	fr(j,1,19){
		fr(i,1,n){
				if(i+(1<<j)>n) break;
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		//		printf("%d %d %d\n",i,j,st[i][j]);
		}
	}
	int maxn=0;
	fr(i,2,n) maxn=max(maxn,Get(i,i+k-2));
	printf("%d\n",maxn);
}

int main(){
	scanf("%d%d",&n,&k);
	fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
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
	rmq();
	return 0;
}