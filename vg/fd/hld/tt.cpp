#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n=10000;
	fr(o,1,20){
		cout<<"10000"<<endl;
		fr(i,2,n) {
			int x=rand()%(i-1)+1;
			int z=rand()%100000+1;
			printf("%d %d %d\n",i,x,z);
		}
		fr(i,1,n){
			cout<<"Q"<<endl;
			int x=rand()%n+1,y=rand()%n+1;
			printf("%d %d\n",x,y);
		}
		cout<<"D"<<endl;
	}
}
