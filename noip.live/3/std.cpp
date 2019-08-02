#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
const int MAXN = 1100;
int a[MAXN];
int b[MAXN];
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    int n;
    while (cin >> n && n)
    {
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++)
            cin >> b[i];
        sort(a, a + n, cmp);
        sort(b, b + n, cmp);
        int sj = 0, ej = n-1;
        int sw = 0, ew = n-1;
        int win = 0;
        while(sj <= ej && sw <= ew)
        {
            if (a[sj] > b[sw])
            {
                win++;
                sj++, sw++;
            }
            else if (a[sj] < b[sw]){
                win--;
                ej--, sw++;
            } 
            else 
            { // 当两者最快的马相等时    
                if (a[ej] > b[ew]){
                    win++;
                    ej--, ew--;
                } 
                else if (a[ej] < b[ew]) {
                    win--;
                    ej--, sw++;
                }
                else {
                    if (a[ej] < b[sw])
                        win--;
                    ej--, sw++;
                }
            }
        }
        cout << win*200 << endl;
    }
    return 0;
}