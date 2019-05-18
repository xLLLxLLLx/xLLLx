#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=5e5+10;
int f[N],nm[N];

int find(int k){
	return f[k]==k ? f[k] : f[k]=find(f[k]);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) f[i]=i;
	fr(o,1,m){
		int tot;scanf("%d",&tot);
		if(!tot) continue;
		int nw;scanf("%d",&nw);
		int fa=f[nw];
		fr(i,2,tot){
			int x;scanf("%d",&x);
			int fx=find(x),fy=find(fa);
			f[fx]=fy;
		}
	}
	fr(i,1,n) find(i);
	fr(i,1,n) nm[f[i]]++;
	fr(i,1,n) printf("%d ",nm[f[i]]);
	return 0;
}