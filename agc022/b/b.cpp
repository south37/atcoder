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

vector<ll> solve(const vector<ll>& a, int n) {
  vector<ll> ans;
  ll i = 0;
  ll j = 0;
  while (n) {
    ans.push_back(a[i] + 12*j);
    ++i;
    if (i == 8) {
      i = 0;
      ++j;
    }
    --n;
  }
  return ans;
}

const vector<ll> even = { 2, 10, 3, 9, 4, 8, 6, 12 };
const vector<ll> odd  = { 6, 2, 10, 3, 9, 4, 8, 12 };;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  if (n == 3) {
    cout << "2 5 63" << endl;
    return 0;
  }

  vector<ll> ans;
  // Here, n >= 4
  if (n % 2 == 1) { // odd
    ans = solve(odd, n);
  } else { // even
    ans = solve(even, n);
  }

  rep(i, n) {
    cout << ans[i];
    if (i < n-1) {
      cout << " ";
    }
  }
  cout << endl;
}
