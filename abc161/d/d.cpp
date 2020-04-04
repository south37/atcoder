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

  ll k;
  cin >> k;
  if (k <= 9) {
    cout << k << endl;
    return 0;
  }

  ll ans = 10;
  rep(i, k-10) {
    // compare 2 digit.
    vector<ll> ds;
    ll now = ans;
    while (now > 0) {
      ds.push_back(now % 10);
      now /= 10;
    }
    // cout << "ds: "; printvec(ds);

    // Here, ds has the digis in reverse order
    bool updated = false;
    rep(i, ds.size()-1) {
      ll lastD = ds[i];
      ll preD = ds[i+1];
      if (preD == 9) { // consider 9 case
        if (lastD == 8) {
          ++ds[i]; // update lastD
          updated = true;
        }
      } else if (preD + 1 > lastD) {
        ++ds[i]; // update lastD
        ll cur = ds[i]-1;
        updated = true;
      }
      if (updated) {
        ll cur = ds[i]-1;
        for (int j = i-1; j >= 0; --j) {
          ds[j] = max(cur, 0ll);
          --cur;
        }
        break; // break repeat
      }
      // Here, continue
    }
    if (!updated) { // ds is decreasing order
      ll n = ds.size();
      ll lastD = ds[n-1]; // most significant digit
      if (lastD < 9) {
        ds[n-1] = lastD + 1;
        ll cur = lastD;
        for (int j = n-2; j >= 0; --j) {
          ds[j] = max(cur, 0ll);
          --cur;
        }
      } else { // 9
        // create 10...0
        ds = vector<ll>(n+1);
        ds[n] = 1;
      }
    }
    reverse(all(ds));

    // Here, we convert vector to number
    ll nex = 0;
    for (int digit : ds) {
      nex *= 10;
      nex += digit;
    }
    ans = nex;
  }

  cout << ans << endl;
}
