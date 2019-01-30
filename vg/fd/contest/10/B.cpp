#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N][N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	int res=0;
	if(res<k){
	fr(i,1,n){
		int nw=i&1,flg=0;
		fr(j,1,n){
			if((j&1)==nw) a[i][j]=1,res++;
			if(res==k) {
				flg=1;break;
			}
		}
		if(flg) break;
	}
	}
	if(res<k) printf("NO\n");
	else {
		printf("YES\n");
		fr(i,1,n) {
			fr(j,1,n){
				if(a[i][j]) cout<<"L";
				else cout<<"S";
			}
			cout<<endl;
		}
	}
	return 0;
}
