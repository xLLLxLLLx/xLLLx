#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e5+10;
char lx[N];
int n;
LL d[N];
int q[N],qz[N][2],all[N],len[2],L[N],R[N],a[N],id[N],sa[N],rk[N],h[N],nm[N];

void Sort(){
	fr(i,1,n) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,n) nm[i]+=nm[i-1];
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
	//fr(i,1,n) printf("%d ",h[i]);
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	int k;
	while(scanf("%d",&k)==1&&k){
		scanf("%s",lx+1);
		len[0]=strlen(lx+1);
		fr(i,1,len[0]) a[i]=lx[i]-'a'+1;
		n=len[0]+1;
		a[n]=27;
		scanf("%s",lx+1);
		len[1]=strlen(lx+1);
		fr(i,1,len[1]) a[n+i]=lx[i]-'a'+1;
		n+=len[1]+1;a[n]=28;
		fr(i,1,n) all[i]=a[i];
		sort(all+1,all+1+n);
		int tt=unique(all+1,all+1+n)-all-1;
		fr(i,1,n) a[i]=lower_bound(all+1,all+1+tt,a[i])-all;
		// fr(i,1,n) printf("%d ",a[i]);
		// puts("");
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
		int tp=0;LL tot=0;
		fr(i,2,n){
			if(h[i]<k) tp=tot=0;
			else {
				int cnt=0;
				if(sa[i-1]<=len[0]) cnt++,tot+=h[i]-k+1;
				while(tp&&h[i]<=q[tp-1]){
					tp--;
					tot-=d[tp]*(q[tp]-h[i]);
					cnt+=d[tp];
				}
				q[tp]=h[i],d[tp]=cnt;
				tp++;
				if(sa[i]>len[0]+1&&sa[i]<n) ans+=tot;
			}
		}
		tp=tot=0;
		fr(i,1,n){
			if(h[i]<k) tp=tot=0;
			else {
				int cnt=0;
				if(sa[i-1]>len[0]+1&&sa[i-1]<n) cnt++,tot+=h[i]-k+1;
				while(tp&&h[i]<=q[tp-1]){
					tp--;
					tot-=d[tp]*(q[tp]-h[i]);
					cnt+=d[tp];
				}
				q[tp]=h[i],d[tp]=cnt;
				tp++;
				if(sa[i]<=len[0]) ans+=tot;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}