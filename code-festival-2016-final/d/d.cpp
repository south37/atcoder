// ref. https://cf16-final.contest.atcoder.jp/data/other/cf16-final/editorial.pdf

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

  ll n, m;
  cin >> n >> m;
  vector<ll> x(n);
  ll maxX = 0;
  rep(i, n) {
    cin >> x[i];
    chmax(maxX, x[i]);
  }

  vector<ll> cnts(maxX + 1); // cnts[i] .. counts of i
  rep(i, n) {
    ++cnts[x[i]];
  }

  vector<vector<ll>> mp(m); // { x MOD m => <cnts> }
  rep(i, maxX + 1) {
    if (cnts[i] > 0) {
      mp[i%m].push_back(cnts[i]);
    }
  }

  // For Debug
  // rep(i, m) {
  //   cout << i << ": "; printvec(mp[i]);
  // }

  ll ans = 0;
  for (int i = 1; i < (m+1)/2; ++i) { // m=7 => (m+1)/2=4, m=8 => (m+1)/2=4
    auto& s = mp[i];
    auto& t = mp[m-i];
    ll s_sum = 0; for (ll cnt : s) { s_sum += cnt; }
    ll t_sum = 0; for (ll cnt : t) { t_sum += cnt; }

    if (t_sum > s_sum) {
      swap(t_sum, s_sum);
      swap(t, s);
    }
    // Here, t_sum <= s_sum
    ans += t_sum;
    ll s_remain = (s_sum - t_sum)/2; // we can make s_remain pairs in maximum case.
    sort(all(s)); reverse(all(s)); // s i decreasing order
    for (ll cnt : s) { // check each count in s
      ll now = min(cnt/2, s_remain); // we can make "now" pairs from cnt.
      s_remain -= now;
      ans += now;
    }
  }

  // check 0-case
  {
    ll s = 0; for (ll cnt : mp[0]) { s += cnt; }
    ans += s/2;
  }

  // check m/2-case
  if (m%2 == 0) {
    ll s = 0; for (ll cnt : mp[m/2]) { s += cnt; }
    ans += s/2;
  }

  cout << ans << endl;
}
