#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N];

int main(){
	int n,x,y;
	cin>>n>>x>>y;
	fr(i,1,n) scanf("%1d",&a[i]);
	int res=0;
	rf(i,n,n-x+1) {
		if(i==n-y){
			if(!a[i]) res++;
			continue;
		}
		if(a[i]) res++;
	}
	printf("%d\n",res);
	return 0;
}