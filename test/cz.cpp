#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
struct data{
	int x,y;
	data(){ x=0,y=0; }
	data(int a,int b){ x=a,y=b; }
	data operator + (const data &C){
	return (data){x*C.x,y-C.y};
}
}A,B,C;

int main(){
	A=data(1,2),B=data(2,3);
	C=B+A;
	printf("%d %d\n",C.x,C.y);
	return 0;
}