#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=310,M=1e6+10;
int a[N],b[M];

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	int res=0;
	fr(i,1,n){
		if(!a[i]){
			if(i!=n) b[++res]=3;
			continue;
		}
		if(i==n){
			b[++res]=1;
			a[i]--;
			fr(j,1,a[i]) b[++res]=2,b[++res]=3,b[++res]=1;
		}
		else {
			b[++res]=1;b[++res]=3;
			a[i]--;
			fr(j,1,a[i]) b[++res]=2,b[++res]=1,b[++res]=3;
		}
	}
	fr(i,1,res){
		if(b[i]==1) printf("P");
		if(b[i]==2) printf("L");
		if(b[i]==3) printf("R");
	}
	return 0;
}
