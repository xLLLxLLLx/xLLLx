#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5e5+10;
char lx[N],ll[N];

int main(){
	scanf("%s",lx+1);
	int lenx=strlen(lx+1);
	fr(i,1,lenx){
		if(lx[i]=='1') res++;
		else cnt++;
	}
	scanf("%s",ll+1);
	int leny=strlen(ll+1);
	if(leny>lenx) fr(i,1,lenx) cout<<lx[i];
	else {
		fr(i,1,leny){
			
		}
	}
	return 0;
}
