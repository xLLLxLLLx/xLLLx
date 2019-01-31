#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	srand(time(NULL));
	cout<<"1000"<<endl;
	fr(i,1,1000){
		int n=rand()%16+1;
		cout<<n<<endl;
		fr(j,1,n){
			int x=rand()%2000-1000,y=rand()%2000-1000;
			cout<<x<<" "<<y<<endl;
		}
	}
}
