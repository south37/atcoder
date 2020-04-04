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
  set<ll> factors;

  {
    ll now = n;
    ll i = 2;
    while (i * i <= now) {
      if (now % i == 0) {
        factors.insert(i);
        while (now % i == 0) {
          now /= i;
        }
      }
      ++i;
    }
    if (now > 1) {
      factors.insert(now);
    }
  }

  vector<pair<ll, ll>> factorCnts; // { factor, cnt }
  {
    ll now = n;
    for (ll factor : factors) {
      ll cnt = 0;
      while (now % factor == 0) {
        ++cnt;
        now /= factor;
      }
      factorCnts.push_back({ factor, cnt });
    }
  }

  for (auto& p : factorCnts) {
    ll factor = p.first;
    ll cnt = p.second;
    cout << factor << ": " << cnt << endl;
  }
}
