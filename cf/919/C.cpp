#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2010;
char lx[N][N];

int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	fr(i,1,n) scanf("%s",lx[i]+1);
	int ans=0;
	fr(i,1,n){
		int res=0;
		fr(j,1,m){
			if(lx[i][j]=='.') res++;
			else res=0;
			if(res>=k) ans++;
		}
	}
	fr(j,1,m){
		int res=0;
		fr(i,1,n){
			if(lx[i][j]=='.') res++;
			else res=0;
			if(res>=k) ans++;
		}
	}
	if(k==1) ans/=2;
	cout<<ans<<endl;
	return 0;
}