#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	srand(time(NULL));
	int n=500000,m=500000;
	cout<<n<<" "<<m<<endl;
	fr(i,1,n) {
		int x=rand()%10000,y=rand()%10000;
		printf("%d %d\n",x,y);
	}
	fr(i,1,m) {
		int t=rand()%2+1,x=rand()%10000,y=rand()%10000;
		printf("%d %d %d\n",t,x,y);
	}
	return 0;
}