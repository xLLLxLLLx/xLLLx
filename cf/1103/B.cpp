#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
string ll;

bool tp(){
	puts("? 0 1");
	fflush(stdout);
	char ch;cin>>ch;
	if(ch=='x'){
		puts("! 1");
		fflush(stdout);
		return true;
	} else return false;
}

int main(){
	for(;;){
		cin>>ll;
		if(ll=="end") return 0;
		if(tp()) continue;
		int l=1,r=5e8,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			printf("? %d %d\n",mid,mid*2);
			fflush(stdout);
			char ch;cin>>ch;
			if(ch=='x') ans=mid,
			else l=mid+1;
		}
		puts("! ans");
		fflush(stdout);
	}
	return 0;
}