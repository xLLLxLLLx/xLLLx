#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int w1,h1,w2,h2;
	cin>>w1>>h1>>w2>>h2;
	int pos=0;
	pos+=2*(h1+h2);
	pos+=2*max(w1,w2);
	pos+=4;
	cout<<pos<<endl;
	return 0;
}
