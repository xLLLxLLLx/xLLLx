const int N = 200010;
char st[N];
int rk[N], sa[N], nr[N], ns[N], tab[N], hi[N];
void calc(int n)
{
    for (int i = 0; i <= 26; ++ i) tab[i] = 0;
    for (int i = 1; i <= n; ++ i) tab[st[i] - 'a' + 1] = 1;
    for (int i = 1; i <= 26; ++ i) tab[i] += tab[i - 1];
    for (int i = 1; i <= n; ++ i) rk[i] = tab[st[i] - 'a' + 1];
    for (int p = 2; (p >> 1) <= n; p <<= 1)
    {
        for (int i = 0; i <= n; ++ i) tab[i] = 0;
        for (int i = 1; i <= n; ++ i) tab[rk[i + (p >> 1)]] ++;
        for (int i = 1; i <= n; ++ i) tab[i] += tab[i - 1];
        for (int i = n; i >= 1; -- i) ns[tab[rk[i + (p >> 1)]] --] = i;
        for (int i = 0; i <= n; ++ i) tab[i] = 0;
        for (int i = 1; i <= n; ++ i) tab[rk[i]] ++;
        for (int i = 1; i <= n; ++ i) tab[i] += tab[i - 1];
        for (int i = n; i >= 1; -- i) sa[tab[rk[ns[i]]] --] = ns[i];
        nr[sa[1]] = 1;
        for (int i = 2; i <= n; ++ i)
            if (rk[sa[i]] == rk[sa[i - 1]] && rk[sa[i] + (p >> 1)] == rk[sa[i - 1] + (p >> 1)])
                nr[sa[i]] = nr[sa[i - 1]];
            else
                nr[sa[i]] = nr[sa[i - 1]] + 1;
        for (int i = 1; i <= n; ++ i)
            rk[i] = nr[i];
        if (rk[sa[n]] == n) break;
    }
    for (int i = 1; i <= n; ++ i)
        if (rk[i] != 1)
        {
            hi[rk[i]] = max(hi[rk[i - 1]] - 1, 0);
            while (st[i + hi[rk[i]]] == st[sa[rk[i] - 1] + hi[rk[i]]])
                hi[rk[i]] ++;
        }
}

SA