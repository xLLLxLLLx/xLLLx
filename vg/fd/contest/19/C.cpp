#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	LL r,h;scanf("%lld%lld",&r,&h);
	LL pos=2*(h/r);
	LL yu=h%r;
//	printf("%lld %lld\n",yu,pos);
	if(yu*2>=sqrt(3.0)*double(r)) pos+=3;
	else if(yu*2LL>=r) pos+=2;
	else pos++;
	cout<<pos<<endl;
	return 0;
}
