#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1010,M=110;
char lx[M][N];

int main(){
	int n;scanf("%d",&n);
	int maxn=0;
	fr(i,1,n) scanf("%s",lx[i]+1);
	fr(i,1,26) fr(j,1,26){
		int tmp=0;
		fr(k,1,n){
			int flg=1;
			int len=strlen(lx[k]+1);
			fr(t,1,len){
				int pos=lx[k][t]-'a'+1;
				if(pos!=i&&pos!=j){
					flg=0;break;
				}
			}
			tmp+=flg*len;
		}
		maxn=max(maxn,tmp);
	}
	cout<<maxn<<endl;
	return 0;
}
