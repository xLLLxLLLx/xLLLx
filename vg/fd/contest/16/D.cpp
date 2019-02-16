#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
int A,B;
int fd[N];
LL d[N];
char lx[N],ll[N];

int main(){
	scanf("%d%d",&A,&B);
	scanf("%s%s",lx+1,ll+1);
	int lenx=strlen(lx+1),lenl=strlen(ll+1);
	fr(i,1,lenl){
		int tmp=i;
		fr(j,1,lenx){
			if(lx[j]==ll[tmp]){
				if(tmp==lenl) tmp=0,d[i]++;
				tmp++;
			}
		}
		fd[i]=tmp;
	}
	int x=1,ans=0;
	fr(i,1,A){
		ans+=d[x];
		x=fd[x];
	}
	printf("%d\n",ans/B);
	return 0;
}
