class Graph
{
private:
    int cnt;
    int Head[maxN];
    int Next[maxM];
    int W[maxM];
    int V[maxM];
    int Depth[maxN];
    int cur[maxN];
public:
    int s,t;
    void init()
        {
            cnt=-1;
            memset(Head,-1,sizeof(Head));
            memset(Next,-1,sizeof(Next));
        }
    void _Add(int u,int v,int w)
        {
            cnt++;
            Next[cnt]=Head[u];
            Head[u]=cnt;
            V[cnt]=v;
            W[cnt]=w;
        }
    void Add_Edge(int u,int v,int w)
        {
            _Add(u,v,w);
            _Add(v,u,0);
        }
    int dfs(int u,int flow)
        {
            if (u==t)
                return flow;
            for (int& i=cur[u];i!=-1;i=Next[i])
            {
                if ((Depth[V[i]]==Depth[u]+1)&&(W[i]!=0))
                {
                    int di=dfs(V[i],min(flow,W[i]));
                    if (di>0)
                    {
                        W[i]-=di;
                        W[i^1]+=di;
                        return di;
                    }
                }
            }
            return 0;
        }
    int bfs()
        {
            queue<int> Q;
            while (!Q.empty())
                Q.pop();
            memset(Depth,0,sizeof(Depth));
            Depth[s]=1;
            Q.push(s);
            do
            {
                int u=Q.front();
                Q.pop();
                for (int i=Head[u];i!=-1;i=Next[i])
                    if ((Depth[V[i]]==0)&&(W[i]>0))
                    {
                        Depth[V[i]]=Depth[u]+1;
                        Q.push(V[i]);
                    }
            }
            while (!Q.empty());
            if (Depth[t]>0)
                return 1;
            return 0;
        }
    int Dinic()
        {
            int Ans=0;
            while (bfs())
            {
                for (int i=1;i<=n;i++)
                    cur[i]=Head[i];
                while (int d=dfs(s,inf))
                {
                    Ans+=d;
                }
            }
            return Ans;
        }
};
