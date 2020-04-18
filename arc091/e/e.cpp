// ref. https://img.atcoder.jp/arc091/editorial.pdf

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

  ll n, a, b;
  cin >> n >> a >> b;

  if (a+b-1 <= n && n <= a*b) { // ok
    vector<ll> ans;
    for (int i = b; i >= 1; --i) { ans.push_back(i); }

    ll cur = b+1; // current value
    // Here, we print additional numbers (max: b-1 numbers) in each step.
    ll remain = n-b-(a-1);
    rep(iter, a-1) {
      ll now = min(remain, b-1);
      remain -= now;
      for (int i = cur+now; i >= cur; --i) { ans.push_back(i); }
      cur += now + 1;
    }

    rep(i, n) {
      cout << ans[i];
      if (i < n-1) { cout << " "; }
    }
    cout << endl;
  } else {
    cout << -1 << endl;
  }
}
