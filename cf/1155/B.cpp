#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define db double
using namespace std;
const int N=1e5+10;
int a[N],b[N];

void fail(){
	printf("NO\n");
	exit(0);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) {
		scanf("%1d",&a[i]);
		if(a[i]==8) b[++b[0]]=i;
	}
	int res=(n-11)/2;
	if(b[0]<=res) fail();
	else {
		int pos=b[res+1];
		int gg=pos-res-1;
		if(gg<=res) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}