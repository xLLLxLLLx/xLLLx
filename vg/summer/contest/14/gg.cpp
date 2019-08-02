#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,opt) for(int i=lst[a][opt];i;i=nxt[i])
using namespace std;

int read() {
    char ch;
    for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
    int x=ch-'0';
    for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x;
}

const int N=5*1e5+5;

int to[N<<2],nxt[N<<2],R[N<<2],lst[N][2],cnt;
void Add(int x,int y,int opt,int r) {
    to[++cnt]=y;R[cnt]=r;nxt[cnt]=lst[x][opt];lst[x][opt]=cnt;
}

int n,m,x,y,l,r,L[N][2];

struct node{
    int x,y,l,r;
    friend bool operator < (node x,node y) {return x.l<y.l;}
};

multiset<node> s;

void Extend(int x,int l,int r,int opt) {
    L[x][opt]=max(L[x][opt],r);
    rep(i,x,opt) {
        node p;
        p.x=x;p.y=to[i];
        p.l=l;p.r=R[i];
        s.insert(p);
    }
    lst[x][opt]=0;
}

int main() {
    n=read();m=read();
    if (n==1) {puts("0");return 0;}
    fo(i,1,m) {
        x=read();y=read();l=read();r=read()-1;
        node p;
        p.x=x;p.y=y;p.l=l;p.r=r-(r-l)%2;s.insert(p);
        p.x=y;p.y=x;p.l=l;p.r=r-(r-l)%2;s.insert(p);
        p.x=x;p.y=y;p.l=l+1;p.r=r-!((r-l)%2);s.insert(p);
        p.x=y;p.y=x;p.l=l+1;p.r=r-!((r-l)%2);s.insert(p);
    }
    memset(L,255,sizeof(L));
    L[1][0]=0;
    while (!s.empty()) {
        node p=*s.begin();s.erase(s.begin());
        if (p.l>p.r) continue;
        int x=p.x,y=p.y,opt=p.l&1;
        if (L[x][opt]>=p.l) {
            if (y==n) {
                printf("%d\n",p.l+1);
                return 0;
            }
            Extend(y,p.l+1,p.r+1,opt^1);
        } else Add(x,y,opt,p.r);
    }
    puts("-1");
    return 0;
}