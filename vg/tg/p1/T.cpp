#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=2e6+10;
int a[N],b[M];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]),b[a[i]]=1;
	fr(i,1,n){
		int A=a[i],B=0;
		fr(j,i+1,n){
			A|=a[j],B|=a[j];
			b[B]=1;b[A]=1;
			if(A==B) break;
		}
	}
	int ans=0;
	fr(i,0,M-1) if(b[i]) ans++;
	printf("%d\n",ans);
	return 0;
}
