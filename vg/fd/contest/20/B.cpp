#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
int a[N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) scanf("%d",&a[i]);
	int minn=n+1,ans=-1;
	fr(i,1,n){
		int flg=1,pos=0;
		fr(j,1,n){
			int zz=(a[i]+(j-i)*k);
			if(zz<=0) {
				flg=0;break;
			}
			if(zz!=a[j]) pos++;
		}
		if(flg){
			if(pos<=minn) ans=i,minn=pos;
		}
	}
	printf("%d\n",minn);
	if(!minn) return 0;
	fr(i,1,n){
		int zz=(a[ans]+(i-ans)*k);
		if(a[i]>zz) printf("- %d %d\n",i,a[i]-zz);
		else if(a[i]<zz) printf("+ %d %d\n",i,zz-a[i]);
	}
	return 0;
}
