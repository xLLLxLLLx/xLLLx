#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
int a[N],st[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%d",&a[i]);
	int head=1,tail=0;
	fr(i,1,n){
		while(head<=tail&&a[i]<=a[st[tail]]) tail--;
		st[++tail]=i;
		while(head<=tail&&st[head]+m-1<i) head++;
		if(i>=m) printf("%d ",a[st[head]]);		
	}
	puts("");
	head=1,tail=0;
	fr(i,1,n){
		while(head<=tail&&a[i]>=a[st[tail]]) tail--;
		st[++tail]=i;
		while(head<=tail&&st[head]+m-1<i) head++;
		if(i>=m) printf("%d ",a[st[head]]);
	}
	return 0;
}