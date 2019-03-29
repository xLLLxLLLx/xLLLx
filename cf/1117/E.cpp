#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10;
int ys[N],sy[N];
char lx[N],ll[N];

int main(){
	scanf("%s",ll+1);
	int len=strlen(ll+1);
	for(int i=1;i<=26*26;i*=26){
		fr(j,1,len) lx[j]=char((j/i)%26+'a');
		printf("? ");
		fr(j,1,len) cout<<lx[j];
		printf("\n");
		fflush(stdout);
		scanf("%s",lx+1);
		fr(j,1,len) ys[j]+=(lx[j]-'a')*i;
	}
	fr(i,1,len) sy[ys[i]]=i;
	printf("! ");
	fr(i,1,len) cout<<ll[sy[i]];
	return 0;
}
