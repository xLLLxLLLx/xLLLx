#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	srand(time(NULL));
	int n=rand()%15+1;
	cout<<n<<endl;
	fr(i,1,n){
		int x=rand()%10+1;
		printf("%d ",x);
	}
	return 0;
}