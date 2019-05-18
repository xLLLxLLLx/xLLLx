#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<set>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define db double
using namespace std;
const int N=1e6+10;
struct node{
	db x,y;
}q[N],d[N],xs[N];

bool cmp(node A,node B){
	if(A.x==B.x) return A.y<B.y;
	else return A.x<B.x;
}

void get(node A,node B){
	
}

void js(node A,node B){
	if(!A.x){

	}
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lf%lf",q[i].x,q[i].y);
	int tot=0,ans=0;
	fr(i,1,n) fr(j,i+1,n){

	}
	sort(xs+1,xs+1+tot,cmp);
	fr(i,1,tot){
		if(xs[i]==xs[i-1]) continue;
		fr(j,i+1,tot){
			if(xs[j+1]==xs[j-1]) continue;
			js(xs[i],xs[j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}