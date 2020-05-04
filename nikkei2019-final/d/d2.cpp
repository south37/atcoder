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

  ll n, m;
  cin >> n >> m;
  ll minL = INF;
  ll maxR = 0;
  ll maxT = 0;
  vector<triple> ts;
  rep(i,m) {
    ll t,l,r;
    cin >> t >> l >> r;
    ts.emplace_back(t,l,r);
    chmin(minL,l);
    chmax(maxR,r);
    chmax(maxT,t);
  }
  reverse(all(ts));

  set<ll> st;
  for (ll i = minL; i <= maxR; ++i) {
    st.insert(i);
  }

  vector<ll> lastT(maxR+1);
  rep(i,m) {
    ll t,l,r;
    tie(t,l,r) = ts[i];
    auto lit = st.lower_bound(l);
    auto rit = st.upper_bound(r);
    for (auto it = lit; it != rit; ++it) {
      lastT[*it] = t;
    }
    st.erase(lit, rit);
  }

  ll ans = maxT*(maxR+1-minL);
  for (ll i = minL; i <= maxR; ++i) {
    ans -= (maxT - lastT[i]);
  }
  cout << ans << endl;
}
