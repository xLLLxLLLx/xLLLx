#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=30,M=110;
char lx[M];
int nm[N];

int js(int x){
	return x*(x-1)/2;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		scanf("%s",lx+1);
		int pos=lx[1]-'a'+1;
		nm[pos]++;
	}
	int ans=0;
	fr(i,1,26){
		int res=nm[i]/2,tmp=nm[i]-res;
		ans+=js(res)+js(tmp);
	}
	cout<<ans<<endl;
	return 0;
}