#include<iostream>
using namespace std;
const int mod=1e9+7;
const int N=20;
long long list[N],now=0,sum;
long long ans=0;
long long binpow(long long x,int y){
	if(y==-1){
		return 0;
	}
	long long tich=1;
	while(y){
		if(y%2==1){
			tich*=x;
			tich%=mod;
		}
		x*=x;
		x%=mod;
		y>>=1;
	}
	return tich;
}
void check(int state){
	long long tich=1;
	for(int i=1;i<=now;i++){
		if((state&(1<<(i-1)))){
			tich*=list[i];
		}
	}	
	if(__builtin_popcount(state)%2==0){
		ans+=binpow(2,sum/tich-1);
		if(ans>=mod){
			ans-=mod;
		}
	}
	else{
		ans-=binpow(2,sum/tich-1);
		if(ans<0){
			ans+=mod;
		}
	}
}
void back(int x,int state){
	if(x==now+1){
		check(state);
		return;
	}
	back(x+1,state);
	back(x+1,(state|(1<<(x-1))));
}
int main(){
	int x,y,i;
	cin>>x>>y;
	if(y%x!=0){
		cout<<0;
		return 0;
	}
	y/=x;
	sum=y;
	for(i=2;i*i<=y;i++){
		if(y%i==0){
			while(y%i==0){
				y/=i;
			}
			now++;
			list[now]=i;
		}
	}
	if(y>1){
		now++;
		list[now]=y;
	}
	back(1,0);
	cout<<ans;
}