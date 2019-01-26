#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010,M=12;
int bx[4]={1,0,-1,0};
int by[4]={0,1,0,-1};
int n,m,p,a[N][N],s[M],x[M][N*N],y[M][N*N],be[M],ed[M],tot[M];

int main(){
	cin>>n>>m>>p;
	fr(i,1,p) scanf("%d",&s[i]);
	fr(i,1,n)
	 fr(j,1,m){
	 	char ch;cin>>ch;
	 	if(ch>='1'&&ch<='9') {
	 		int pos=ch-'0';
	 		a[i][j]=pos,ed[pos]++;
	 		x[pos][ed[pos]]=i,y[pos][ed[pos]]=j;
	 	}
	 	if(ch=='#') a[i][j]=-1;
	 }
	for(;;){
		int ff=0;
		fr(i,1,p) fr(oo,1,s[i]) {
			int e=ed[i],flg=0;
			while(be[i]+1<=e){
				be[i]++;flg=1;ff=1;
				int nx=x[i][be[i]],ny=y[i][be[i]];
				fr(j,0,3) {
					int xx=nx+bx[j],yy=ny+by[j];
					if(xx<=0||xx>n||yy<=0||yy>m||a[xx][yy]) continue;
					a[xx][yy]=i;
					ed[i]++,x[i][ed[i]]=xx,y[i][ed[i]]=yy;
				 }
			}
			if(!flg) break;
		}
		if(!ff) break;
	}
	fr(i,1,n)
	 fr(j,1,m){
	 	if(a[i][j]!=-1) {
	 		//printf("%d %d %d\n",i,j,a[i][j]);
	 		tot[a[i][j]]++;
	 	}
	 }
	fr(i,1,p) printf("%d ",tot[i]);
	return 0;
}
