#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=1e3+10;
int qz[N];
char lx[N],ll[N];

int main(){
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	scanf("%s%s",lx+1,ll+1);
	fr(i,1,n-m+1){
		int flg=1;
		fr(j,1,m) if(lx[i+j-1]!=ll[j]) {flg=0;break;}
		if(flg) qz[i]++;
	}
	fr(i,1,n-m+1) qz[i]+=qz[i-1];
	fr(i,1,q){
		int l,r;scanf("%d%d",&l,&r);
		if(r-l+1<m) printf("0\n");
		else printf("%d\n",qz[r-m+1]-qz[l-1]);
	}
	return 0;
}