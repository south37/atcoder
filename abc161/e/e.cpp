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

vector<ll> getPositions(const string& s, ll k, ll c) {
  ll n = s.size();
  ll i = 0;
  vector<ll> ans;
  while (i < n && ans.size() < k) {
    if (s[i] == 'o') {
      ans.push_back(i);
      i += c+1;
    } else {
      ++i;
    }
  }
  return ans;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, k, c;
  cin >> n >> k >> c;
  string s;
  cin >> s;

  vector<ll> l = getPositions(s, k, c);
  reverse(all(s));
  vector<ll> r = getPositions(s, k, c);
  reverse(all(s)); // revert state
  rep(i, k) { r[i] = n-1-r[i]; } // update index of r. r is decreasing order.

  // Here, l and r are calculated.
  vector<ll> lastL(n+1, -1); // lastL[i] .. last position before i.
  rep(i, k) { lastL[l[i]+1] = i; }
  rep(i, n) {
    if (lastL[i+1] == -1) { lastL[i+1] = lastL[i]; }
  }
  vector<ll> lastR(n+1, -1); // lastR[i+1] .. last position after i.
  rep(i, k) { lastR[r[i]] = i; }
  for (int i = n-1; i >= 0; --i) {
    if (lastR[i] == -1) { lastR[i] = lastR[i+1]; }
  }

  vector<ll> ans;
  rep(i, n) {
    if (s[i] == 'x') { continue; }
    ll li = lastL[i]; // last position before i.
    ll ri = lastR[i+1]; // last position after i.
    ll cnt = 0; // maximum count without i.
    if (li != -1) { cnt += li + 1; }
    if (ri != -1) { cnt += ri + 1; }
    if (li != -1 && ri != -1 && (r[ri]-l[li] <= c)) {
      --cnt;
    }
    if (cnt >= k) { continue; } // we can make k without i
    ans.push_back(i);
  }

  for (int idx : ans) {
    cout << idx + 1 << endl;
  }
}
