#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=110;
int a[N];

int main(){
	int T;cin>>T;
	fr(o,1,T){
		int n;scanf("%d",&n);
		fr(i,1,n) scanf("%1d",&a[i]);
		int l=-1;
		fr(i,1,n){
			if(a[i]==8) {l=i;break;}
		}
		if(l==-1||n-l+1<11) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}