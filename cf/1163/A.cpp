#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	int pos=n/2;
	if(!m) printf("1\n");
	else if(m<=pos) printf("%d\n",m);
	else printf("%d\n",n-m);
	return 0;
}