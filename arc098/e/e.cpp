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
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k, q;
  cin >> n >> k >> q;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  ll ans = INF;
  rep(i, n) {
    // Here, a[i] is min
    vector<ll> small; // small emenents in each region

    ll pre = -1; // prev one.
    ll j = 0;
    while (j < n) {
      while (j < n && a[j] >= a[i]) { ++j; }
      // Here, j == n or a[j] < a[i]
      vector<ll> now; // elements in this region
      for (int k = pre + 1; k < j; ++k) {
        now.push_back(a[k]);
      }
      ll cnt = now.size()-k+1; // maximum trial in this region
      if (cnt > 0) {
        sort(all(now));
        rep(k, cnt) {
          small.push_back(now[k]);
        }
      }
      pre = j;
      ++j;
    }

    if (small.size() < q) { continue; } // inavalid
    sort(all(small));
    ans = min(ans, small[q-1] - a[i]);
  }

  cout << ans << endl;
}
