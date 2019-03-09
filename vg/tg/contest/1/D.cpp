#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
const db pi=acos(-1);
struct data{
	db x,y;
}a[N];
db ox,oy;
set<db>::iterator sit
set<db>st;

bool cmp(data xx,data yy){
	if(xx.x!=yy.x) return xx.x<yy.x;
	return xx.y<yy.y;
}

db Get(db x,db y){
	db posx=x-ox,posy=y-oy;
	if(!posx) {
		if(posy>0) Arg=90.0;
		else Arg=270.0;
		return Arg;
	}
	db Arg=atan(posy/posx)/pi*180.0;
	if(posx<0){
		if(posy<0) return Arg-180.0;
		else return Arg+180.0;
	} else{
		if(posy<0) return 360.0+Arg;
		else return Arg;
	}
}

db Cross(data A,data B){
	return A.x*B.y-A.y*B.x;
}

int main(){
	int n;scanf("%d",&q);
	db sumx=0,sumy=0;
	fr(i,1,3){
		scanf("%lf%lf",&a[i].x,&a[i].y);
		sumx+=a[i].x,sumy+=a[i].y;
	}
	ox=sumx/3.0,oy=sumy/3.0;
	fr(i,1,3) set.insert(Get(sumx-ox,sumy-oy));
	fr(i,1,q-3){
		int tp;db x,y;
		scanf("%d%lf%lf",&tp,&x,&y);
		if(tp==1){
			
		} else {
			
		}
	}
	return 0;
}
