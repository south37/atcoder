// ref. https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_c

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

  ll w, h;
  cin >> w >> h;
  vector<P> edges; // pair of <cost, type>. 0 .. p, 1 .. q
  rep(i, w) {
    ll cost;
    cin >> cost;
    edges.emplace_back(cost, 0);
  }
  rep(i, h) {
    ll cost;
    cin >> cost;
    edges.emplace_back(cost, 1);
  }

  sort(all(edges));
  ll x = w+1; // remaining x
  ll y = h+1; // remaining y

  ll ans = 0;
  for (auto& p : edges) {
    ll cost = p.first;
    ll type = p.second;
    if (type == 0) { // type x
      ans += cost * y;
      --x;
    } else { // type y
      ans += cost * x;
      --y;
    }
  }
  cout << ans << endl;
}
