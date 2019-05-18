#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
#define db double
using namespace std;
const int N=1e5+10;

int main(){
	int n,m;
	int res=0,tmp=0;
	cin>>n>>m;
	fr(i,1,n){
		int x;scanf("%d",&x);
		if(x&1) res++;
	}
	fr(i,1,m){
		int x;scanf("%d",&x);
		if(x&1) tmp++;
	}
	int ans=min(res,m-tmp)+min(tmp,n-res);
	cout<<ans<<endl;
	return 0;
}