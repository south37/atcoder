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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;

  vector<ll> ds; // prime factors of n
  {
    ll m = n;
    ll i = 2;
    while (i*i <= m) {
      if (m%i == 0) {
        ds.push_back(i);
        while (m%i == 0) { m /= i; }
      }
      ++i;
    }
    if (m>1) {
      ds.push_back(m);
    }
  }
  // printvec(ds);

  ll cnt = 0; // The count of not coprime number
  ll m = ds.size();
  rep(i,1<<m) {
    ll d = 1; // current number
    rep(j,m) {
      if (i&(1<<j)) {
        d *= ds[j];
      }
    }
    if (d == 1) { continue; }
    // cout << d << endl;

    if (__builtin_popcountll(i)%2 == 1) { // should plus
      cnt += n/d;
    } else { // should minus
      cnt -= n/d;
    }
  }

  ll ans = n - cnt;
  cout << ans << endl;
}
