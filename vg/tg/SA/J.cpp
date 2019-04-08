#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+25,M=15;
char lx[N];
int L[M],R[M],a[N],nm[N],sa[N],id[N],rk[N],h[N];
int k,n,len[15];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,100)) nm[i]+=nm[i-1];
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

bool check(int x){
	int mk=0;
	fr(j,0,k-1) L[j]=n,R[j]=0;
	fr(i,2,n){
		if(h[i]<x){
			int flg=1;
			fr(j,0,k-1){
				if(R[j]-L[j]<x) {
					flg=0;break;
				}
			}
			if(flg&&mk==(1<<k)-1) return true;
			mk=0;
			fr(j,0,k-1) L[j]=n,R[j]=0;
		} else {
			int sum=0;
			fr(j,0,k-1) {
				int l=sum+1,r=sum+len[j];
				if(sa[i]>=l&&sa[i]<=r) mk|=(1<<j),L[j]=min(L[j],sa[i]),R[j]=max(R[j],sa[i]);
				if(sa[i-1]>=l&&sa[i-1]<=r) mk|=(1<<j),L[j]=min(L[j],sa[i-1]),R[j]=max(R[j],sa[i-1]);
				sum+=len[j]+1;
			}
		}
	}
	fr(j,0,k-1) if(R[j]-L[j]<x) return false;
	if(mk==(1<<k)-1) return true;
	return false; 
}

void init(){
	memset(id,0,sizeof id);
	memset(a,0,sizeof a);
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		scanf("%d",&k);
		n=0,init();
		fr(i,0,k-1){
			scanf("%s",lx+1);
			len[i]=strlen(lx+1);
			fr(j,1,len[i]) a[n+j]=lx[j]-'a'+1;
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
		Geth();
		int l=0,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}