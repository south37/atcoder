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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,w,c;
  cin >> n >> w >> c;
  vector<P> ls; // (l,id)
  vector<ll> rs(n);
  vector<ll> cs(n);
  rep(i,n) {
    ll l,r,p;
    cin >> l >> r >> p;
    ls.emplace_back(l,i);
    rs[i] = r;
    cs[i] = p;
  }
  ls.emplace_back(w,n); // last boarder
  sort(all(ls));

  // rep(i,n) {
  //   cout << ls[i].first << "," << ls[i].second << endl;
  // }
  // printvec(rs);
  // printvec(cs);

  ll ans = INF;
  ll now = 0; // current cost
  set<P> st; // (r,id). in C.
  rep(i,n+1) {
    auto p = ls[i];
    ll l = p.first;
    ll id = p.second;
    // Here, remove all left values in [0,l-c]
    while (!st.empty() && (*st.begin()).first <= l-c) {
      now -= cs[(*st.begin()).second];
      st.erase(st.begin());
    }
    assert(st.empty() || (l-c <= (*st.begin()).first));
    if (l-c >= 0) {
      // Here, values are remaining in (l-c,l)
      chmin(ans, now);
    }

    if (id == n) { break; } // end
    now += cs[id];
    st.emplace(rs[id],id);
  }
  cout << ans << endl;
}
