#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

namespace Reader
{
    int read()
    {
        char c = getchar();
        int x = 0, flag = 1;
        while (not isdigit(c))
        {
            if (c == '-')
                flag = -1;
            c = getchar();
        }
        while (isdigit(c))
        {
            x = x * 10 + c - '0';
            c = getchar();
        }
        return x * flag;
    }
}


const int maxn = 100005;
int fa[maxn];

int n, m;

int find (int x)
{
    if (fa[x] != x)
    {
        return fa[x] = find (fa[x]);
    }
    return fa[x];
}

inline void init ()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }
}

int main()
{

    return 0;
}