#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	srand(time(NULL));
	int n=100000;
	int k=rand()%100+1;
	cout<<n<<" "<<k<<endl;
	fr(i,1,n) {
		int x=rand()%100000001,y=rand()%100000001;
		printf("%lld %lld\n",y);
	}
	return 0;
}