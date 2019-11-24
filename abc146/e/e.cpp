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

  ll n, k;
  cin >> n >> k;
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }

  rep(i, n) {
    a[i] = a[i] % k;
  }

  // Now, we start from the all position, in which i is less than
  // We want to find 0 and larger point.

  vector<ll> ones;
  rep(i, n) {
    if (a[i] == 1) {
      ones.push_back(i);
    }
  }

  vector<P> pairs; // (digit, count). count > 0 only when digit = 0.
  // vector<ll> zeros;
  rep(i, n) {
    ll zero_cnt = 0;
    ll j = i;
    while (j < n && a[j] == 0) { ++zero_cnt; }
    if (zero_cnt > 0) {
      pairs.emplace_back(0, zero_cnt);
    }
    if (j < n) {
      pairs.emplace_back(a[j], 1);
    }
    // Now, j is not zero
    i = j + 1;
  }

  vector<ll> oks; // The oks

  ll ans = 0;

  // Now, we have ones and pairs.
  ll sz = pairs.size();
  ll i = 0;
  while (i < sz) {
    ll continues = 0;

    ll j = i;
    while (j < sz) {
      if (pairs[j].fr == 1) {
        ++continues;
        ++j;
        continue;
      }

      ll zero_cnt = 0;
      if (j-1 >= 0 && pairs[j-1].fr == 0) {
        zero_cnt += pairs[j-1].sc;
      }
      if (j+1 < sz && pairs[j+1].fr == 0) {
        zero_cnt += pairs[j+1].sc;
      }
      // Now, we can use zero_cnt for pair[i].
      if (pairs[j].fr <=  zero_cnt) {
        ++continues;
      } else {
        break;
      }

      ++j;
    }

    if (continues >= 2) {
      ans += continues * (continues -1)/2;
    } else {
      ans += continues;
    }

    i = j +1;
  }

  cout << ans << endl;
}
