#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=4010;
char lx[N];
int n,len,be=-1;
int a[N],all[N],sa[N],id[N],rk[N],st[N][20],nm[N],h[N];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,n) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
	/*printf("sa\n");
	fr(i,1,n) printf("%d ",sa[i]);
	puts("");*/
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) H--;
		int j=sa[rk[i]-1];
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
	/*fr(i,1,n) printf("H%d ",h[i]);
	puts("");*/
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int Get(int l,int r){
	if(l>r) swap(l,r);
	l++;
	//printf("%d %d\n", l,r);
	int t=log(double(r-l+1))/log(2.0);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}

void rmq(){
	fr(i,1,n) st[i][0]=h[i];
	fr(j,1,19){
		fr(i,1,n){
			if(i+(1<<j)>n) break;
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}

int main(){
	scanf("%s",lx+1);
	n=strlen(lx+1);
	len=n;
	fr(i,1,n) a[i]=lx[i]-'A'+1;
	a[n+1]=1000;
	fr(j,1,n) a[n+1+j]=a[n-j+1];
	n=n*2+1;
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
	Geth(),rmq();
	int ans=0,res=0;
	fr(i,1,len){
		int pos=Get(rk[i+1],rk[n-i+2]);
		if(pos*2+1>ans) ans=pos*2+1,res=i-pos;
		if(lx[i]==lx[i+1]) {
			pos=Get(rk[i+2],rk[n-i+2]);
			if(pos*2+2>ans) ans=pos*2+2,res=i-pos;
		}
	}
	fr(i,res,res+ans-1) printf("%c",lx[i]);
	return 0;
}