#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
int A[N],B[N];

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int main(){
	int n,m;cin>>n>>m;
	fr(i,1,n+1) cin>>A[i];
	fr(i,1,m+1) cin>>B[i];
	if(n>m) {
		int flg=0;
		if(A[1]<0) flg^=1;
		if(B[1]<0) flg^=1;
		if(flg) printf("-Infinity\n");
		else printf("Infinity\n");
		return 0;
	}
	else if(n<m) return printf("0/1\n"),0;
	else {
		int flg=0;
		if(A[1]<0) flg^=1,A[1]=-A[1];
		if(B[1]<0) flg^=1,B[1]=-B[1];
		int pos=gcd(max(A[1],B[1]),min(A[1],B[1]));
		if(flg) printf("-%d/%d\n",A[1]/pos,B[1]/pos);
		else printf("%d/%d\n",A[1]/pos,B[1]/pos);
	}
	return 0;
}
