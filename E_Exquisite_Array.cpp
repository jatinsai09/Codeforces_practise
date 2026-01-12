#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define pll pair < ll, ll >
    #define finish goto finished;

#define MAX LLONG_MAX
#define MIN LLONG_MIN

#define next cout << "\n";
#define nl "\n"
#define sp " "
#define ff first;
#define ss second

#define mini(a) * min_element(begin(a), end(a));
#define maxi(a) * max_element(begin(a), end(a));

#define sorta(arr, n) sort(arr, arr + n)
#define sortd(arr, n) sort(arr, arr + n, greater < ll >)
#define sortva(v) sort(begin(v), end(v))
#define sortvd(v) sort(rbegin(v), rend(v))
#define coutvec(v) for (auto& it: v) cout << it << " ";
#define cinvec(v) for (auto& it: v) cin >> it;
#define setbitsof(x) __builtin_popcountll(x)

const int MOD = 1e9 + 7;
const int mod = 998244353;

const int N = 2e5 + 10;
vector < ll > fact(N), inv(N), primes;
vector < vector < ll > > pfac(N);

ll add(ll a, ll b, ll m = MOD) {
    return ((a % m) + (b % m) + m) % m;
};
ll sub(ll a, ll b, ll m = MOD) {
    return ((a % m) - (b % m) + m) % m;
};
ll mul(ll a, ll b, ll m = MOD) {
    return ((a % m) * (b % m)) % m;
};
ll modExp(ll a, ll e, ll m = MOD) {
    a %= m;
    ll r = 1;
    while (e) {
        if (e & 1) {
            r = mul(r, a, m);
        }
        a = mul(a, a, m);
        e >>= 1;
    }

    return r;
}
ll invf(ll a, ll m = MOD) {
    return modExp(a, m - 2, m);
}

void init() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] % MOD * i % MOD) % MOD;
    }
    for (int i = 0; i < N; i++) {
        inv[i] = modExp(fact[i], MOD - 2, MOD);
    }
}
ll nCr(ll n, ll r) {
    return (fact[n] % MOD * inv[n - r] % MOD * inv[r] % MOD) % MOD;
}

void find_pfac() {
    for (ll i = 2; i < N; i++) {
        if (!pfac[i].empty()) {
            continue;
        }
        primes.push_back(i);
        for (ll j = i; j < N; j += i) {
            pfac[j].push_back(i);
        }
    }
}

class DSU {
    public: vector < int > parent,
    size;
    DSU(int n) {
        parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y, ll& cur) {
        int px = find(x), py = find(y);

        if (px == py) {
            return false;
        }

        cur -= 1LL * size[px] * (size[px] + 1) / 2;
        cur -= 1LL * size[py] * (size[py] + 1) / 2;

        if (size[py] < size[px]) {
            parent[py] = px;
            size[px] += size[py];
            cur += 1LL * size[px] * (size[px] + 1) / 2;
        }
        else {
            parent[px] = py;
            size[py] += size[px];
            cur += 1LL * size[py] * (size[py] + 1) / 2;
        }
        return true;
    }
};

bool is_palindrome(const string & s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

struct pairHash {
    size_t operator()(const pair < ll, ll > & p) const noexcept {
        size_t h = p.first;
        h ^= (size_t) p.second + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2);
        return h;
    }
};

bool is_prime(ll x) {
    if (x <= 1) return false;
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

bool is_perfect(ll x) {
    if (x < 0) return false;
    ll sr = sqrt(x);
    return (sr * sr == x);
}

string dectobin(ll n) {
    string s = "";
    while (n > 0) {
        s += to_string(n % 2);
        n /= 2;
    }
    reverse(begin(s), end(s));
    return s;
}

int bintodec(const string & n) {
    ll dec_value = 0, base = 1, len = n.size() - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (n[i] == '1')
            dec_value += base;
        base *= 2;
    }
    return dec_value;
}

void solve() {

    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll tc = 1;
    cin >> tc;
    //init();
    //find_pfac();
    while (tc--) {
        //solve();
        ll n;
        cin >> n;
        vector<ll> a(n);
        cinvec(a);

        vector<vector<int>> pos(n);
        for(int i = 1; i < n; i++) {
            int d = abs(a[i] - a[i - 1]);
            pos[d].push_back(i);
        }

        DSU dsu(n);
        vector<ll> on(n) , res(n);
        ll cur = 0;

        for(int k = n - 1; k >= 1; k--) {
            for(auto& i : pos[k]) {
                on[i] = 1;
                dsu.size[i] = 1;
                cur += 1;

                if(i - 1 >= 1 && on[i - 1]) {
                    dsu.unite(i, i - 1, cur);
                }
                if(i + 1 < n && on[i + 1]) {
                    dsu.unite(i, i + 1, cur);
                }
            }
            res[k] = cur;
        }

        for(int k = 1; k < n; k++) {
            cout << res[k] << sp;
        }
        cout << nl;

        finished: ;
    }
}
