// https://www.spoj.com/problems/COURAGE/

#include<bits/stdc++.h>
using namespace std;

#define gc getchar_unlocked
#define fo(u,k,n) for(u=k;u<=n;u++)
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define endl '\n'
#define ff first
#define ss second
#define sz(a) (ll)(a).size()
#define Min(v) *min_element(all(v))
#define Max(v) *max_element(all(v))
#define all(x) x.begin(), x.end()
#define allr(c) c.rbegin(),c.rend()
#define mem0(x) memset(x, 0, sizeof(x))
#define mem1(x) memset(x, -1, sizeof(x))
#define PI 3.1415926535897932384626
#define print(container) for (auto it : container) cout << it << " "; cout << endl;
//===============================================================================================================
typedef pair<ll, ll>              pll;
typedef vector<ll>                vl;
typedef vector<pll>               vpll;
typedef vector<vl>                vvl;
typedef map<ll, ll>               mll;
typedef map<ll, bool>             mlb;
typedef unordered_map<ll, ll>     umll;
//===============================================================================================================
void precision(ll a, ll k) {cout << fixed << setprecision(k) << a;}
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
void google(ll t) {cout << "Case #" << t << ": ";}
ll mod_mul(ll a, ll b) {a = a % (ll)(1e9 + 7); b = b % (ll)(1e9 + 7); return (((a * b) % (ll)(1e9 + 7)) + (ll)(1e9 + 7)) % (ll)(1e9 + 7);}
ll mod_add(ll a, ll b) {a = a % (ll)(1e9 + 7); b = b % (ll)(1e9 + 7); return (((a + b) % (ll)(1e9 + 7)) + (ll)(1e9 + 7)) % (ll)(1e9 + 7);}
ll pwr(ll a, ll b) {a %= (ll)(1e9 + 7); ll res = 1; while (b > 0) {if (b & 1) res = res * a % (ll)(1e9 + 7); a = a * a % (ll)(1e9 + 7); b >>= 1;} return res;}
vector<ll> sieve(ll n) {ll *arr = new ll[n + 1](); vector<ll> vect; for (ll u = 2; u <= n; u++)if (arr[u] == 0) {vect.push_back(u); for (ll j = u * u; j <= n; j += u)arr[j] = 1;} return vect;}
//=============================================DEBUG START=======================================================
template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) { return os << '{' << p.first << ", " << p.second << '}';}
template < class T, class = decay_t<decltype(*begin(declval<T>()))>, class = enable_if_t < !is_same<T, string>::value >> ostream & operator<<(ostream &os, const T &c) {
	os << '[';
	for (auto it = c.begin(); it != c.end(); ++it) os << &", "[2 * (it == c.begin())] << *it;
	return os << ']';
}
//support up to 5 args
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_0(_CALL, ...)
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...) _NTH_ARG(dummy, ##__VA_ARGS__, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0)(MACRO, ##__VA_ARGS__)
//Change output format here
#define out(x) #x " = " << x << "; "
#define dbg(...) cerr << "Line " << __LINE__ << ": " FOR_EACH_MACRO(out, __VA_ARGS__) << "\n"

#ifndef ONLINE_JUDGE
#define cerr cout  // if you want to print to stdout, uncomment this
#else
#define dbg(...)
#endif
//===============================================DEBUG END=======================================================
const ll mod = 1000000007ll;
const ll inf = 1e18;
//===============================================================================================================
ll u = 0, k = 0, j = 0, m = 0, n = 0, l = 0, c = 0;
const ll N = 1000005;
ll a[N];
vpll tree(4 * N);

void build(ll ind, ll l, ll r) {
	if (l > r) return;

	if (l == r) {
		ll k;
		cin >> k;
		tree[ind] = make_pair(k, k);
		return;
	}
	ll mid = (l + r) >> 1;

	build(2 * ind + 1, l, mid);
	build(2 * ind + 2, mid + 1, r);

	tree[ind].first = tree[2 * ind + 1].first + tree[2 * ind + 2].first;
	tree[ind].second = min(tree[2 * ind + 1].second, tree[2 * ind + 2].second);

}

void update(ll ind, ll l, ll r, ll i, ll val) {
	if (l > r || i > r || i < l) return;

	if (l == r) {
		tree[ind].first += val;
		tree[ind].second += val;
		return;
	}

	ll mid = (l + r) >> 1;
	update(2 * ind + 1, l, mid, i, val);
	update(2 * ind + 2, mid + 1, r, i, val);

	tree[ind].first = tree[2 * ind + 1].first + tree[2 * ind + 2].first;
	tree[ind].second = min(tree[2 * ind + 1].second, tree[2 * ind + 2].second);
}

pair<ll, ll> query(ll ind, ll l, ll r, ll ql, ll qr) {

	if (ql > r || qr < l) return {0, INT_MAX};

	if (ql <= l && qr >= r) return tree[ind];

	ll mid = (l + r) >> 1;

	auto left = query(2 * ind + 1, l, mid, ql, qr);
	auto right = query(2 * ind + 2, mid + 1, r, ql, qr);

	return {left.first + right.first, min(left.second, right.second)};
}

void solve() {
	ll q, n;
	cin >> n;
	build(0ll, 0ll, n - 1ll);
	cin >> q;
	while (q--) {
		string type;
		ll l, r;
		cin >> type >> l >> r;
		if (type == "COUNT") {
			auto it = query(0, 0, n - 1, l, r);
			cout << (it.first - it.second) << endl;
		}
		if (type == "EAT") {
			update(0, 0, n - 1, r, -l);
		}
		else if (type == "GROW") {
			update(0, 0, n - 1, r, l);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll t = 1;
	// cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

