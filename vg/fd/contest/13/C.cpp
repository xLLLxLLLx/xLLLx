#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
char lx[N];
vector<int>qx[30];
int a[30];

int main(){
	scanf("%s",lx+1);
	int len=strlen(lx+1);
	fr(i,1,len){
		int pos=lx[i]-'a'+1;
		qx[pos].push_back(i);
	}
	int lst=0;
	rf(i,26,1){
		int len=qx[i].size();
		if(len) {
			int l=0,r=len-1,ans=-1;
			while(l<=r) {
				int mid=(l+r)>>1;
				if(qx[i][mid]<lst) l=mid+1;
				else r=mid-1,ans=mid;
			}
			if(ans!=-1) {
				lst=qx[i][len-1];
				a[i]=len-ans;
			}
		}
	}
	rf(i,26,1){
		fr(j,1,a[i]) printf("%c",char(i+'a'-1));
	}
	return 0;
}
