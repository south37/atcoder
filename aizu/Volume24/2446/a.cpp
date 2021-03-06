// ref. http://compro.tsutajiro.com/archive/181015_incexc.pdf

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define sz(x) (ll)(x).size()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;
typedef vector<ll> vl;
typedef vector<P> vp;

const ll INF = (ll)2e18 + 5;
const ll MOD = 1000000007;  // 1e9 + 7

ll gcd(ll a, ll b) {
  if (a < b) { swap(a, b); }
  if (b == 0) { return a; }
  return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
  if (a/gcd(a,b) > INF / b) { // a*b/gcd(a,b) > INF. too large
    return INF;
  } else {
    return a / gcd(a,b) * b;
  }
}

// Mevius Transform.
// cf. http://compro.tsutajiro.com/archive/181015_incexc.pdf
// - dp.size() == 1ll<<n.
// - dp must be initialzed by g.
void MeviusTransform(vector<ll>& dp, ll n) {
  rep(i,n)rep(bit,1ll<<n) {
    if (bit>>i&1) {
      dp[bit] -= dp[bit^(1ll<<i)];
    }
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }
  vector<double> p(n);
  rep(i,n) {
    cin >> p[i];
    p[i] /= 100;
  }

  vector<ll> dp(1ll<<n);
  // initialzation
  rep(bit,1ll<<n) {
    if (bit == 0) { continue; } // Skip empty state bit.

    ll mul = 1; // lcm of all selected values.
    rep(i,n) {
      if (bit>>i&1) {
        mul = lcm(mul,a[i]);
      }
    }
    dp[bit] = m/mul; // count of intersection at bit state.
  }

  // Mevius Transform
  MeviusTransform(dp,n);

  // Calculate answer
  double ans = 0;
  rep(bit,1ll<<n) {
    double prob = 1.0; // probability of selected bit state.
    rep(i,n) {
      prob *= ((bit>>i&1) ? p[i] : 1-p[i]);
    }
    ans += prob * abs(dp[bit]);
  }
  cout << ans << endl;
}
