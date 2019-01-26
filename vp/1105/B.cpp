#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int n,k,a[30];
char lx[N];

int main(){
	cin>>n>>k;
	scanf("%s",lx+1);
	int l=1;
	fr(i,2,n){
		if(l==k) a[lx[i-1]-'a'+1]++,l=0;
		if(lx[i]==lx[i-1]) l++;
		else l=1;
	}
	if(l==k) a[lx[n]-'a'+1]++;
	int maxn=0;
	fr(i,1,26) maxn=max(maxn,a[i]);
	printf("%d\n",maxn);
	return 0;
}
