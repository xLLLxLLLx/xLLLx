#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e4+10;
char lx[N];
int n;
int a[N],id[N],rk[N],sa[N],h[N],nm[N];

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,n) nm[i]+=nm[i-1];
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
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		scanf("%s",lx+1);
		n=strlen(lx+1);
		memset(a,0,sizeof a);
		fr(i,1,n) a[i]=lx[i]-'A'+1;
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
	//	fr(i,1,n) printf("%d ",rk[i]);
		Geth();
		LL ans=0;
		fr(i,1,n) ans+=(n-sa[i]+1-h[i])*1LL;
		printf("%lld\n",ans);
	}
	return 0;
}