#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=150010;
int f[N],nt[N],ed[N];

int find(int k){
	return f[k]==k?f[k]:f[k]=find(f[k]);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) f[i]=nt[i]=ed[i]=i;
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		//cout<<y<<" "<<fy<<endl;
		if(fx==fy) continue;
		nt[ed[fx]]=fy;
		ed[fx]=ed[fy];
		f[fy]=fx;
	}
	fr(i,1,n) if(f[i]==i){
		int lt=i;
		cout<<lt<<" ";
		while(nt[lt]!=lt) printf("%d ",nt[lt]),lt=nt[lt];
	}
	return 0;
}
