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

/*
string zero[5] = {
  ".###",
  ".#.#",
  ".#.#",
  ".#.#",
  ".###",
};

string one[5] = {
  "..#.",
  ".##.",
  "..#.",
  "..#.",
  ".###",
};

  ".###"
  "...#"
  ".###"
  ".#.."
  ".###"

  ".###"
  "...#"
  ".###"
  "...#"
  ".###"
.#.#
.#.#
.###
...#
...#

.###
.#..
.###
...#
.###

.###
.#..
.###
.#.#
.###

.###.###.###.
...#.#.#.#.#.
...#.###.###.
...#.#.#...#.
...#.###.###.
*/

string nums[5] = {
  ".###..#..###.###.#.#.###.###.###.###.###.",
  ".#.#.##....#...#.#.#.#...#.....#.#.#.#.#.",
  ".#.#..#..###.###.###.###.###...#.###.###.",
  ".#.#..#..#.....#...#...#.#.#...#.#.#...#.",
  ".###.###.###.###...#.###.###...#.###.###.",
};

vector<string> s(5);

// idx .. index
bool isNum(int idx, int num) {
  ll start = idx*4;
  ll numStart = num*4;

  bool res = true;
  rep(i,5) {
    rep(j,4) {
      if (s[i][start+j] != nums[i][numStart+j]) {
        res = false;
        break;
      }
    }
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  rep(i,5) {
    cin >> s[i];
  }
  string ans;
  rep(i,n) {
    rep(j,10) { // loop in [0,9]
      if (isNum(i,j)) {
        ans += (char)('0'+j);
      }
    }
  }
  cout << ans << endl;
}
