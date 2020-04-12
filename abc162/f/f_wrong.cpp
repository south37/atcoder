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
  vector<ll> a(n);
  rep(i, n) {
    cin >> a[i];
  }
  // Here, check the even-odd
  if (n%2 == 0) { // even
    // here, we should check of sum in even, oda
    ll eSum = 0;
    ll oSum = 0;
    rep(i, n) {
      if (i%2==0) {
        eSum += a[i];
      } else {
        oSum += a[i];
      }
    }
    cout << max(eSum, oSum) << endl;
    return 0;
  }

  // Here, n%2== 1
  vector<ll> leftOdds(n); // sum of [0, i] in odds
  vector<ll> leftEvens(n); // sum of [0, i] in even
  vector<ll> rightOdds(n);
  vector<ll> rightEvens(n);

  // Scan from left
  leftEvens[0] = a[0];
  leftOdds[0] = 0;
  for (int i = 1; i < n; ++i) {
    leftEvens[i] = leftEvens[i-1];
    leftOdds[i] = leftOdds[i-1];
    if (i%2 == 0) {
      leftEvens[i] += a[i];
    } else {
      leftOdds[i] += a[i];
    }
  }

  rightEvens[n-1] = a[n-1]; // n-1 is even
  rightOdds[0] = 0;
  // Scan from right
  for (int i = n-2; i >= 0; --i) {
    rightEvens[i] = rightEvens[i+1];
    rightOdds[i] = rightOdds[i+1];
    if (i%2 == 0) {
      rightEvens[i] += a[i];
    } else {
      rightOdds[i] += a[i];
    }
  }

  cout << "a: "; printvec(a);
  cout << "leftEvens:"; printvec(leftEvens);
  cout << "leftOdds:"; printvec(leftOdds);
  cout << "rightEvens:"; printvec(rightEvens);
  cout << "rightOdds:"; printvec(rightOdds);

  cout << "leftEvens[n-2]: " << leftEvens[n-2] << endl;
  cout << "leftOdds[n-2]: " << leftOdds[n-2] << endl;
  cout << "rightEvens[1]: " << rightEvens[1] << endl;
  cout << "rightOdds[1]: " << rightOdds[1] << endl;

  ll ans = max(leftEvens[n-2], leftOdds[n-2]);
  ans = max(ans, max(rightOdds[1], rightEvens[1]));
  for (int i = 1; i < n-1; ++i) {
    // Here, i is not used
    cout << "i: " << i << endl;
    cout << "leftEvens + rightOdds: " << leftEvens[i-1] + rightOdds[i+1] << endl;
    cout << "leftOdds + rightEvens: " << leftOdds[i-1]  + rightEvens[i+1] << endl;

    if (i % 2 == 0) {
      ans = max(ans, leftEvens[i-2] + rightOdds[i+1]);
      ans = max(ans, leftOdds[i-1]  + rightEvens[i+2]);
      ans = max(ans, leftEvens[i-2]  + rightEvens[i+2]);
    } else {
      ans = max(ans, leftEvens[i-1] + rightOdds[i+1]);
      ans = max(ans, leftOdds[i-1]  + rightEvens[i+1]);
    }
  }
  cout << ans << endl;
}

