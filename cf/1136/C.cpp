#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
map<int,int>mp[N];

int main(){
    int n,m;scanf("%d%d",&n,&m);
    fr(i,1,n) fr(j,1,m) {
        int x;scanf("%d",&x);
        mp[i+j][x]++;
    }
    fr(i,1,n) fr(j,1,m) {
        int x;scanf("%d",&x);
        if(!mp[i+j][x]) return printf("No\n"),0;
        mp[i+j][x]--;
    }
    printf("Yes\n");
    return 0;
}
