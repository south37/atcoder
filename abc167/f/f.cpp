// ref. https://www.youtube.com/watch?v=ENSOy8u9K9I&feature=youtu.be

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

bool check(const vector<P>& s) {
  int h = 0;
  for (const P& p : s) {
    int b = h+p.first; // proceed to min.
    if (b < 0) { return false; }
    h += p.second;
  }
  return true;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;

  int total = 0;
  vector<P> ls, rs;
  rep(i,n) {
    string s;
    cin >> s;
    int h = 0, b = 0; // h .. sum, b .. min
    for (char c : s) {
      if (c == '(') {
        ++h;
      } else {
        --h;
      }
      chmin(b, h);
    }
    if (h>0) {
      ls.emplace_back(b,h);
    } else {
      rs.emplace_back(b-h,-h); // from right.
    }
    total += h;
  }
  sort(ls.rbegin(), ls.rend()); // decreasing order
  sort(rs.rbegin(), rs.rend()); // decreasing order
  if (check(ls) && check(rs) && total == 0) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}
