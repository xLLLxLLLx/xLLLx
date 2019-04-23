#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int gcd(int a,int b){
	return b ? gcd(b,a%b) : a ;
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		int x;scanf("%d",&x);
		x*=2;
		int pos=gcd(x,360);
		if(x>=180&&x+pos==360) printf("%d\n",720/pos); 
			else printf("%d\n",360/pos);
	}
	return 0;
}