#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010;
struct data{
	int A,B,id;
}a[N];
int vis[N];

void fail(){
	printf("-1\n");
	exit(0);
}

bool cmp(data xx,data yy){
	if(xx.A!=yy.A) return xx.A>yy.A;
	return xx.B>yy.B;
}

int main(){
	int n,cnt=0,res=0;scanf("%d",&n);
	fr(i,1,n) a[i].id=i;
	fr(i,1,n) scanf("%1d",&a[i].A),cnt+=a[i].A;
	fr(i,1,n) scanf("%1d",&a[i].B),res+=a[i].B;
	int x=0,y=0,z=0,t=0;
	fr(i,1,n){
		if(a[i].A){
			if(a[i].B) x++;
			else y++;
		} else {
			if(a[i].B) z++;
			else t++;
		}
	}
	sort(a+1,a+1+n,cmp);
	fr(i,0,n/2){
		if(i>cnt||i>res) break;
		int tmp=res-i;
		fr(j,0,min(x,i)){
			int pos=i-j,sx=tmp-j,md=n/2-i-sx;
			if(pos>y||sx>z||md>t) continue;
			if(pos<0||sx<0||md<0) continue;
			//cout<<j<<" "<<pos<<" "<<sx<<" "<<md<<endl;
			fr(k,1,j) vis[a[k].id]=1;
			fr(k,x+1,x+pos) vis[a[k].id]=1;
			fr(k,x+y+1,x+y+sx) vis[a[k].id]=1;
			fr(k,x+y+z+1,x+y+z+md) vis[a[k].id]=1;
			fr(k,1,n) if(vis[k]) printf("%d ",k);
			return 0;
		}
	}
	fail();
	return 0;
}
