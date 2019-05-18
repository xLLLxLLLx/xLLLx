#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=2e5+10;
char lx[N];
string ll;

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	int lt=1;
	ll="";
	ll+=lx[1];
	int nw=1,res=0;
	fr(i,2,n){
		if(lx[i]==lx[nw]) res++;
		else {
			ll+=lx[i];
			if(i+1<=n) ll+=lx[i+1];
			nw=i=i+1;
		}
	}
	int len=ll.length();
	if(len&1) res++;
	cout<<res<<endl;
	if(len&1) fr(i,0,len-2) cout<<ll[i];
	else cout<<ll;
	puts("");
	return 0;
}