#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
const db pi=acos(-1);
db a[N],b[N];
db X,Y;

db pf(db x){
	return x*x;
}

db dis(db x,db y){
	return pf(x-X)+pf(y-Y);
}

int main(){
	int n;scanf("%d",&n);
	scanf("%lf%lf",&X,&Y);
	db minn=1e18,maxn=0;
	fr(i,1,n){
		scanf("%lf%lf",&a[i],&b[i]);
		db pos=dis(a[i],b[i]);
		minn=min(minn,pos),maxn=max(maxn,pos);
	}
	a[n+1]=a[1],b[n+1]=b[1];
	fr(i,1,n){
		db posx=a[i]-a[i+1],posy=b[i]-b[i+1];
		if(!posx) {
			if(Y>=b[i+1]&&Y<=b[i]) minn=min(pf(X-a[i]),minn);
			if(Y>=b[i]&&Y<=b[i+1]) minn=min(pf(X-a[i]),minn);
		}
		else if(!posy) {
			if(X>=a[i+1]&&X<=a[i]) minn=min(pf(Y-b[i]),minn);
			if(X>=a[i]&&X<=a[i+1]) minn=min(pf(Y-b[i]),minn);
		}
		else {
			db kk,k,c,cc;
			k=posy/posx;c=b[i]-k*a[i];
			kk=-1.0/k;cc=Y-kk*X;
			db js=(cc-c)/(k-kk);
			db sj=kk*js+cc;
			db tmp=dis(js,sj);
			if(js>=a[i+1]&&js<=a[i]) minn=min(minn,tmp);
			if(js>=a[i]&&js<=a[i+1]) minn=min(minn,tmp);
		}
	}
	//cout<<maxn<<" "<<minn<<endl;
	printf("%.18f\n",(maxn-minn)*pi);
	return 0;
}
