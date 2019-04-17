#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10,M=2010;
int w[N],f[M],b[M],qz[M];

int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	fr(i,1,n) scanf("%d",&w[i]);
	sort(w+1,w+1+n);
	fr(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		if(x<=k) b[x]=max(b[x],y);
	}
	fr(i,1,k) qz[i]=qz[i-1]+w[i],f[i]=qz[i];
	fr(i,1,k) fr(j,1,i) f[i]=min(f[i],f[i-j]+qz[i]-qz[i-j+b[j]]);
	//fr(i,1,k) printf("f[%d]=%d\n",i,f[i]);
	printf("%d\n",f[k]);
	return 0;
}