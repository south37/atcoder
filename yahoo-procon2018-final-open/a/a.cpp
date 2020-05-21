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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

const ll MAX_M = 100005;

vector<ll> primes(ll x) {
  vector<ll> ret;
  ll i = 2;
  while (i*i <= x) {
    if (x%i == 0) {
      ret.push_back(i);
      while (x%i == 0) { x/=i; }
    }
    ++i;
  }
  if (x > 1) {
    ret.push_back(x);
  }
  return ret;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,m;
  cin >> n >> m;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  // cnt[i] .. count of numbers which has i as factor.
  vector<ll> cnt(MAX_M);
  rep(i,n) {
    ll x = a[i];
    vector<ll> ds = primes(x);
    // printvec(ds);
    ll k = ds.size();
    rep(i,1ll<<k) {
      ll now = 1; // factor
      rep(j,k) {
        if (i>>j&1) { now *= ds[j]; }
      }
      if (now > 1) {
        ++cnt[now];
      }
    }
  }
  // printvec(cnt);

  for (ll i = 1; i <= m; ++i) {
    ll ans = n; // count of not coprime

    vector<ll> ds = primes(i);
    ll k = ds.size();
    rep(i,1ll<<k) {
      ll now = 1; // factor
      rep(j,k) {
        if (i>>j&1) { now *= ds[j]; }
      }
      if (now == 1) { continue; }

      if (__builtin_popcountll(i)%2 == 0) { // even. plus
        ans += cnt[now];
      } else { // odd. minus
        ans -= cnt[now];
      }
    }

    cout << ans << endl;
  }
}
