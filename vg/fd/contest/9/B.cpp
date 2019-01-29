#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
LL d[N];
int vis[N],c[N];
LL a[N][N],b[N][N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) fr(j,1,n) scanf("%lld",&a[i][j]);
	fr(i,1,n) scanf("%d",&c[i]);
	memset(b,0x3f,sizeof b);
	rf(o,n,1) {
		int pos=c[o];vis[pos]=1;
		fr(i,1,n)
			if(vis[i]) b[i][pos]=a[i][pos],b[pos][i]=a[pos][i];
		fr(i,1,n) {
			if(!vis[i]) continue;
			fr(j,1,n) {
				if(!vis[j]) continue;
				b[j][pos]=min(b[j][pos],b[j][i]+b[i][pos]);
				b[pos][j]=min(b[pos][j],b[pos][i]+b[i][j]);
			}
		}
		fr(i,1,n) fr(j,1,n) {
			if(vis[i]&&vis[j]) b[i][j]=min(b[i][j],b[i][pos]+b[pos][j]);
		}
		fr(i,1,n) {
			if(!vis[i]) continue;
			fr(j,1,n) {
				if(!vis[j]) continue;
				d[o]+=b[i][j]; 
			}
		}
	}
	fr(i,1,n) printf("%lld ",d[i]);
	return 0;
}
