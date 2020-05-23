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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<queue<ll>> qs(n); // i .. row i.
  rep(i,n) {
    ll k;
    cin >> k;
    rep(j,k) {
      ll t;
      cin >> t;
      qs[i].push(t);
    }
  }

  set<P> tops; // set of <value,idx>
  set<P> seconds; // set of <value,idx>
  map<ll,ll> topsMp; // { idx => value }
  map<ll,ll> secondsMp; // { idx => value }

  // pop v from qs[i] and set it to st and mp
  auto add = [&](set<P>& st, map<ll,ll>& mp, ll i) {
    ll v;
    if (qs[i].empty()) {
      v = 0;
    } else {
      v = qs[i].front(); qs[i].pop();
    }
    st.insert(P(v,i));
    mp[i] = v;
  };

  // setup tops
  rep(i,n) {
    add(tops, topsMp, i);
  }

  // setup seconds
  rep(i,n) {
    add(seconds, secondsMp, i);
  }

  // move idx from seconds to tops
  auto moveToTopFromSecond = [&](ll i) {
    ll v = secondsMp[i];
    auto it = seconds.find(P(v,i)); // pick from seconds
    seconds.erase(it);

    P p = *it; // picked from seconds
    tops.insert(p);
    topsMp[p.second] = p.first; // update mp

    add(seconds, secondsMp, i); // from queue to second
  };

  ll m;
  cin >> m;
  rep(iter,m) {
    ll a;
    cin >> a;
    if (a == 1) {
      // Here, we pick only from tops
      auto it = prev(tops.end()); // most largest

      cout << it->first << endl;
      ll idx = it->second;
      tops.erase(it);
      moveToTopFromSecond(idx);
    } else { // a == 2
      // Here, we pick from tops and seconds
      auto itTop = prev(tops.end()); // most largest
      auto itSecond = prev(seconds.end()); // most largest

      if (itTop->first > itSecond->first) { // top is largest
        cout << itTop->first << endl;
        ll idx = itTop->second;
        tops.erase(itTop);
        moveToTopFromSecond(idx);
      } else { // second id largest
        cout << itSecond->first << endl;
        ll idx = itSecond->second;
        seconds.erase(itSecond);
        add(seconds, secondsMp, idx); // move from queue to seconds
      }
    }
  }
}
