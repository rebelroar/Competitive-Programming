//  rebel_roar
//
//
//                                    =====                =====
//                                  ===    ====        ====    ===
//                                 ==         ===    ===         ==
//                                 ==            ====            ==
//                                 ==            ====            ==
//                                 ==          ==    ==          ==
//                                 ==        ===      ===        ==
//                                  ==  ======================  ==
//                               ======    ===          ===    ======
//                           ===    ==    ==              ==    ==    ===
//                        ===        == ===      ====      === ==       ===
//                       ==           ====     ========     ====          ==
//                      ==            ===     ==========     ===           ==
//                       ==           ====     ========     ====          ==
//                        ===        == ===      ====      === ==       ===
//                           ===    ==    ==              ==    ==    ===
//                               ======    ===          ===    ======
//                                  ==  ======================  ==
//                                 ==        ===      ===        ==
//                                 ==          ==    ==          ==
//                                 ==            ====            ==
//                                 ==            ====            ==
//                                 ==         ===    ===         ==
//                                  ===    ====        ====    ===
//                                    =====                =====

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

const ll N = 100005;
vector<ll> lazy(4 * N, 0);
vector<ll> tree(4 * N, 0);

void updateRangeLazy(ll ind, ll l, ll r, ll ql, ll qr, ll inc) {
	if (lazy[ind] != 0) {
		tree[ind] += (r - l + 1) * lazy[ind];
		if (l != r) {
			lazy[2 * ind + 1] += lazy[ind];
			lazy[2 * ind + 2] += lazy[ind];

		}
		lazy[ind] = 0;
	}
	if (l > r || r < ql || qr < l) return;
	if (l >= ql && qr >= r) {
		tree[ind] += (r - l + 1) * inc;

		if (l != r) {
			lazy[2 * ind + 1] += inc;
			lazy[2 * ind + 2] += inc;
		}
		return;
	}
	ll mid = (l + r) >> 1;
	updateRangeLazy(2 * ind + 1, l, mid, ql, qr, inc);
	updateRangeLazy(2 * ind + 2, mid + 1, r, ql, qr, inc);

	tree[ind] = (tree[2 * ind + 1] + tree[2 * ind + 2]);
}

ll query(ll ind, ll l, ll r, ll ql, ll qr) {
	if (lazy[ind] != 0) {
		tree[ind] += (r - l + 1) * lazy[ind];
		if (l != r) {
			lazy[2 * ind + 1] += lazy[ind];
			lazy[2 * ind + 2] += lazy[ind];

		}
		lazy[ind] = 0;
	}
	if (l > qr or r < ql) return 0;

	if (l >= ql && r <= qr) return tree[ind];

	ll mid = (l + r) >> 1;
	ll left = query(2 * ind + 1, l, mid, ql, qr);
	ll right = query(2 * ind + 2, mid + 1, r, ql, qr);
	return (left + right);
}

// void build_tree(vector<int> &tree, int tree_ind, int ss, int se, vector<int> a) {
// 	if (ss == se) {
// 		tree[tree_ind] = a[ss];
// 		return;
// 	}
// 	int mid = (ss + se) >> 1;
// 	build_tree(tree, 2 * tree_ind + 1, ss, mid, a);
// 	build_tree(tree, 2 * tree_ind + 2, mid + 1, se, a);
// 	tree[tree_ind] = min(tree[2 * tree_ind + 1], tree[2 * tree_ind + 2]);
// 	return;
// }

void solve() {
	ll n, q;
	cin >> n >> q;
	while (q--) {
		ll type, l, r, val;
		cin >> type;
		if (type == 0) {
			cin >> l >> r >> val;
			updateRangeLazy(0, 0, n - 1, l - 1, r - 1, val);
		}
		else {
			cin >> l >> r;
			cout << query(0, 0, n - 1, l - 1, r - 1) << endl;
		}
		// fo(u, 0, 10)cout << tree[u] << " ";
		// cout << endl;
		// fo(u, 0, 10)cout << lazy[u] << " ";
		// cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

