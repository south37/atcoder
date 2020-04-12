// ref. https://img.atcoder.jp/exawizards2019/editorial.pdf

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

int dir = 0;
ll n, q;
string s;
vector<pair<char, char>> spells; // pair of <t, d>

// Check the destination of x. Return true if x does not reach to -1.
bool check(ll x) {
  rep(i, q) {
    char t, d;
    tie(t, d) = spells[i];
    if (s[x] == t) { // match
      if (dir == 0) {
        x = (d=='L') ? (x-1) : (x+1);
      } else { // reverse
        x = (d=='L') ? (x+1) : (x-1);
      }
    }
    if (x < 0) { return false; }
    if (x >= n) { return true; }
  }
  return true;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> q;
  cin >> s;
  spells.resize(q);
  rep(i, q) {
    cin >> spells[i].first >> spells[i].second;
  }

  vector<ll> range(2);
  rep(k, 2) {
    // Here, we do binary search to calculate left boundary.
    ll l = -1, r = n;
    // search in (l, r]
    while (r-l > 1) {
      ll mid = (r+l)/2;
      if (check(mid)) { // mid does not go to -1
        r = mid;
      } else {
        l = mid;
      }
    }
    // Here, l is out. r is in.
    range[k] = r;
    reverse(all(s));
    dir ^= 1;
  }

  ll left  = range[0];
  ll right = n-1-range[1];

  if (right >= left) {
    cout << (right-left+1) << endl;
  } else {
    cout << 0 << endl;
  }
}
