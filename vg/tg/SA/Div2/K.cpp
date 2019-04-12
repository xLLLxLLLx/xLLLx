#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e5+10;
char lx[N];
int n;
int q[N],L[N],R[N],a[N],id[N],sa[N],rk[N],h[N],nm[N];

LL mul(LL x,LL y){ return x*y; }

LL pf(LL x){ /*printf("ccc%lld\n",x);*/return (x+1)*x; }

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
	/*printf("%d\n",n);
	fr(i,1,n) printf("%d ",h[i]);
	puts("");*/
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	scanf("%s",lx+1);
	n=strlen(lx+1);
	fr(i,1,n) a[i]=lx[i]-'a'+1;
	fr(i,1,n) id[i]=i,rk[i]=a[i];
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
	LL ans=0,pos=0;
	fr(i,1,n) ans+=mul(i,n-1);
	int tp=0;q[tp]=1;
	fr(i,2,n){
		while(tp&&h[q[tp]]>=h[i]) tp--;
		L[i]=q[tp]+1;
		q[++tp]=i;
	}
	tp=0;q[tp]=n+1;
	rf(i,n,2){
		while(tp&&h[q[tp]]>h[i]) tp--;
		R[i]=q[tp]-1;
		q[++tp]=i;
	}
	fr(i,2,n) ans-=mul(mul(2,mul(i-L[i]+1,R[i]-i+1)),h[i]);
	printf("%lld\n",ans);
	return 0;
}