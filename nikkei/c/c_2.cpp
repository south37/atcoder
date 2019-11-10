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

  ll n;
  cin >> n;
  vector<P> a(n);
  vector<P> b(n);
  rep(i, n) {
    cin >> a[i].fr;
    a[i].sc = i;
  }
  rep(i, n) {
    cin >> b[i].fr;
    b[i].sc = i;
  }

  sort(all(a));
  sort(all(b));

  // Check the sorted state. In each i, a[i] <= b[i] must be satisfied.
  rep(i, n) {
    if (a[i].fr > b[i].fr) {
      cout << "No" << endl;
      return 0;
    }
  }

  // Check if the i exists in which a[i+1] <= b[i].
  for (ll i = 0; i + 1 < n; ++i) {
    if (a[i+1].fr <= b[i].fr) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  // Check the count of cycles. We treat the cycles as the connected components.
  vector<ll> p(n); // p[i] .. The parent of i.
  rep(i, n) {
    p[a[i].sc] = b[i].sc;
  }
  ll ans = 0; // The necessary count of swap.
  vector<bool> visited(n);
  rep(i, n) {
    if (visited[i]) { continue; }

    ll x = i;
    ll len = 0;
    do {
      visited[x] = true;
      x = p[x];
      ++len;
    } while (x != i);
    ans += len-1;
  }

  if (ans <= n-2) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
