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

  set<P> bigs; // sum is plus
  set<P> smalls; // sum is minus

  vector<string> S(n);
  rep(i,n) {
    cin >> S[i];
    ll minV = 0;
    ll now = 0;
    rep(j, S[i].size()) {
      if (S[i][j] == '(') {
        ++now;
      } else {
        --now;
      }
      chmin(minV, now);
    }
    ll minCost = 0;
    if (minV < 0) { // In this case, we need minCost to enter.
      minCost = -minV;
    }
    // cout << S[i] << endl;
    // cout << "minCost,now: " << minCost << "," << now << endl;
    if (now >= 0) { // positive or 0
      bigs.insert(P(minCost, now));
    } else { // negative
      smalls.insert(P(minCost, now));
    }
  }

  ll now = 0;
  while (!bigs.empty()) {
    auto it = bigs.upper_bound(P(now, INF)); // try larger one.
    if (it == bigs.begin()) { // not found
      cout << "No" << endl;
      return 0;
    }
    now += prev(it)->second;
    bigs.erase(prev(it));
  }

  vector<P> sms; // pair of <diff, minCost>
  for (auto it = smalls.begin(); it != smalls.end(); ++it) {
    // sms.push_back(P(it->second, it->first));
    sms.push_back(*it);
  }
  sort(all(sms));
  // reverse(all(sms)); // decreasing order of diff.
  for (auto& p : sms) {
    ll diff = p.second;
    ll minCost = p.first;
    if (now < minCost) {
      cout << "No" << endl;
      return 0;
    }
    now += diff;
  }
  // while (!smalls.empty()) {
  //   auto it = smalls.upper_bound(P(now, INF));
  //   if (it == smalls.begin()) { // not found
  //     cout << "No" << endl;
  //     return 0;
  //   }
  //   now += prev(it)->second;
  //   smalls.erase(prev(it));
  // }
  // Here, bigs and smalls are empty
  if (now != 0) { // invalid
    cout << "No" << endl;
  } else {
    cout << "Yes" << endl;
  }
}
