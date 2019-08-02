const int MAXN = 10005;

int n, m, eve[MAXN], odd[MAXN];
vector <int> u, v, vec[MAXN];

inline bool Compare(int x, int y){
    char opt[3];
    printf("? %d %d\n", x, y);
    fflush(stdout);
    scanf("%s", opt);
    return opt[0] == '<';
}

inline void Seperate(int bel, int x){
    u.clear(), v.clear();
    for (auto y : vec[bel])
        if (Compare(y, x))
            u.pb(y);
        else
            v.pb(y);
}

inline int Insert(int x){
    for (int i = m; i > x; i --)
        vec[i + 1] = vec[i];
    vec[x] = u, vec[x + 1] = v, m ++;
    int ret = 0;
    for (int i = 1; i <= x; i ++)
        ret += vec[i].size();
    return ret * 2 + 1;
}

int main()
{
    n = Read(), m = 1;
    if (n == 1)
    {
        puts("! 1");
        fflush(stdout);
        return 0;
    }
    for (int i = 1; i <= n >> 1; i ++)
        vec[1].pb(i);
    for (int i = 1; i <= n + 1 >> 1; i ++)
    {
        int L = 1, R = m, ret = 0, cnt = 0;
        while (L <= R)
        {
            int mid = L + R >> 1;
            if (Compare(vec[mid][0], i))
                ret = mid, L = mid + 1;
            else
                R = mid - 1;
        }
        if (!ret)
        {
            Seperate(1, i);
            if (u.empty())
                odd[i] = 1;
            else if (v.empty())
                odd[i] = u.size() * 2 + 1;
            else
                odd[i] = Insert(1);
        }
        else
        {
            for (int i = 1; i < ret; i ++)
                cnt += vec[i].size();
            Seperate(ret, i);
            if (v.empty())
            {
                if (ret == m)
                    odd[i] = n;
                else
                {
                    cnt += vec[ret].size();
                    Seperate(ret + 1, i);
                    if (u.empty())
                        odd[i] = cnt * 2 + 1;
                    else
                        odd[i] = Insert(ret + 1);
                }
            }
            else
                odd[i] = Insert(ret);
        }
    }
    int cur = 0;
    for (int i = 1; i <= m; i ++)
        for (auto j : vec[i])
            cur ++, eve[j] = cur * 2;
    printf("!");
    for (int i = 1; i <= n >> 1; i ++)
        printf(" %d", eve[i]);
    for (int i = 1; i <= n + 1 >> 1; i ++)
        printf(" %d", odd[i]);
    putchar(10), fflush(stdout);
    return 0;
}