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

  ll n;
  cin >> n;
  string S;
  cin >> S;

  ll s = 0; // summ

  vector<char> chars(3);
  chars[0] = 'B';
  chars[1] = 'G';
  chars[2] = 'R';

  do {
    ll now = 0;
    ll r = 0;
    char a = chars[0];
    char b = chars[1];
    char c = chars[2];

    // cout << "a:" << a << endl;
    // cout << "b:" << b << endl;
    // cout << "c:" << c << endl;

    rep(i, n) {
      if (S[i] == a) {
        ++r;
      } else if (S[i] == b) {
        now += r;
      } else { // s[i] == c
        s += now;
      }
    }
  } while (next_permutation(all(chars)));

  // cout << "s: " << s << endl;

  // Here, all sum is calculated
  for (int m = 1; m < n; ++m) {
    // Here, we try all cas
    rep(i, n) {
      ll j = i + m;
      ll k = j + m;
      if (j >= n || k >= n) { break; }
      // Check (i,j,k)
      if (S[i] != S[j] && S[j] != S[k] && S[i] != S[k]) { // valid
        --s;
      }
    }
  }

  cout << s << endl;
}
