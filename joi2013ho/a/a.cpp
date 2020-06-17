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

// Run Length Encoding
// e.g. issii -> (i1)(s2)(i2)
vector<pair<int, ll>> run_length(const vector<ll>& s) {
  ll n = s.size();
  vector<pair<int, ll>> res;
  rep(i, n) {
    ll cnt = 1;
    while (i < n - 1 && s[i] == s[i+1]) {
      ++cnt;
      ++i;
    }
    res.emplace_back(s[i], cnt);
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  vector<ll> b(n-1);
  rep(i,n-1) {
    b[i] = (a[i]!=a[i+1]);
  }

  vector<pair<int, ll>> ps = run_length(b);
  ll m = ps.size();

  // For Debug
  // printvec(b);
  // rep(i,m) {
  //   cout << "(" << ps[i].first << "," << ps[i].second << ")" << endl;
  // }

  ll ans = min((ll)b.size(),2ll); // We can make 2 in worst case. We conside this for the case when there is no 1 in b.
  rep(i,m) {
    if (ps[i].first == 0) { continue; } // skip 0

    // case 1. try prev and latter
    {
      // Here, ps[i].first == 1
      ll now = ps[i].second;
      if (i>0) {
        ++now; // add contribution from i-1
        if (ps[i-1].second == 1 && i-2 >= 0) { // only 1. we can add.
          now += ps[i-2].second;
        }
      }
      if (i<m-1) {
        ++now; // add contribution from i+1
        if (ps[i+1].second == 1 && i+2 < m) {
          now += ps[i+2].second;
        }
      }

      chmax(ans,now);
    }

    // case 2. try prev
    {
      ll now = ps[i].second;
      if (i>0 && ps[i-1].second >= 2) {
        chmax(ans,now+2); // add 2 as prev
        if (ps[i-1].second == 2 && i-2 >= 0) {
          chmax(ans,now+2+ps[i-2].second);
        }
      }
    }

    // case 3. try latter
    {
      ll now = ps[i].second;
      if (i<m-1 && ps[i+1].second >= 2) {
        chmax(ans,now+2); // add 2 as latter
        if (ps[i+1].second == 2 && i+2 < m) {
          chmax(ans,now+2+ps[i+2].second);
        }
      }
    }
  }
  cout << ans+1 << endl;
}
