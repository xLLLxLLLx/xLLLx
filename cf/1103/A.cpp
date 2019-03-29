#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
char lx[N];

int main(){
	scanf("%s",lx+1);
	int len=strlen(lx+1);
	int pos=0,tmp=0;
	fr(i,1,len){
		if(lx[i]=='0'){
			printf("1 %d\n",pos+1);
			pos=(pos+1)%4;
		} else {
			printf("4 %d\n",tmp+1);
			tmp=(tmp+2)%4;
		}
	}
	return 0;
}