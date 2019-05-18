#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<bitset>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int M=55;
bitset<10010>a[M],tot;

int main(){
	int m,n;scanf("%d%d",&m,&n);
	fr(i,1,n) tot[i]=1;
	fr(i,1,m){
		int x;scanf("%d",&x);
		fr(j,1,x){
			int y;scanf("%d",&y);
			a[i][y]=1;
		}
		fr(j,1,i-1) {
			if((a[j]&a[i]).count()==x) return printf("impossible\n"),0;
		}
		a[i]^=tot;
	}
	printf("possible\n");
	return 0;
}