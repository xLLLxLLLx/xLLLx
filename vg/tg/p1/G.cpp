#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int a[N];
char lx[N];

int main(){
	scanf("%s",lx+1);
	int n=strlen(lx+1);
	fr(i,1,n) a[i]=lx[i]-'0';
	fr(i,1,n) if(!a[i]||a[i]==8) return printf("YES\n%d\n",a[i]),0;
	fr(i,1,n)
	 fr(j,i+1,n){
	 	int pos=a[i]*10+a[j];
	 	if(pos%8==0) return printf("YES\n%d%d\n",a[i],a[j]),0;
	 }
	fr(i,1,n)
	 fr(j,i+1,n)
	  fr(k,j+1,n){
	  	int kk=(a[i]*100+a[j]*10+a[k])%8;
	  	if(!kk) return printf("YES\n%d%d%d\n",a[i],a[j],a[k]),0;
	  }
	printf("NO\n");
	return 0;
}
