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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, a, b;
  cin >> n >> a >> b;
  ll diff = abs(a-b);
  if (a>b) { swap(a,b); }
  // Here, a<=b

  if (diff%2 == 1) {
    // Here, we battle in 1 or n
    // ll ans1 = max(abs(1-a),abs(1-b));
    // ll ans2 = max(abs(n-a),abs(n-b));

    // Here, we battle in middle
    ll ans3 = 0, ans4 = 0;
    {
      // go 1.
      ll _a = a, _b = b;
      ans3 += _a-1;
      _a -= ans3;
      _b -= ans3;
      assert(_a == 1);

      --_b;
      ++ans3;
      // Here, parity is same
      ans3 += (_b-1)/2;
    }
    {
      // go n.
      ll _a = a, _b = b;
      ans4 += n-_b;
      _a += ans4;
      _b += ans4;
      assert(_b == n);

      ++_a;
      ++ans4;
      // Here, parity is same
      ans4 += (n-_a)/2;
    }

    // cout << min(min(ans1, ans2),min(ans3,ans4)) << endl;
    cout << min(ans3,ans4) << endl;
  } else {
    cout << diff/2 << endl;
  }
}
