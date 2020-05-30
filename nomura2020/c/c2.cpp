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

const ll INF = 1e16;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> a(n+1);
  rep(i,n+1) {
    cin >> a[i];
  }
  if (a[0] >= 2) {
    cout << -1 << endl;
    return 0;
  }
  assert(a[0] <= 1);

  vector<ll> maxNodes(n+1);
  maxNodes[0] = 1-a[0];
  for (int i = 1; i <= n; ++i) {
    maxNodes[i] = 2*maxNodes[i-1] - a[i];
    chmin(maxNodes[i], INF); // for avoiding overflow
  }
  // printvec(maxNodes);

  ll ans = 0; // TODO: update

  ll cnt = a[n]; // node + leaf
  ans += cnt;
  for (ll i = n-1; i >= 0; --i) {
    // node must be in [minNode,cnt]
    ll minNode = (cnt+1)/2;

    ll node = min(cnt, maxNodes[i]); // initial value
    ll leaf = a[i];

    // // TODO: update logic of all
    // ll all = pow(2,i);
    // // ll all = 1;
    // // {
    // //   ll j = 0;
    // //   while (j < i && all < node + leaf) { // all-leaf < node
    // //     all *= 2;
    // //     ++j;
    // //   }
    // // }
    // cout << "cnt: " << cnt << endl;
    // cout << "all: " << all << endl;
    // cout << "leaf: " << leaf << endl;
    // cout << "node: " << node << endl;
    // cout << "all-leaf: " << all-leaf << endl;
    // cout << "minNode: " << minNode << endl;

    // if (all < cnt + leaf) { // Here, all == 2^i
    //   chmin(node, all - leaf);
    //   // Here, node >=minNode. OK>
    // } else { // Here, all is large. node <= all - leaf
    //   // Do nothing
    // }

    if (node < minNode) { // check size of node. node is too small.
      cout << -1 << endl;
      return 0;
    }

    cnt = node + leaf; // update cnt
    ans += cnt;
  }

  cout << ans << endl;
}
