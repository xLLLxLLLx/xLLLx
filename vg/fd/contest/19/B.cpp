#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int t[N],l[N],r[N];

int main(){
	int n,m,s,f;
	scanf("%d%d%d%d",&n,&m,&s,&f);
	fr(i,1,m) scanf("%d%d%d",&t[i],&l[i],&r[i]);
	int lt=0;
	if(s<f){
		int nw=s;
		fr(i,1,m){
			if(nw==f) return 0;
			fr(j,lt+1,t[i]-1){
				if(nw==f) return 0;
				nw++,printf("R");
			}
			if(nw==f) return 0;
			if(nw>=l[i]-1&&nw<=r[i]) printf("X");
			else nw++,printf("R");
			lt=t[i];
		}
		while(nw!=f) nw++,printf("R");
	} else {
		int nw=s;
		fr(i,1,m){
			if(nw==f) return 0;
			fr(j,lt+1,t[i]-1){
				if(nw==f) return 0;
				nw--;printf("L");
			}
			if(nw==f) return 0;
			if(nw>=l[i]&&nw<=r[i]+1) printf("X");
			else nw--,printf("L");
			lt=t[i];
		}
		while(nw!=f) nw--,printf("L");
	}
	return 0;
}
