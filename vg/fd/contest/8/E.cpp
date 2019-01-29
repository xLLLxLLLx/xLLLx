#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=30;
int a[N],n,b[N];

void out(){
	printf("0\n");
	fr(i,1,n){
		fr(j,1,a[i]){
			printf("%c",char(i+'a'-1));
		}
	}
	exit(0);
}

int main(){
	scanf("%d",&n);
	if(n==1){
		int x;scanf("%d",&x);
		printf("%d\n",x);
		fr(i,1,x) printf("a");
		return 0;
	}
	int res=0,sum=0,be=-1;
	fr(i,1,n) {
		scanf("%d",&a[i]);
		if(a[i]&1) be=i,res++;
		sum+=a[i];
	}
	int cnt=0;
	if(res>=2) out();
	if(res) printf("1\n");
	else {
		printf("%d\n",sum/2+1);//when on test... xLLLx tried in luangaoQAQ
	}
	fr(i,1,n){
		if(i==be) continue;
		fr(j,1,a[i]/2){
			b[++cnt]=i;
		}
	}
	if(be!=-1){
		fr(i,1,a[be]) b[++cnt]=be;
	}
	rf(i,n,1){
		if(i==be) continue;
		fr(j,1,a[i]/2){
			b[++cnt]=i;
		}
	}
	fr(i,1,sum) printf("%c",char(b[i]+'a'-1));
	return 0;
}
