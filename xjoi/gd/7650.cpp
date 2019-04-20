#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1010;
queue<int>q;
int a[N];
char lx[2];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		int x;
		scanf("%s",lx+1);
		if(lx[1]=='+') scanf("%d",&x),q.push(x);
		else q.pop();
	}
	int res=0;
	while(!q.empty()) a[++res]=q.front(),q.pop();
	rf(i,res,1) printf("%d ",a[i]);
	return 0;
}