#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
#define LL long long
#define pb push_back
using namespace std;

int main(){
	cout<<"200"<<endl;
	fr(i,1,200){
		printf("%d %d\n",i*2+1,i*10+1);
	}
	cout<<"200"<<endl;
	fr(i,1,200){
		int x=rand()%200+1;
//		int y=rand()%10000+1;
		int y=10000;
		cout<<x<<" "<<y<<endl;
	}
	return 0;
}
