#include <bits/stdc++.h>
using namespace std;
class point
{
public:
    double x,y;

    point(){}
    point(double _x,double _y)
    {
        x=_x;
        y=_y;
    }

    void get()
    {
        RD(x,y);
    }

    point operator-(point a)
    {
        return point(x-a.x,y-a.y);
    }

    double operator*(point a)
    {
        return x*a.y-y*a.x;
    }

    double operator^(point a)
    {
        return x*a.x+y*a.y;
    }

    double getLen()
    {
        return sqrt(x*x+y*y);
    }

    double getAng(point a)
    {
        return atan2(*this*a,*this^a);
    }
};

int n,g[305][305],t[305];
point a[305];
double p[305][305],dis[305],r[305];

int DB(double x)
{
    if(x>1e-10) return 1;
    if(x<-1e-10) return -1;
    return 0;
}

void SPFA()
{
    queue<int> Q;
    int inq[305]={0},i,j,k;
    FOR0(i,n) Q.push(i),inq[i]=1;
    while(!Q.empty())
    {
        k=Q.front();
        Q.pop();

        inq[k]=0;
        FOR0(i,n) if(g[k][i]&&DB(dis[k]+p[k][i]-dis[i])<0)
        {
            dis[i]=dis[k]+p[k][i];
            if(inq[i]) continue;
            inq[i]=1;
            Q.push(i);
            if(++t[i]>n)
            {
                puts("NO");
                return;
            }
        }
    }
    puts("YES");
}

int main()
{
    RD(n);
    int i,j;
    FOR0(i,n+1) a[i].get(),RD(r[i]);
    FOR0(i,n) FOR0(j,n) if(i!=j)
    {
        if(DB(r[i]+r[j]+r[n]*2-(a[i]-a[j]).getLen())>0)
        {
            g[i][j]=1;
            p[i][j]=(a[i]-a[n]).getAng(a[j]-a[n]);
        }
    }
    SPFA();
    return 0;
}