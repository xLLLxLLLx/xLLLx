#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e7+10;
int nm[15]={6,2,5,5,4,5,6,3,7,6};
int a[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int main(){
	int n,k;read(n),read(k);
	k=n/k;
	fr(i,0,9) a[i]=nm[i];
	fr(i,10,n) {
		a[i]=a[i/10]+nm[i%10];
	//	cout<<i<<" "<<a[i]<<endl;
	}
	int ans=0;
	k-=(4+a[n]);
	fr(i,1,n/2){
		if(a[i]+a[n-i]==k) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
