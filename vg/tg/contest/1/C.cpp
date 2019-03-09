#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int rev[N],A[15];
LL qx[N];
int bx=-1,by=-1;
map<LL,LL>mp,pp;

int Rev(int x){
	A[0]=0;
	for(;x;x/=10) A[++A[0]]=x%10;
	int pos=0,kk=1;
	rf(i,A[0],1) pos+=A[i]*kk,kk*=10;
	return pos;
}

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

void fail(){
	printf("-1\n");
	exit(0);
}

void UPD(int x,int y,int z){
	int gg=gcd(max(x,y),min(x,y));
	x/=gg,y/=gg;
	LL pos=x*1LL*100000+y;
	mp[pos]+=z;
}

void Cha(int x,int y,int z){
	int gg=gcd(max(x,y),min(x,y));
	x/=gg,y/=gg;
	LL pos=x*1LL*100000+y;
	pp[pos]+=z;
}

LL Get(int x,int y){
	int gg=gcd(max(x,y),min(x,y));
	x/=gg,y/=gg;
	LL pos=y*1LL*100000+x;
	if(!mp.count(pos)) return 0LL;
	return mp[pos];
}

LL Ask(int x,int y){
	int gg=gcd(max(x,y),min(x,y));
	x/=gg,y/=gg;
	LL pos=y*1LL*100000+x;
	if(!pp.count(pos)) return 0LL;
	return pp[pos];
}

int main(){
	int maxx,maxy,w;
	cin>>maxx>>maxy>>w;
	fr(i,1,max(maxx,maxy)) rev[i]=Rev(i);
	fr(i,1,maxx) UPD(i,rev[i],1);
	LL pos=-1,nw=0,maxn=1e11;
	fr(i,1,maxy){
		Cha(i,rev[i],1);
		nw+=Get(i,rev[i]);
		//cout<<"i="<<i<<"nw="<<nw<<endl;
		if(nw>=w) {
			pos=i;
			maxn=min(maxn,pos*maxx);
			bx=maxx,by=pos;
			UPD(maxx,rev[maxx],-1);
			nw-=Ask(maxx,rev[maxx]);
			break;
		}
	}
	//cout<<nw<<endl;
	if(pos==-1) fail();
	rf(i,maxx-1,1){
		while(nw<w&&pos<maxy){
			pos++;
			Cha(pos,rev[pos],1);
			nw+=Get(pos,rev[pos]);
		}
		//cout<<i<<" "<<pos<<" "<<nw<<endl;
		if(nw<w) break;
		if(maxn>pos*1LL*i) maxn=pos*1LL*i,bx=i,by=pos;
		nw-=Ask(i,rev[i]);
		UPD(i,rev[i],-1);
	}
	printf("%d %d\n",bx,by);
	return 0;
}
