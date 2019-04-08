#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10,LOG=20,inf=1e9;
char lx[N];
int n;
int a[N],rk[N],id[N],h[N],sa[N],nm[N],v[N];

void Sort(){
	fr(i,1,max(n,26)) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,26)) nm[i]+=nm[i-1];
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
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

void rmq(){
	int zz=rk[1];
	v[zz]=inf;
	fr(i,zz+1,n) v[i]=min(v[i-1],h[i]);
	rf(i,zz-1,1) v[i]=min(v[i+1],h[i+1]);
}

bool check(int x){
	fr(i,1,n/x-1){
		int be=i*x+1;
		if(v[rk[be]]<x) return false;
	}
	//puts("");
	return true;
}

int main(){
	for(;;){
		scanf("%s",lx+1);
		if(lx[1]=='.') break;
		n=strlen(lx+1);
		fr(i,1,n) a[i]=lx[i]-'a'+1;
		fr(i,1,n) rk[i]=a[i],id[i]=i;
		Sort();
		for(int j=1,p=0;p<n;j<<=1){
			p=0;
			fr(i,n-j+1,n) id[++p]=i;
			fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
			Sort(),swap(id,rk);
			p=0;
			fr(i,1,n) rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
		}
		Geth(),rmq();
		int len=sqrt(n),maxn=0;
		fr(i,1,len){
			if(n%i) continue;
			if(check(i)) maxn=max(maxn,n/i);
			if(check(n/i)) maxn=max(maxn,i);
		}
		printf("%d\n",maxn);
		//fr(i,1,n) a[i]=0;
	}
	return 0;
}