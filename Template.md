# Rainbow_auto 的模板

> powered by CTL 代码来自 acwing.com

## 火车头

```cpp
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
#include <queue>

#define fastread ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define endl "\n"

using namespace std;

int main ()
{
	fastread
	
	return 0;
}
```

## 基础算法

### 快速排序

```cpp
void QuickSort (int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int mid = (l + r) >> 1;

    int x = a[mid];
    int i = l - 1;
    int j = r + 1;
    while (i < j)
    {
        do i ++; while (a[i] < x);
        do j --; while (a[j] > x);
        if (i < j) swap (a[i], a[j]);
    }

    QuickSort (l, j);
    QuickSort (j + 1, r);
}
```

### 二分

#### 整数二分

```cpp
int bsearch1 (int x) // lower_bound (x)
{
    int l = 1, r = n;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int bsearch2 (int x) // upper_bound (x) - 1
{
    int l = 1, r = n;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (a[mid] <= x) l = mid;
        else r = mid - 1;
    }
}
```

#### 浮点数二分

```cpp
double eps = 1e-9;
double bsearch_double (double x) // 求x的三次方根
{
    double l = min (x, -x), r = max (x, -x);
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (mid * mid * mid > x) l = mid;
        else r = mid;
    }
    return l;
}
```

### 高精度

#### 加法 (高精度+高精度)

```cpp
vector<int> Add (vector<int> a, vector<int> b)
{
    if (a.size() < b.size())
    {
        swap (a, b);
    }

    vector<int> res;
    int t = 0;
    for (int i = 0; i < a.size(); i++)
    {
        t += a[i];
        if (i < b.size()) t += b[i];
        res.push_back (t % 10);
        t /= 10;
    }

    if (t) res.push_back(t);

    return res;
}
```

#### 减法 (高精度 - 高精度)

```cpp
bool operator < (vector<int> a, vector<int> b)
{
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i --)
    {
        if (a[i] != b[i])
        {
            return a[i] < b[i];
        }
    }
    return false; // a == b
}

vector<int> Sub(vector<int> a, vector<int> b)
{
    bool flag = false;
    if (a < b)
    {
        flag = true;
        swap (a, b);
    }

    vector<int> res;

    int t = 0;
    for (int i = 0; i < a.size(); i++)
    {
        t = a[i] - t;
        if (i < b.size()) t -= b[i];
        res.push_back((t + 10) % 10);
        if (t < 0)
        {
            t = 1;
        }
        else
        {
            t = 0;
        }
    }

    while (res.size() > 1 and res.back() == 0) res.pop_back ();
    if (flag)
    {
        res.push_back(-1); // 负数 -1
    }
    else
    {
        res.push_back(0); // 正数 0
    }
    return res;
}
```

#### 乘法 (高精度\*低精度)

```cpp
vector<int> mul (vector<int> a, int b)
{
    vector<int> res;
    int t = 0;
    for (int i = 0; i < a.size() or t; i ++)
    {
        if (i < a.size()) t += a[i] * b;
        res.push_back(t % 10);
        t /= 10;
    }
    while (res.size() > 1 and res.back() == 0) res.pop_back();
}

```

#### 除法 (高精度/低精度)

```cpp
vector<int> div (vector<int> a, int b, int& r)
{
    vector<int> res;
    r = 0;
    for (int i = 0; i < a.size(); i ++)
    {
        r = r * 10 + a[i];
        res.push_back (r / b);
        r %= b;
    }
    return res;
}
```

### 前缀和

#### 一维

```cpp
void init ()
{
    for (int i = 1; i <= n; i++)
    {
        s[i] = s[i - 1] + a[i];
    }
}

int sum (int l, int r)
{
    return s[r] - s[l - 1];
}
```

#### 二维

```cpp
int a[maxn][maxn];
int s[maxn][maxn];
int n;
inline void init ()
{
    for (int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= m; j++)
        {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
}

inline int sum (int x1, int y1, int x2, int y2)
{
    return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][x2 - 1];
}
```

### 差分

#### 一维差分

```cpp
inline void insert (int l, int r, int x)
{
    sub[l] += x;
    sub[r + 1] -= x;
}

inline void init ()
{
    for (int i = 1; i <= n; i++)
    {
        insert(i, i, a[i]);
    }
}

inline void build_sum ()
{
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + sub[i];
    }
}
```

#### 二维差分

```cpp
int d[maxn][maxn]; // 差分数组
int s[maxn][maxn]; // 前缀和数组

int a[maxn][maxn]; // 原数组

inline void insert (int x1, int y1, int x2, int y2, int x)
{
    d[x2 + 1][y2 + 1] += x;
    d[x2 + 1][y1] -= x;
    d[x1][y2 + 1] -= x;
    d[x1][y1] += x;
}

void init ()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            insert (i, j, i, j, a[i][j]);
        }
    }
}

void build_sum ()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + d[i][j];
        }
    }
}
```

### 双指针法

```cpp
inline void two_pointers ()
{
    for (int i = 0, j = 0; i < n; i++)
    {
        while (j < i and check (j, i))
        {
            j++;
        }

        // 具体逻辑
    }
}
```

### 位运算

```cpp
inline int lowbit(int x)
{
    return x & (-x);
}

inline int get_bit (int x, int k)
{
    return (x >> k) & 1;
}
```

### 离散化

```cpp
vector<int> all; // 所有需要离散化的数

inline void discretize ()
{
    sort (all.begin(), all.end());
    all.erase (unique (all.begin(), all.end()), all.end());
}

inline int find (int x) // 原来值为x, 对应值为find(x)
{
    int l = 0, r = all.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (all[mid] >= x) r = mid;
        else l = mid - 1;
    }
    return l + 1; // 下标从1开始则 + 1
}
```

### 区间合并

```cpp
typedef pair<int, int> PII;

int n;
vector<PII> ranges;

inline void merge (vector<PII>& segs)
{
    vector<PII> res;
    sort (segs.begin(), segs.end());

    int st = -2e9, ed = -2e9;
    for (auto seg : segs)
    {
        if (seg.first > ed)
        {
            if (st != -2e9) res.push_back ({st, ed});
            st = seg.first;
            ed = seg.second;
        }
        else
        {
            ed = max (ed, seg.second);
        }
    }
    if (st != -2e9) res.push_back ({st, ed});

    segs = res;
}

```

### KMP

```cpp
n = Reader::read();
for (int i = 1; i <= n; i++) cin >> p[i];

m = Reader::read();
for (int i = 1; i <= m; i++) cin >> s[i];

for (int i = 2, j = 0; i <= n; i++)
{
    while (j and p[j + 1] != p[i]) j = nxt[j];
    if (p[j + 1] == p[i]) j++;
    nxt[i] = j;
}

for (int i = 1, j = 0; i <= m; i++)
{
    while (j and p[j + 1] != s[i]) j = nxt[j];
    if (p[j + 1] == s[i]) j++;
    if (j == n)
    {
        cout << i - n << " ";
        j = nxt[j];
    }
}
```

## 基础数据结构

### 单调队列

```cpp
deque<int> q;
for (int i = 1; i <= n; i++)
{
    while (not q.empty() and i - q.back() > k) q.pop_back();
    while (not q.empty() and a[q.front()] >= a[i]) q.pop_front();
    q.push_front(i);
    if (i >= k)
    {
        cout << a[q.back()] << endl;
    }
}
```

### 单调栈

```cpp
stack<int> s;
for (int i = 1; i <= n; i++)
{
    while (not s.empty() and a[s.top()] >= a[i]) s.pop();
    if (s.empty()) cout << "-1 ";
    else cout << s.top() << " ";
    s.push(i);
}
```

### Trie 字典树

```cpp
const int maxn = 100005;
int trie[maxn][26];
int cnt[maxn];
int id;

inline void insert (string s)
{
    int now = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int ch = s[i] - 'a';
        if (not trie[now][ch])
        {
            id++;
            trie[now][ch] = id;
        }
        now = trie[now][ch];
    }
}

inline void query(string s)
{
    int now = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int ch = s[i] - 'a';
        if (not trie[now][ch])
        {
            return 0;
        }
        now = trie[now][ch];
    }
    return cnt[now];
}
```

### 并查集

```cpp
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

```

### 堆

```cpp
const int maxn = 1000010;
int n;

int h[maxn];
int ph[maxn]; // 第k个插入到点的位置
int hp[maxn]; // 第i个点是第几个插入的
int siz;

inline void heap_swap (int a, int b)
{
    swap (h[a], h[b]);
    swap (hp[a], hp[b]);
    swap (ph[hp[a]], ph[hp[b]]);
}

void up (int x)
{
    if (x / 2 > 0 and h[x] < h[x / 2])
    {
        heap_swap (x, x / 2);
        up (x / 2);
    }
}

void down (int x)
{
    int t = x;
    if (x * 2 <= siz and h[t] > h[x * 2]) t = x * 2;

    if (x * 2 + 1 <= siz and h[t] > h[x * 2 + 1]) t = x * 2 + 1;

    if (t != x)
    {
        heap_swap (x, t);
        down (t);
    }
}

```

## 图论

### 邻接表/链式前向星

```cpp
const int maxn = 1000010;
int to[maxn], pre[maxn], last[maxn];
int cnt;

inline void addEdge (int u, int v)
{
    cnt ++;
    to[cnt] = v;
    pre[cnt] = last[u];
    last[u] = cnt;
}
```

### 拓扑排序

```cpp
int ind[maxn];
vector<int> topsort ()
{
    vector<int> ans;
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (ind[i] == 0)
        {
            q.push(i);
        }
    }

    while (not q.empty())
    {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int i = last[u]; i; i = pre[i])
        {
            int v = to[i];
            in[v]--;
            if (in[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (ans.size() == n)
    {
        return ans;
    }
    else
    {
        return vector(1, -1);
    }
}
```

### 最短路

#### Dijkstra

```cpp
struct Node{
    int id;
    int dis;
    friend bool operator < (Node a, Node b)
    {
        return a.dis > b.dis; // priority_queue
    }
};

bool vis[maxn];
int dis[maxn];
bool dij (int s)
{
    memset (dis, 0x3f, sizeof (dis));
    memset (vis, 0, sizeof (vis));
    dis[s] = 0;
    priority_queue <Node> q;
    q.push (Node{s, dis[s]});

    while (not q.empty ())
    {
        int u = q.top().id; q.pop();
        if (vis[u]) continue;
        vis[u] = true;

        for (int i = last[u]; i ; i = pre[i])
        {
            int v = to[i];
            if (dis[v] > dis[u] + w[i])
            {
                dis[v] = dis[u] + w[i];
                q.push (Node{v, dis[v]});
            }
        }
    }

    if (dis[n] == 0x3f3f3f3f) return false;
    else return true;
}
```

#### SPFA 判断负环

```cpp
bool inq[maxn];
int dis[maxn];
int times[maxn];

bool SPFA (int s)
{
    memset (inq, 0, sizeof (inq));
    memset (dis, 0x3f, sizeof (dis));
    dis[s] = 0;
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        q.push (i);
        inq[i] = true;
    }

    while (not q.empty())
    {
        int u = q.front (); q.pop();
        inq[u] = false;

        for (int i = last[u]; i; i = pre[i])
        {
            int v = to[i];
            if (dis[v] > dis[u] + w[i])
            {
                dis[v] = dis[u] + w[i];
                times[v] = times[u] + 1;
                if (times[v] >= n)
                {
                    return true; // 产生负环
                }

                if (not inq[v])
                {
                    q.push (v);
                    inq[v] = true;
                }
            }
        }
    }
    return false; // 没有负环
}
```

### 匈牙利算法

```cpp

// 待补充

```

## 数论

### 试除法判素数

```cpp
bool is_prime (int x)
{
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    return true;
    }
}
```

### 分解质因数

```cpp
vector < pair<int,int> > prime_fact (int x)
{
    vector < pair<int,int> > res;
    for (int i = 2; i <= x / i; i++)
    {
        int s = 0;
        while (x % i == 0)
        {
            x /= i;
            s ++;
        }
        if (s > 0)
        {
            res.push_back ({i, s});
        }
    }
    if (x > 1)
    {
        res.push_back ({x, 1});
    }

    return res;
}
```

### 线性筛

```cpp
const int maxn = 10000005;
int primes[maxn], cnt;
int is_prime[maxn];

void get_prime (int n)
{
    for (int i = 2; i <= n; i++)
    {

    }
}
```

### 试除法求约数

```cpp

vector<int> get_divisors (int x)
{
    vector<int> res;
    for (int i = 1; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            res.push_back (i);
            if (i != x / i) res.push_back (x / i);
        }
    }
    sort (res.begin(), res.end());
    return res;
}

```

### 约数个数

$$ 任何一个约数 d 可以表示成 \prod \limits_{i = 1} ^ k p_i ^ {\beta_i} $$
$$ 每一个 \beta 都可以在0到\alpha_i中选择 $$
$$ ans = (\alpha_1 + 1 )(\alpha_2 + 1) ... (\alpha_n + 1) $$

```cpp
const int mod = 1e9 + 7;

unordered_map<int, int> h;
void prime_fact (int x)
{
    for (int i = 2; i <= x / i; i++)
    {
        while (x % i == 0)
        {
            h[i] ++;
            x /= i;
        }
    }   
    if (x > 1)
    {
        h[x] ++;
    } 
}

int main ()
{
    int n = Reader::read();

    while (n --) 
    {
        int x = Reader::read();
        prime_fact (x);
    }

    long long ans = 1;
    for (auto i : h) ans = ans * (i.second + 1) % mod;

    cout << ans << endl;

    return 0;
}
```

### 约数之和

```cpp
const int mod = 1e9 + 7;

unordered_map <int, int> h;
void prime_fact (int x)
{
    for (int i = 2; i <= x / i; i++)
    {
        while (x % i == 0)
        {
            h[i]++;
            x /= i;
        }
    }
    if (x > 1) h[x] ++;
}

int main ()
{
    int n = Reader::read();
    while (n --)
    {
        int x = Reader::read();
        
        prime_fact (x);
    }

    long long ans = 1;
    for (auto x : h)
    {
        long long t = 1;
        for (int i = 1; i <= x.second; i++)
        {
            t = (t * x.first + 1) % mod;
        }
        ans = (ans * t) % mod;
    }

    cout << ans << endl;

    return 0;
}
```

### gcd
```cpp
int gcd (int a, int b)
{
    return b ? gcd (b, a % b) : a;
}
```
> 小技巧：gcd 不用背 ctrl + 单击`__gcd`就可以看到stl algorithm 中的gcd实现 ~~不过gcd也挺好背的~~

### 欧拉函数

```cpp
int phi (int x)
{
    int res = x;
    for (int i = 2; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}
```

### 扩展欧几里得算法

```cpp
ll exgcd (ll a, ll b, ll& x, ll& y)
{
    if (not b)
    {
        x = 1, y = 0;
        return a;
    }    
    ll res = exgcd (b, a % b, y, x);
    y -= x * (a / b);
    return res;
}
```

### 中国剩余定理

```cpp
ll crt ()
{
    mul = 1;
    for (int i = 1; i <= n; i++) mul *= a[i];

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ll m = mul / a[i];
        ll mr = 0, y = 0;
        exgcd (m, a[i], mr, y);
        mr = mr < 0 ? mr + a[i] : mr;
        ans += b[i] * m * mr; 
    }
    return ans % mul;
}

```

### 扩展中国剩余定理

```cpp
typedef __int128 ll;
const int maxn = 100005;

struct Equation
{
	ll r, m;
	bool ok;
}eq[maxn];
int n;

namespace exCRT
{
	ll exgcd (ll a, ll b, ll& x, ll& y)
	{
		if (not b)
		{
			x = 1, y = 0;
			return a;
		}
		ll res = exgcd (b, a % b, y, x);
		y -= a / b * x;
		return res;
	}

	ll gcd (ll a, ll b)
	{
		if (not b) return a;
		else return gcd (b, a % b);
	}

	ll lcm (ll a, ll b)
	{
		return a * b / gcd (a, b);
	}

	Equation merge (Equation e1, Equation e2)
	{
		ll r1 = e1.r, m1 = e1.m;
		ll r2 = e2.r, m2 = e2.m;
		
		ll x, y;
		ll d = exgcd (m1, m2, x, y);
		
		ll c = r2 - r1;
		if (c % d != 0) return Equation{0, 0, false};
		
		ll t0 = x * c / d % (m2 / d);
		if (t0 < 0) t0 += m2 / d;
	
		ll em = lcm (m1, m2);
		ll er = (m1 * t0 + r1) % em;
		if (er < 0) er += em;
		return Equation{er, em, true};		
	}

	ll exCRT ()
	{
		Equation curr = eq[1];
		for (int i = 2; i <= n; i++)
		{
			curr = merge (curr, eq[i]);
			if (not curr.ok) return -1;
		}
		return curr.r % curr.m;
	}
}
```

### 高斯消元
```cpp
const double eps = 1e-6;
const int maxn = 105;

int n;
double a[maxn][maxn];

int gauss ()
{
	int r = 0;
	for (int c = 0; c < n; c ++)
	{
		int t = r;
		for (int i = r; i < n; i++)
		{
			if (fabs (a[i][c]) > fabs (a[t][c]))
			{
				t = i;
			}
		}
		
		if (fabs (a[t][c]) < eps) continue;
		
		for (int i = c; i < n + 1; i++) swap (a[t][i], a[r][i]);
		for (int i = n; i >= c; i--) a[r][i] /= a[r][c];
		for (int i = r + 1; i < n; i++)
		{
			if (fabs (a[i][c]) > eps)
			{
				for (int j = n; j >= c; j--)
				{
					a[i][j] -= a[r][j] * a[i][c];
				}
			}
		}
		
		r++;
	}
	
	if (r < n)
	{
		for (int i = r; i < n; i++)
		{
			if (fabs (a[i][n]) > eps)
			{
				return 1; // No solution
			}
		}
		return 2; // Infinite group solutions
	}
	
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			a[i][n] -= a[j][n] * a[i][j];
		}
	}
		
	return 3;
}
```