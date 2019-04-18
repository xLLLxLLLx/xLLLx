#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define SF scanf
#define PF printf
#define MAXN 300010
#define y1 chunhua
using namespace std;
typedef long long ll;
ll x,y;
ll a[MAXN];
vector<ll> fac,facn;
vector<int> facx,facy;
vector<pair<int,int> >facv;
vector<ll> check;
int n;
ll sum[MAXN];
/*ll gcd(ll x,ll y){
    if(y==0)
        return x;
    return gcd(y,x%y);  
}*/
void factorize(ll val){
    /*for(ll i=2;i<=val&&i<=1000000ll;i++)
        if(val%i==0){
            fac.push_back(i);
            while(val%i==0)
                val/=i;
        }*/
    if(val>1){
        ll q=(long long)(sqrt(val));
        if(q*q==val){
            fac.push_back(q);
            return ;    
        }
        for(int i=1;i<=n;i++)
            check.push_back(a[i]);
        check.push_back(x);
        check.push_back(y);
        ll g=val;
        for(int i=0;i<check.size();i++){
            g=gcd(val,check[i]);
            if(g!=1&&g!=val){
                if(g<val/g){
                    fac.push_back(g);
                    fac.push_back(val/g);
                }
                else{
                    fac.push_back(val/g);
                    fac.push_back(g);   
                }
                return ;
            }
        }
        fac.push_back(val);
    }
}
int main(){
    /*SF("%d%lld%lld",&n,&x,&y);
    for(int i=1;i<=n;i++)
        SF("%lld",&a[i]);
    if(y%x){
        PF("0");
        return 0;   
    }*/
    factorize(y);
    for(int i=0;i<fac.size();i++)
        facv.push_back(make_pair(0,0));
    ll x1=x;
    ll y1=y;
    for(int i=0;i<fac.size();i++){
        int cnt=0;
        while(x1%fac[i]==0){
            x1/=fac[i];
            cnt++;  
        }
        facv[i].first=cnt;
    }
    for(int i=0;i<fac.size();i++){
        int cnt=0;
        while(y1%fac[i]==0){
            y1/=fac[i];
            cnt++;  
        }
        facv[i].second=cnt;
    }

    for(int i=0;i<fac.size();i++){
        if(facv[i].first!=facv[i].second){
            facn.push_back(fac[i]);
            facx.push_back(facv[i].first);
            facy.push_back(facv[i].second); 
        }
    }

    for(int i=1;i<=n;i++){
        if(a[i]%x)
            continue;
        ll val=a[i];
        int mask=0;
        for(int j=0;j<facn.size();j++){
            int cnt=0;
            while(val%facn[j]==0){
                val/=facn[j];
                cnt++;  
            }
            mask+=((cnt>facx[j])<<j);
        }
        sum[mask]++;
    }
    for(int i=0;i<facn.size();i++)
        for(int mask=0;mask<(1<<facn.size());mask++)
            if(mask&(1<<i))
                sum[mask]+=sum[mask-(1<<i)];
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(y%a[i])
            continue;
        ll val=a[i];
        int mask=0;
        for(int j=0;j<facn.size();j++){
            int cnt=0;
            while(val%facn[j]==0){
                val/=facn[j];
                cnt++;  
            }
            mask+=((cnt<facy[j])<<j);
        }
        ans+=sum[(1<<facn.size())-mask-1];
    }
    PF("%lld",ans);
}