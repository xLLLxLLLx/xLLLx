#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	srand(time(NULL));
	int n=50000;
	cout<<n<<endl;
	fr(i,2,n) {
		int x=rand()%(i-1)+1;
		printf("%d %d\n",i,x);
	}
	return 0;
}