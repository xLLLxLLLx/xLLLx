#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
const int N=310;
int main(){
	srand(time(NULL));
	cout<<"300"<<endl;
	fr(i,1,300){
		int x=rand()%1000000000+1;
		cout<<x<<" ";
	}
	cout<<endl;
	fr(i,1,300){
		int x=rand()%100000+1;
		cout<<x<<" ";
	}
	return 0;
}
