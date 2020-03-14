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

ll check_diff(string& a, string& b) {
  ll n = a.size();
  ll m = b.size();

  ll foundAt = -1;
  bool foundGlobal = false;

  rep(i, n) {
    // Here, try the check with a[i..n-1] and b[0..m-1]
    bool found = true;
    for (int j = i; 1; ++j) {
      if ((j == n) || (j-i == m)) { // reached to last
        break;
      }

      if (a[j] == '?') { // ok
        continue;
      }
      if (b[j-i] == '?') { // ok
        continue;
      }

      if (a[j] != b[j-i]) {
        found = false;
        break;
      }
    }
    if (found) {
      foundAt = i;
      foundGlobal = true;
      break;
    }
  }
  // Here, if foundGlobal is true, then foundAt == i.
  if (foundGlobal) {
    // Set value to '?'
    for (int j = foundAt; 1; ++j) {
      if ((j == n) || (j-foundAt == m)) { // reached to last
        break;
      }
      if (a[j] == '?' && b[j-foundAt] == '?') {
        continue;
      }
      if (a[j] == '?') { // ok
        a[j] = b[j-foundAt];
        continue;
      }
      if (b[j-foundAt] == '?') { // ok
        b[j-foundAt] = a[j];
        continue;
      }
      // Here, do nothing
    }
    return (n - foundAt);
  } else {
    return 0;
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  string a, b, c;
  cin >> a;
  cin >> b;
  cin >> c;

  ll totalSize = (a.size() + b.size() + c.size());
  ll ans = totalSize;
  vector<string> strs = { a, b, c };
  vector<ll> perm = { 0, 1, 2 };
  do {
    string aa = strs[perm[0]];
    string bb = strs[perm[1]];
    string cc = strs[perm[2]];

    // Try (aa,bb) and (bb,cc)
    string a1 = aa;
    string b1 = bb;
    string c1 = cc;
    ll ab1 = check_diff(a1, b1);
    ll bc1 = check_diff(b1, c1);
    ll candAns1 = totalSize - ab1 - bc1;
    ans = min(ans, candAns1);

    // Try (bb,cc) and (aa,bb)
    string a2 = aa;
    string b2 = bb;
    string c2 = cc;
    ll bc2 = check_diff(b2, c2);
    ll ab2 = check_diff(a2, b2);
    ll candAns2 = totalSize - ab2 - bc2;
    ans = min(ans, candAns2);
  } while (next_permutation(all(perm)));
  // At first, try (a, b, c)

  cout << ans << endl;
}
