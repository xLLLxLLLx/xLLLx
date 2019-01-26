#include<bits/stdc++.h>
#define fi first
#define se second
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
map<LL,string>mp;
map<LL,string> :: iterator sit;

char zh(int z){
	return char(z+'0');
}

string Get(LL x){
	string ll="",lx="";
	int res=0;
	for(;x;){
		res++;
		int pos=x%10;x/=10;
		ll+=zh(pos);
	}
	rf(i,res-1,0) lx+=ll[i];
	return lx;
}

int main(){
	LL n;cin>>n;
	for(LL i=2;i*i<=n;++i){
		int k=1;
		for(LL j=i*i;j<=n;j*=i){
			string pos="";k++;
			pos+=Get(i)+"^"+Get(k);
			if(!mp.count(j)) mp[j]=Get(j);
			if(pos.length()<mp[j].length()) mp[j]=pos;
		}
	}
	string ans=Get(n);
	for(sit=mp.begin();sit!=mp.end();++sit){
		string pos="",gg=(*sit).se;LL tmp=(*sit).fi;
		LL k=n/tmp,yu=n%tmp;
		if(k>1) {
			if(!mp.count(k)) pos+=Get(k)+"*"+gg;
			else pos+=mp[k]+"*"+gg;
		} else pos+=gg; 
		if(yu>0){
			if(!mp.count(yu)) pos+="+"+Get(yu);
			else pos+="+"+mp[yu];
		}
		if(ans.length()>pos.length()) ans=pos;
	}
	cout<<ans<<endl;
	return 0;
}
