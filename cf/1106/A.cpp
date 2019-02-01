#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
int bx[4]={-1,-1,1,1};
int by[4]={-1,1,-1,1};
int a[N][N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) fr(j,1,n){
		char ch;cin>>ch;
		if(ch=='X') a[i][j]=1;
	}
	int ans=0;
	fr(i,1,n) fr(j,1,n){
		if(!a[i][j]) continue;
		int flg=1;
		fr(t,0,3){
			int xx=i+bx[t],yy=j+by[t];
			if(xx<0||xx>n||yy<0||yy>n) {
				flg=0;break;
			}
			if(a[xx][yy]!=a[i][j]) { flg=0;break; }
		}
	//	if(flg) printf("%d %d\n",i,j);
		ans+=flg;
	}
	printf("%d\n",ans);
	return 0;
}
