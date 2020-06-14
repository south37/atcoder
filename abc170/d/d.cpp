#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>
#include <stack>

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
  vector<ll> a(n);
  rep(i,n) {
    cin >> a[i];
  }

  map<ll,ll> vs;
  rep(i,n) {
    ++vs[a[i]];
  }
  // printmap(vs);

  ll ans = 0;
  rep(i,n) {
    --vs[a[i]];
    // if (vs[a[i]] == 0) { // reach to 0
    //   vs.erase(a[i]);
    // }

    set<ll> divs;
    {
      ll j = 1;
      while (j*j <= a[i]) {
        if (a[i] % j == 0) {
          divs.insert(j);
          divs.insert(a[i]/j);
        }
        ++j;
      }
    }
    // Here, divs has all divisors
    // printvec(divs);

    bool found = false;
    for (ll v : divs) {
      if (vs.find(v) != vs.end() && vs[v] != 0) {
        found = true;
      }
    }
    if (!found) { // not divisoble
      ++ans;
    }

    ++vs[a[i]];
  }

  cout << ans << endl;
}
