#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010,M=1e6+10;
int b[N],p[M],c[N];
queue<int>q;

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,k){
		int x;scanf("%d",&x);
		b[x]=1;
		if(x==n) return printf("1\n"),0;
	}
	memset(p,0x3f,sizeof p);
	fr(i,0,1000) if(b[i]) {
		c[++c[0]]=i-n;
		if(c[c[0]]>0) {
			//cout<<c[c[0]]<<endl;
			q.push(c[c[0]]),p[c[c[0]]]=1;
		}
	}
	while(!q.empty()){
		int zz=q.front();q.pop();
		fr(i,1,c[0]) {
			int pos=c[i]+zz;
			if(pos<0) continue;
			if(p[pos]>p[zz]+1) p[pos]=p[zz]+1,q.push(pos);
			if(!pos) return printf("%d\n",p[pos]),0;
		}
	}
	printf("-1\n");
	return 0;
}
