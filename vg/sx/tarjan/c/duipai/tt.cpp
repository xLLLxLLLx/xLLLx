#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	srand(time(NULL));
	int T=rand()%5+1;
	fr(o,1,T) {
		int n=rand()%8+2,m=rand()%15+1;
		cout<<n<<" "<<m<<endl;
		fr(i,1,m) {
			int x=rand()%n+1,y=rand()%n+1;
			if(x==y) {
				if(x>1) x--;
				else if(y>1) y--;
			}
			printf("%d %d\n",x,y);
		}
		int q=rand()%8+1;
		printf("%d\n",q);
		fr(i,1,q) {
			int x=rand()%m+1;
			int y=rand()%m+1;
			printf("%d %d\n",x,y);
		}
	}
	printf("0 0\n");
	return 0;
}