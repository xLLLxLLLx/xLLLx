#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
char lx[N];

int main(){
	scanf("%s",lx+1);
	int n=strlen(lx+1);
	if(lx[n]=='1'||lx[1]=='0'||lx[n-1]=='0') return printf("-1\n"),0;
	fr(i,1,n/2) if(lx[i]!=lx[n-i]) return printf("-1\n"),0;
	int nw=2,rt=2,nm=1;
	printf("1 2\n");
	fr(i,2,n/2){
		if(lx[i]=='1'){
			printf("%d %d\n",++nw,rt);
			rt=nw;
		} else printf("%d %d\n",++nw,rt);
		nm++;
	}
	fr(i,nm+1,n-1) printf("%d %d\n",++nw,rt);
	return 0;
}