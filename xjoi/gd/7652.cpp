#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1010;
queue<int>q;
int vis[N];

int main(){
	int n,m;scanf("%d%d",&m,&n);
	int ans=0;
	fr(i,1,n){
		int x;scanf("%d",&x);
		if(vis[x]) 233;
		 else {
		 	ans++;
		 	if(q.size()==m) vis[q.front()]=0,q.pop();
		 	vis[x]=1,q.push(x);
		 }
	}
	cout<<ans<<endl;
}