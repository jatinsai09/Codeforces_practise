#include <bits/stdc++.h>
using namespace std;

vector<int> g[200005];
int cnt[200005];
int groups;

void dfs(int v, int p)
{
    bool leaf = true;
    cnt[v] = 0;

    for(int u : g[v])
    {
        if(u == p) continue;
        leaf = false;
        dfs(u, v);
        cnt[v] += cnt[u];
    }

    if(leaf)
    {
        cnt[v] = 1;
    }

    if(v != 1 && cnt[v] % 3 == 0)
    {
        groups++;
        cnt[v] = 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        for(int i = 1; i <= n; i++)
        {
            g[i].clear();
        }

        for(int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        groups = 0;
        dfs(1, 0);

        if(cnt[1] == 0 && groups % 3 == 0)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}
