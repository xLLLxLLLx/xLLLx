#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N=105,M=20005;
const double eps=1e-8;
struct point
{
    double x,y;
    point(){}
    point(double _x,double _y):x(_x),y(_y){}
    inline friend point operator + (const point &a,const point &b)
    {return point(a.x+b.x,a.y+b.y);}
    inline friend point operator - (const point &a,const point &b)
    {return point(a.x-b.x,a.y-b.y);}
    inline friend point operator * (const point &a,const double &b)
    {return point(a.x*b,a.y*b);}
    inline friend double operator * (const point &a,const point &b)
    {return a.x*b.x+a.y*b.y;}
    inline friend double operator ^ (const point &a,const point &b)
    {return a.x*b.y-a.y*b.x;}
    inline friend bool operator < (const point &a,const point &b)
    {return a.x-b.x<-eps||(abs(a.x-b.x)<eps&&a.y-b.y<-eps);}
    inline friend bool operator == (const point &a,const point &b)
    {return abs(a.x-b.x)<eps&&abs(a.y-b.y)<eps;}
    inline double len(){return sqrt(x*x+y*y);}
    inline point unit(){double d=len();return point(x/d,y/d);}
    inline double ang(){return atan2(y,x);}
};
struct line
{
    point st,ed,v;
}l[N];
vector<point>p;
vector<double>ans;
int n,tot=-1,first[M],to[M],nxt[M],nxte[M];
bool vis[M];
// void add {
    point get_inter(line a,line b)
    {
        double s1=b.v^(a.st-b.st);
        double s2=((a.ed-b.st)^b.v)+s1;
        return a.st+a.v*(s1/s2);
    }

    int get_id(const point &a)
    {
        return lower_bound(p.begin(),p.end(),a)-p.begin();
    }

    void add(int x,int y)
    {
        nxt[++tot]=first[x],first[x]=tot,to[tot]=y;
    }
// }
void Init()
{
    memset(first,-1,sizeof(first));
    memset(nxte,-1,sizeof(nxte));
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%lf%lf%lf%lf",&l[i].st.x,&l[i].st.y,&l[i].ed.x,&l[i].ed.y);
        l[i].v=(l[i].ed-l[i].st);
    }
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(abs(l[i].v^l[j].v)>eps)
                p.push_back(get_inter(l[i],l[j]));
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    for(int i=0;i<n;i++)
    {
        vector<double>dis;
        point d=l[i].v.unit();
        for(int j=0;j<n;j++)
            if(abs(l[i].v^l[j].v)>eps)
            {
                point inter=get_inter(l[i],l[j]);
                dis.push_back((inter-l[i].st)*d);
            }
        sort(dis.begin(),dis.end());
        dis.erase(unique(dis.begin(),dis.end()),dis.end());
        for(int j=1,sz=dis.size();j<sz;j++)
        {
            int a=get_id(l[i].st+d*dis[j]);
            int b=get_id(l[i].st+d*dis[j-1]);
            add(a,b),add(b,a);
        }
    }
    for(int i=0,sz=p.size();i<sz;i++)
    {
        vector<pair<double,int> >P;
        for(int e=first[i];e!=-1;e=nxt[e])
            P.push_back(make_pair((p[to[e]]-p[i]).ang(),e));
        sort(P.begin(),P.end());
        for(int j=0,sz=P.size();j<sz;j++)
            nxte[P[(j+1)%sz].second^1]=P[j].second;
    }
}

void work()
{
    for(int i=0;i<=tot;i++)
    {
        if(vis[i])continue;
        stack<int>s;
        s.push(i),vis[i]=true;
        int j=nxte[i];
        while(!vis[j])
        {
            if(!s.empty()&&(s.top()^1)==j)s.pop();
            else s.push(j);
            vis[j]=true;
            j=nxte[j];
            if(j==-1)break;
        }
        if(i==j)
        {
            double area=0;
            while(!s.empty())
            {
                area+=(p[to[s.top()^1]]^p[to[s.top()]]);
                s.pop();
            }
            area*=0.5;
            if(area>0)ans.push_back(area);
        }
    }
}

int main()
{
    //freopen("lx.in","r",stdin);
    Init();
    work();
    printf("%d\n", ans.size());
    sort(ans.begin(), ans.end());
    for(int i=0,sz=ans.size();i<sz;++i)
        printf("%.4lf\n",ans[i]);
    return 0;
}