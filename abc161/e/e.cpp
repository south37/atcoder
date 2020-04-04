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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k, c;
  cin >> n >> k >> c;
  string s;
  cin >> s;

  vector<ll> avail; // available
  {
    rep(i, n) {
      if (s[i] == 'o') {
        avail.push_back(i);
      }
    }
  }

  // Here, st has the information
  set<ll> selected;
  selected.insert(avail[0]);
  ll last = avail[0];
  for (int i = 1; i < avail.size(); ++i) {
    ll idx = avail[i];
    if (idx > last + c) {
      selected.insert(idx);
      last = idx;
    }

    if (selected.size() == k) { // reached
      break;
    }
  }

  // Here, selected has idx in greeday way.
  set<ll> remain;
  for (int idx : avail) {
    if (selected.find(idx) == selected.end()) { // not in selected
      remain.insert(idx);
    }
  }

  vector<ll> ans;
  // ll ans = 0;
  // Here, selected, remain is created.
  // We try all elements in selected, if we can create a set, then it should not be ans.
  for (int unselected : selected) {
    set<ll> selected2;
    ll last = -INF;
    rep(i, avail.size()) {
      ll idx = avail[i];
      if (idx == unselected) { continue; } // skip unselected element

      if (idx > last + c) {
        selected2.insert(idx);
        last = idx;
      }

      if (selected2.size() == k) { // reached
        break;
      }
    }

    if (selected2.size() == k) { // can create
      // do nothing
    } else {
      ans.push_back(unselected + 1);
    }
  }

  for (int id : ans) {
    cout << id << endl;
  }
}
