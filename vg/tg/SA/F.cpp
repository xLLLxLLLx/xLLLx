#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int tot,k,n;
char lx[N];
LL c[N],d[N];
int q[N],a[N],h[N],st[tp],mk[N],id[N],rk[N],sa[N],nm[N],len[N];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,N-1) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) --H;		int j=sa[rk[i]-1];
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	scanf("%d%d",&tot,&k);
	n=0;
	fr(i,1,k){
		scanf("%s",lx+1);
		len[i]=strlen(lx+1);
		fr(j,1,len[i]) a[n+j]=lx[i]-'a'+1,mk[n+j]=i;
		n+=len[i]+1;
		a[n]=i+26;
	}
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
	fr(i,1,n){
		
	}
	fr(i,1,n) c[i]+=c[i-1],d[mk[i]]++;
	fr(i,1,k) printf("%lld ",d[i]);
	return 0;
}