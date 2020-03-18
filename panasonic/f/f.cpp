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

// Calculate the distance between (ai,aj) and (bi,bj)
ll solve(ll ai, ll aj, ll bi, ll bj) {
  if (aj > bj) {
    swap(ai, bi);
    swap(bj, bj);
  }
  ll s = 1;
  rep(i, 30) { s *= 3; }
  ll dist = abs(ai-bi) + abs(aj-bj); // Manhattan distance
  ll res = dist;
  while (1) {
    s /= 3;
    if (s <= 0) { break; }
    ll nai = ai/s, nbi = bi/s; // location at scale s.
    if (nai != nbi) { break; } // if not in same row, result should be Manhattan distance
    ll naj = aj/s, nbj = bj/s;
    if (nai == 1 && abs(naj-nbj) > 1) { // not in same column
      ll up  = s*nai-1;
      ll bot = s*(nai+1);
      ll loss = min(ai,bi) - up;
      loss = min(loss, bot - max(ai,bi));
      res = dist + loss*2;
      break;
    }
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll q;
  cin >> q;
  rep(qi, q) {
    ll ai, aj, bi, bj;
    cin >> ai >> aj >> bi >> bj;
    --ai; --aj; --bi; --bj; // 0-indexed
    ll ans = 0;
    ans = max(ans, solve(ai, aj, bi, bj)); // horizontal
    ans = max(ans, solve(aj, ai, bj, bi)); // vertical
    cout << ans << endl;
  }
}
