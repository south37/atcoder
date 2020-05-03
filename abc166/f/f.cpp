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

  ll n, a, b, c;
  cin >> n >> a >> b >> c;
  if (a+b+c == 0) {
    cout << "No" << endl;
    return 0;
  }
  vector<string> ops(n);
  rep(i,n) {
    cin >> ops[i];
  }

  vector<char> ans;
  rep(i,n) {
    string& s = ops[i];

    if (s == "AB") {
      if (a == 0 && b == 0) {
        cout << "No" << endl;
        return 0;
      }

      if (a == 0) {
        ++a; --b;
        ans.push_back('A');
      } else if (b == 0) {
        --a; ++b;
        ans.push_back('B');
      } else { // a > 0 && b > 0
        if (a == 1 && b == 1 && c == 0 && i < n-1 && ops[i] != ops[i+1]) {
          if (ops[i+1] == "BC") { // use b
            --a; ++b;
            ans.push_back('B');
          } else { // "AC". use a
            ++a; --b;
            ans.push_back('A');
          }
        } else { // Here, either one is selectable.
          ++a; --b;
          ans.push_back('A');
        }
      }
    } else if (s == "BC") {
      if (b == 0 && c == 0) {
        cout << "No" << endl;
        return 0;
      }

      if (b == 0) {
        ++b; --c;
        ans.push_back('B');
      } else if (c == 0) {
        --b; ++c;
        ans.push_back('C');
      } else { // b > 0 && c > 0
        if (a == 0 && b == 1 && c == 1 && i < n-1 && ops[i] != ops[i+1]) {
          if (ops[i+1] == "AC") { // use c
            --b; ++c;
            ans.push_back('C');
          } else { // "AB". use a
            ++b; --c;
            ans.push_back('B');
          }
        } else { // Here, either one is selectable.
          ++b; --c;
          ans.push_back('B');
        }
      }
    } else { // s == "AC"
      if (c == 0 && a == 0) {
        cout << "No" << endl;
        return 0;
      }

      if (c == 0) {
        --a; ++c;
        ans.push_back('C');
      } else if (a == 0) {
        ++a; --c;
        ans.push_back('A');
      } else { // a > 0 && c > 0
        if (a == 1 && b == 0 && c == 1 && i < n-1 && ops[i] != ops[i+1]) {
          if (ops[i+1] == "AB") { // use a
            ++a; --c;
            ans.push_back('A');
          } else { // "BC". use c
            --a; ++c;
            ans.push_back('C');
          }
        } else { // Here, either one is selectable.
          --a; ++c;
          ans.push_back('C');
        }
      }
    }

    // cout << a << "," << b << "," << c << endl;
  }
  cout << "Yes" << endl;
  rep(i,n) {
    cout << ans[i] << endl;
  }
}
