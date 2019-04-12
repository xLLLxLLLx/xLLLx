#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
struct data{
	LL x,y;
}a[N];
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
char ch[4]={'R','D','L','U'};
vector<LL>v;

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y);
	int flg=0;
	fr(i,1,n){
		if(i==1) flg=(a[i].x+a[i].y)&1;
		else if(flg!=((a[i].x+a[i].y)&1)) return printf("-1\n"),0;
	}
	rf(i,30,0) v.push_back(1LL<<i);
	if(!flg) v.push_back(1);
	int len=v.size();
	printf("%d\n",len);
	fr(i,0,len-1) printf("%lld ",v[i]);
	puts("");
	fr(i,1,n){
		LL xx=a[i].x,yy=a[i].y;
		fr(j,0,len-1){
			LL minn=1e18,res=-1;
			fr(o,0,3){
				LL nx=xx-v[j]*dx[o],ny=yy-v[j]*dy[o];
				if(minn>abs(nx)+abs(ny)) minn=abs(nx)+abs(ny),res=o;
			}
			xx-=v[j]*dx[res],yy-=v[j]*dy[res];
			printf("%c",ch[res]);
		}
		puts("");
	}
	return 0;
}