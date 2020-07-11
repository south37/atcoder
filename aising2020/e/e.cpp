#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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

void solve() {
  ll n;
  cin >> n;
  vector<ll> k(n), l(n), r(n);
  map<ll,vector<ll>> mp; // k => list of idx
  ll ans = 0;
  rep(i,n) {
    cin >> k[i] >> l[i] >> r[i];
    mp[k[i]].push_back(i);
    ll mn = min(l[i],r[i]);
    ans += mn;
    l[i] -= mn;
    r[i] -= mn;
  }

  // cout << "l: "; printvec(l);
  // cout << "r: "; printvec(r);
  // cout << "ans: " << ans << endl;
  // for (ll i = 1; i <= n; ++i) {
  //   cout << i << ": ";
  //   vector<ll>& indices = mp[i];
  //   for (ll idx : indices) {
  //     cout << idx << " ";
  //   }
  //   cout << endl;
  // }

  {
    priority_queue<ll, vector<ll>, greater<ll>> q;
    for (ll i = 1; i <= n; ++i) { // loop size
      vector<ll>& indices = mp[i];
      for (ll idx : indices) {
        if (l[idx] > 0) {
          q.emplace(l[idx]);
          ans += l[idx];
          // cout << "+l[idx]: " << l[idx] << endl;
        }
      }
      // Here, all values are added.

      // pop until q.size() <= i
      while (q.size() > i) {
        ll li = q.top(); q.pop();
        ans -= li;
        // cout << "-l[idx]: " << li << endl;
      }
    }
  }

  {
    priority_queue<ll, vector<ll>, greater<ll>> q;
    for (ll i = n; i >= 1; --i) { // loop size from right
      vector<ll>& indices = mp[i-1]; // boundary is (i-1)+1 == i
      for (ll idx : indices) {
        if (r[idx] > 0) {
          q.emplace(r[idx]);
          ans += r[idx];
          // cout << "+r[idx]: " << r[idx] << endl;
        }
      }
      // Here, all values are added.

      // pop until q.size() <= "n-i+1"
      while (q.size() > n-i+1) {
        ll ri = q.top(); q.pop();
        ans -= ri;
        // cout << "-r[idx]: " << ri << endl;
      }
    }
  }

  cout << ans << endl;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(iter,t) {
    solve();
  }
}
