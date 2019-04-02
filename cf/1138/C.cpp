#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
int c[N];
int sz[N][N],hz[N][N],s[N],h[N];
int a[N][N],b[N][N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) fr(j,1,m) scanf("%d",&a[i][j]);
	fr(i,1,n){
		fr(j,1,m) c[j]=a[i][j];
		sort(c+1,c+1+m);
		int w=unique(c+1,c+1+m)-c-1;
		fr(j,1,m) hz[i][j]=lower_bound(c+1,c+1+w,a[i][j])-c;
		h[i]=w;
	}
	fr(j,1,m){
		fr(i,1,n) c[i]=a[i][j];
		sort(c+1,c+1+n);
		int w=unique(c+1,c+1+n)-c-1;
		fr(i,1,n) sz[i][j]=lower_bound(c+1,c+1+w,a[i][j])-c;
		s[j]=w;
	}
	fr(i,1,n) fr(j,1,m){
		if(hz[i][j]-sz[i][j]>0) b[i][j]=max(h[i],hz[i][j]+s[j]-sz[i][j]);
		else b[i][j]=max(s[j],sz[i][j]+h[i]-hz[i][j]);
	}
	fr(i,1,n) {
		fr(j,1,m){
			printf("%d ",b[i][j]);
		}
		puts("");
	}
	return 0;
}
