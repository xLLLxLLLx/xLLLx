#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,M=1010;
int a[N],b[N],c[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		int y;
		scanf("%d%d",&a[i],&b[i]);
	}
	fr(i,1,n){
	 fr(j,1,n){
	 	if(i==j) continue;
	 	if(a[j]==b[i]) c[j]=1;
	 }
	}
	int ans=0;
	fr(i,1,n) if(!c[i]) ans++;
	printf("%d\n",ans);
	return 0;
}
