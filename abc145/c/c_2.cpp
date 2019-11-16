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

vector< vector<double >> dist; // Tree which contains the distance of i-j.

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<double> x(n);
  vector<double> y(n);
  rep(i, n) {
    cin >> x[i];
    cin >> y[i];
  }
  // printvec(x);
  // printvec(y);

  dist.assign(n, vector<double>(n)); // Tree which contains the distance of i-j.
  rep(i, n) {
    for (int j = i + 1; j < n; ++j) {
      double d = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
      dist[i][j] = d;
      dist[j][i] = d;
    }
  }

  vector<ll> a(n);
  rep(i, n) { a[i] = i; }

  double ans = 0;
  do {
    rep(i, n-1) {
      ans += dist[a[i]][a[i+1]];
    }
  } while (next_permutation(all(a)));

  ll divisor = 1;
  rep(i, n) {
    divisor *= i + 1;
  }

  cout << (ans / (double)divisor) << endl;
}
