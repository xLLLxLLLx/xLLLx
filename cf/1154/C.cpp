#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=10;
int qz[N][3],js[N],mk[N];

int main(){
	int a,b,c;cin>>a>>b>>c;
	int maxn=0;
	mk[1]=mk[4]=mk[7]=0,mk[2]=mk[6]=1,mk[3]=mk[5]=2;
	fr(i,1,7){
		fr(o,0,2) qz[i][o]=qz[i-1][o];
		qz[i][mk[i]]++;
	}
	fr(i,1,7){
		js[0]=a,js[1]=b,js[2]=c;
		int pos=8-i;
		fr(j,i,7){
			int flg=1;
			fr(o,0,2) if(js[o]<(qz[j][o]-qz[i-1][o])) flg=0;
			if(!flg) {pos=j-i;break;}
		}
		//printf("%d %d\n",i,pos);
		if(pos!=8-i) maxn=max(maxn,pos);
		else {
			fr(o,0,2) js[o]-=qz[7][o]-qz[i-1][o];
			int res=1e9;
			fr(o,0,2) res=min(res,js[o]/qz[7][o]);
			pos+=res*7;
			fr(o,0,2) js[o]-=res*qz[7][o];
			int zz=0;
			fr(j,1,7) {
				int flg=1;
				fr(o,0,2) if(js[o]<qz[j][o]) flg=0;
				if(!flg) {zz=j-1;break;}
			}
			pos+=zz;
			maxn=max(maxn,pos);
		}
	}
	cout<<maxn<<endl;
	return 0;
}