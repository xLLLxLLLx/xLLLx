#include<iostream>
#include<cstdio>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+120,M=1010;
int k,n,bz;
int mk[110],len[N],a[N],id[N],rk[N],sa[N],h[N],nm[N];

void Sort(){
	fr(i,1,max(n,200)) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,200)) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) H--;
		int j=sa[rk[i]-1];
		while(a[j+H]==a[i+H]) H++;
		h[rk[i]]=H;
	}
//	fr(i,2,n) printf("%d ",h[i]);
//	puts("");
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

bool check(int x){
	fr(i,0,k-1) mk[i]=0;
	fr(i,2,n){
		if(h[i]<x) {
			int res=0;
			fr(j,0,k-1) res+=mk[j],mk[j]=0;
			if(res>bz) return true;
		} else {
			int sum=0;
			fr(j,0,k-1){
				int l=sum+1,r=sum+len[j];
				if(sa[i]>=l&&sa[i]<=r) mk[j]=1;
				if(sa[i-1]>=l&&sa[i-1]<=r) mk[j]=1;
				sum+=len[j]+1;
			}
		}
	}
	int res=0;
	fr(i,0,k-1) res+=mk[i];
	return res>bz;
}

char lx[N];

int main(){
	int FF=0;
	while(scanf("%d",&k)==1&&k){
		if(FF) puts("");
		FF=1;
		n=0,bz=k/2;
		int maxn=0;
		fr(i,0,k-1){
			scanf("%s",lx+1);
			len[i]=strlen(lx+1);
			maxn=max(maxn,len[i]);
			fr(j,1,len[i]) a[n+j]=lx[j]-'a'+1;
			n+=len[i]+1;a[n]=i+27;
		}
		//fr(i,1,n) printf("%d ",a[i]);
		//puts("");
		//a[1]=1,a[2]=1,a[3]=2,a[4]=1,a[5]=1,a[6]=1,a[7]=1,a[8]=2;
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
		int l=0,r=maxn,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		if(!ans) printf("?\n");
		else {
			//printf("%d\n",ans);
			int gg=0;
			fr(i,0,k-1) mk[i]=0;
			fr(i,1,n){
				if(h[i]<ans) {
					int res=0;
					fr(j,0,k-1) res+=mk[j],mk[j]=0;
					if(res>bz){
						fr(j,gg,gg+ans-1) printf("%c",a[j]+'a'-1);
						puts("");
					}
				} else {
					int sum=0;
					fr(j,0,k-1){
						int l=sum+1,r=sum+len[j];
						if(sa[i]>=l&&sa[i]<=r) mk[j]=1,gg=sa[i];
						if(sa[i-1]>=l&&sa[i-1]<=r) mk[j]=1,gg=sa[i-1];
						sum+=len[j]+1;
					}
				}
			}
		}
	}
	return 0;
}