#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=510,M=1e5+10;
struct data{
	db w;
	int rk;
}a[N];
int b[M],v[N],qx[N<<1];
string lz;
string lx[N],ll[N];

bool cmp(data xx,data yy){
	if(xx.w!=yy.w) return xx.w>yy.w;
	return ll[xx.rk]<ll[yy.rk];
}

void init(){
	fr(i,1000,9999){
		int flg=0,len=sqrt(i);
		fr(j,2,len){
			if(i%j==0) {
				flg=1;break;
			}
		}
		if(!flg) b[i]=1;
	}
}

bool comp(int x,int y){
	return x>y;
}

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		int n,m;scanf("%d%d",&n,&m);
		memset(b,0,sizeof b),memset(v,0,sizeof v);
		init();
		int t,x;scanf("%d",&t);

		fr(i,1,t) scanf("%d",&x),b[x]=2;
		scanf("%d",&t);

		fr(i,1,t) scanf("%d",&x),b[x]=3;
		int dw;scanf("%d",&dw);

		fr(i,1,dw) {
			cin>>lx[i];
			scanf("%d",&v[i]);
			if(v[i]==1) v[i]=36;
			if(v[i]==2) v[i]=27;
			if(v[i]==3) v[i]=18;
		}
		
		fr(i,1,n) a[i].w=0,a[i].rk=i;

		fr(i,1,n) {
			cin>>ll[i];cin>>lz;
			fr(j,1,dw){
				if(lz==lx[j]) {
					a[i].w+=v[j];
					break;
				}
			}
			char ch;cin>>ch;
			if(ch=='F') a[i].w+=33;
			int kk,tt;scanf("%d%d",&kk,&tt);
			fr(o,1,kk) {
				int x;scanf("%d",&x);
				if(b[x]==1) a[i].w+=1.0;
				else if(b[x]==2) a[i].w+=2.5;
				else if(b[x]==3) a[i].w+=1.5;
				else a[i].w+=0.3;
			}
			fr(o,1,tt) scanf("%d",&qx[o]);
			if(tt) sort(qx+1,qx+1+tt,comp);
			if(tt>=3) a[i].w+=db(db(max(0,(qx[3]-1200)))/100.0)*1.5;
		}
		sort(a+1,a+1+n,cmp);
		fr(i,1,m) {
			cout<<ll[a[i].rk]<<" ";
			printf("%.3lf\n",a[i].w);
		}
	}
	return 0;
}
