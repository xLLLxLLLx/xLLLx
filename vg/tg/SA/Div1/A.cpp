#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010,M=26;
char lx[N];
int n;
int a[N],id[N],sa[N],mk[M+1],rk[N],nm[N],h[N],qz[N];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(M,n)) nm[i]+=nm[i-1];
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
//	fr(i,2,n) printf("%d ",h[i]);
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	scanf("%s",lx+1);
	n=strlen(lx+1);
	fr(i,1,M) scanf("%1d",&mk[i]),mk[i]=1-mk[i];
	int k;scanf("%d",&k);
	fr(i,1,n) a[i]=lx[i]-'a'+1,qz[i]=qz[i-1]+mk[a[i]];
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
	LL ans=0;
	fr(i,1,n){
	//	printf("%d\n",i);
		int l=sa[i],r=n,pos=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(qz[mid]-qz[sa[i]-1]<=k) pos=mid,l=mid+1;
			else r=mid-1;
		}
		if(pos==-1) continue;
		int len=pos-sa[i]+1;
		ans+=max(0,len-h[i]);
	}
	printf("%lld\n",ans);
	return 0;
}