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

  ll n;
  cin >> n;
  vector<int> d(3);
  rep(i,3) { cin >> d[i]; }
  vector<P> q;
  rep(i,n) {
    string s;
    cin >> s;
    int a, b;
    if (s == "AB") { a = 0, b = 1; } // (0,1)
    if (s == "AC") { a = 0, b = 2; } // (0,2)
    if (s == "BC") { a = 1, b = 2; } // (1,2)
    q.emplace_back(a,b);
  }
  string ans;
  auto add = [&](int a, int b) { // b->a.
    ++d[a];
    --d[b];
    ans += 'A'+a;
  };
  q.emplace_back(0,1); // sentinel.

  rep(i,n) {
    int a = q[i].first;
    int b = q[i].second;
    if (!d[a] && !d[b]) { // invalid. both is 0.
      cout << "No" << endl;
      return 0;
    }
    if (!d[a]) {
      add(a,b);
    } else if (!d[b]) {
      add(b,a);
    } else {
      int na = q[i+1].first;
      int nb = q[i+1].second;
      if (a == na || a == nb) { // a is used in next tern.
        add(a,b);
      } else {
        add(b,a);
      }
    }
  }
  cout << "Yes" << endl;
  rep(i,n) {
    cout << ans[i] << endl;
  }
}
