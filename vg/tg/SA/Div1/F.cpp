#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
char lx[N];
int n;
int a[N],q[N],qz[N],h[N],mk[N],id[N],rk[N],sa[N],nm[N];

void Sort(){
	memset(nm,0,sizeof nm);
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
	// fr(i,1,n) printf("%d ",h[i]);
	// puts("");
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	scanf("%d",&n);
	scanf("%s",lx+1);
	fr(i,1,n) scanf("%1d",&mk[i]);
	reverse(mk+1,mk+1+n);
//	fr(i,1,n) printf("%d ",mk[i]);
//	puts("");
	fr(i,1,n) a[i]=lx[n-i+1]-'a'+1;
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
	fr(i,1,n)
		if (mk[sa[i]]) qz[i]=qz[i-1]+1;
		 else qz[i]=qz[i-1];
	LL maxn=0;int tp=0;
	fr(i,1,n) if(!mk[i]) {maxn=n-i+1;break;}
	h[++n]=-1,q[0]=1;
	fr(i,2,n){
		int f=1;
		while(tp&&h[q[tp]]>=h[i]){
			if(h[q[tp]]==h[i]) {f=0,q[tp]=i;break;}
			//printf("%d %d\n",h[q[tp]],i-q[tp-1]-(qz[i-1]-qz[q[tp-1]-1]));
			maxn=max(maxn,h[q[tp]]*1LL*(i-q[tp-1]-(qz[i-1]-qz[q[tp-1]-1])));
			tp--;
		}
		if(f) q[++tp]=i;
	}
	printf("%lld\n",maxn);
	return 0;
}