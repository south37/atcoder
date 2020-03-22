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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll h, w, k;
  cin >> h >> w >> k;
  vector<string> block(h);
  rep(i, h) {
    cin >> block[i];
  }

  // Here, we try all divisor in h. [0, h-1)
  // e.g. h = 3 <=> [0,1]
  ll ans = INF;
  rep(i, 1ll << (h-1)) {
    bool isInvalid = false; // becomes true when this i is invalid

    ll cand = 0;
    vector<ll> bnd; // contains the information of boundary
    rep(j, h-1) {
      if (i & (1ll<<j)) {
        bnd.push_back(j);
      }
    }
    cand += bnd.size();

    vector<ll> cnts(bnd.size() + 1); // counts in each region
    // Here, we calculate all case.
    rep(c, w) {
      // ll idx = 0;
      rep(r, h) {
        // if (bnd[idx]
        ll idx = upper_bound(all(bnd), r) - bnd.begin(); // idx of counts
        if (block[r][c] == '1') { // bound white
          ++cnts[idx];
        }
      }

      // Check the counts. if reached to bigger than k, we add boundary and re-add.
      bool reachToK = false;
      rep(r, h) {
        ll idx = upper_bound(all(bnd), r) - bnd.begin(); // idx of counts
        if (cnts[idx] > k) { // reached to k.
          reachToK = true;
          ++cand; // add boundary
          break;
        }
      }

      if (reachToK) { // reach to k
        cnts.assign(bnd.size() + 1, 0); // reset
        rep(r, h) { // set current
          ll idx = upper_bound(all(bnd), r) - bnd.begin(); // idx of counts
          if (block[r][c] == '1') { // bound white
            ++cnts[idx];
          }
          if (cnts[idx] > k) { // reach to k in one loop
            isInvalid = true;
          }
        }
      }
    }

    if (!isInvalid) {
      ans = max(ans, cand);
    }
  }

  cout << ans << endl;
}
