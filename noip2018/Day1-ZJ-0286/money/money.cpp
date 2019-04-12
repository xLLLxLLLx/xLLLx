#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=110,M=2.5e4+10;
int a[N],n,vis[M];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void rd(){
	freopen("money.in","r",stdin);
	freopen("money.out","w",stdout);
}

int qx[M];

int main(){
	rd();
	int T;read(T);
	fr(o,1,T){
		read(n);
		int res=0,cnt=1,maxn=0;
		qx[1]=0;
		fr(i,1,n) {
			read(a[i]);
			if(a[i]>maxn) maxn=a[i];
		}
		sort(a+1,a+1+n);
		fr(i,1,n){
			if(vis[a[i]]!=o) {
				res++;
				int now=1,tmp=cnt;
				for(;;){
					int kk=a[i]*now;
					if(kk>maxn) break;
					if(vis[kk]==o) break;
					fr(j,1,cnt) {
						int pos=qx[j]+kk;
						if(pos>maxn||vis[pos]==o) continue;
						vis[pos]=o,qx[++tmp]=pos;
					}
					now++;
				}
				cnt=tmp;
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
