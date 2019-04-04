#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;

int main(){
	srand(time(NULL));
	int n=30000;
	cout<<n<<endl;
	fr(i,1,n){
		int k=rand()%10007,p=rand()%n+1,b=rand()%10007;
		cout<<k<<" "<<p<<" "<<b<<endl;
	}
	cout<<"10000"<<endl;
	fr(i,1,10000){
		int x=rand()%5;
		if(!x) {
			int y=rand()%n+1,p=rand()%n+1,b=rand()%10007,k=rand()%10007;
			printf("C %d %d %d %d\n",y,k,p,b);
		} else {
			int y=rand()%n+1;
			printf("A %d\n",y);
		}
	}
	return 0;
}
