#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int a[N];

int main(){
	int n;scanf("%d",&n);
	int maxn=0;
	fr(i,1,n) scanf("%d",&a[i]),maxn=max(maxn,a[i]);
	int pos=0,lt=0;
	fr(i,1,n){
		if(a[i]==maxn) lt++;
		else pos=max(pos,lt),lt=0;
	}
	pos=max(pos,lt);
	cout<<pos<<endl;
	return 0;
}
