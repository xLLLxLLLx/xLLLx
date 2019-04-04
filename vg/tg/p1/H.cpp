#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5;
int a[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int main(){
	int k;read(k);
	if(k==1) return printf("YES\n2 1\n1 2\n"),0;
	else if(k%2==0) return printf("NO\n"),0;
	else {
		printf("YES\n");
		printf("%d %d\n",(k+2)*2,(k+2)*k);
		a[1]=1,a[2]=k+1,a[3]=k+2;
		fr(o,1,3) fr(i,2,k) printf("%d %d\n",a[o],i);
		fr(i,2,k) fr(j,i+1,k){
			if(i%2==0) if(j==i+1) continue;
			printf("%d %d\n",i,j);
		}
		printf("%d %d\n",a[2],a[3]);
		int pos=k+2;
		fr(o,1,3) fr(i,2,k) printf("%d %d\n",a[o]+pos,i+pos);
		fr(i,2,k) fr(j,i+1,k){
			if(i%2==0) if(j==i+1) continue;
			printf("%d %d\n",i+pos,j+pos);
		}
		printf("1 %d\n",pos+1);
		printf("%d %d\n",a[2]+pos,a[3]+pos);
	}
	return 0;
}