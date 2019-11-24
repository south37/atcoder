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
  string s;
  cin >> s;

  vector<P> valid_indices;

  vector<P> dp(n+1, mp(-1, -1)); // contains the (count, prev_distance)
  ll largest_cnt = -1;
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '1') {
      dp[i] = mp(-1, -1);
      continue;
    }
    // Now, s[i] == '0'
    if (i <= m) {
      dp[i] = mp(1, i);
      valid_indices.emplace_back(i, 1);
      continue;
    }

    // Now, i > m.
    // We want to find i-m <= "j in d" <= i.

    auto iter = lower_bound(all(valid_indices), mp((ll)(i-m), -1LL));
    if (iter == valid_indices.end()) {
      cout << -1 << endl;
      return 0;
    }
    ll id = (*iter).fr;
    ll cnt = (*iter).sc;
    dp[i] = mp(cnt+1, i - id);
    valid_indices.emplace_back(i, cnt+1);
  }

  // Now, dp[n] contains the result.
  if (dp[n] == mp(-1LL, -1LL)) {
    cout << -1 << endl;
    return 0;
  }

  vector<ll> ans;
  ll i = n;
  P cur = dp[n];
  rep(iter, dp[n].fr) {
    ans.push_back(cur.sc);
    i -= cur.sc;
    cur = dp[i];
  }
  reverse(all(ans));

  rep(j, ans.size()) {
    cout << ans[j] << ((j == ans.size() - 1) ? '\n' : ' ');
  }
}
