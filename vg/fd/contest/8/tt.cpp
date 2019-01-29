#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
int a[N],f[N],b[N],d[N];

int find(int k){
	return f[k]==k?k:f[k]=find(f[k]);
}

void add(int x,int y){
	int fx=find(x),fy=find(y);
	f[fx]=fy;
}

int main(){
	while(1){
		int n;scanf("%d",&n);
		if(!n) break;
		printf("NOWW!!!%d\n",n);
		fr(i,1,n/2) a[i]=i,a[n-i+1]=i;
		a[n/2+1]=n/2+1;
		int flg=0;
		fr(i,1,n) {
			int cnt=0;
			fr(j,1,n/2+1) f[j]=j;
			fr(j,i,n) b[++cnt]=a[j];
			fr(j,1,i-1) b[++cnt]=a[j];
			fr(j,1,n/2) add(b[j],b[n-j+1]);
			int ans=0;
			fr(j,1,n/2+1) if(f[j]==j) ans++;
			flg=0;
			if(ans!=1) flg=1,printf("%d %d\n",i,ans);
		}
	}
	return 0;
}
