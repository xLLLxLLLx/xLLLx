const int N = 200000;
int nxt[N][30], par[N], len[N], tot;
int append(int p, int c)
{
    if (nxt[p][c] && len[nxt[p][c]] == len[p] + 1) return nxt[p][c];
    int np = ++ tot, f = nxt[p][c]; len[np] = len[p] + 1;
    while (p && !nxt[p][c]) nxt[p][c] = np, p = par[p];
    if (!p) par[np] = 1;
    else
    {
        int q = nxt[p][c];
        if (len[q] == len[p] + 1) par[np] = q;
        else
        {
            int nq = f ? np : ++ tot;
            len[nq] = len[p] + 1;
            memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
            par[nq] = par[q]; par[q] = nq; if (!f) par[np] = nq;
            while (p && nxt[p][c] == q) nxt[p][c] = nq, p = par[p];
        }
    }
    return np;
}

SAM