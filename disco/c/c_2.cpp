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
  vector<string> s(h);
  rep(i, h) {
    cin >> s[i];
  }
  // Now, s[i][j] is the cell
  vector<vector<ll> > ans(h, vector<ll>(w, -1));

  vector< vector<ll> > straberies(h);
  ll strabery = 1;
  rep(i, h) {
    rep(j, w) {
      if (s[i][j] == '#') {
        straberies[i].push_back(strabery);
        strabery = min(k, strabery + 1);
      }
    }
  }

  rep(i, h) {
    if (straberies[i].size() == 0) {
      // We set this value later.

      // if (i == 0) { continue; } // Treat later.

      // rep(j, w) {
      //   ans[i][j] = ans[i-1][j]; // Same with prev.
      // }
    } else { // straberies[i].size() >= 1
      ll ss = straberies[i][0];
      ll last_s = straberies[i][straberies[i].size()-1];
      rep(j, w) {
        if (s[i][j] == '#') { // s found
          ans[i][j] = ss;
          ss = min(last_s, ss + 1); // Set next strabery
        } else {
          ans[i][j] = ss;
        }
      }
    }
  }

  // We set -1
  rep(i, h) {
    rep(j, w) {
      if (ans[i][j] == -1) { // not defined.
        if (i >= 1) {
          ans[i][j] = ans[i-1][j];
        }
      }
    }
  }
  for (int i = h - 1; i >= 0; --i) {
    rep(j, w) {
      if (ans[i][j] == -1) { // not defined.
        if (i+1 <= h-1) {
          ans[i][j] = ans[i+1][j];
        }
      }
    }
  }

  // TODO(set i = 0 and cnts[0] = 0 case.)
  // if ((straberies[0].size() == 0) && (h >= 2)) {
  //   rep(j, w) {
  //     ans[0][j] = ans[1][j];
  //   }
  // }

  rep(i, h) {
    rep(j, w) {
      cout << ans[i][j];
      if (j != w-1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}
