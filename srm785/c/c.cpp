// ref. https://community.topcoder.com/stat?c=problem_solution&cr=40986386&rd=17965&pm=16135

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

const ll INF = 1e12;
const ll MOD = 1000000007;  // 1e9 + 7

// dp[i][j] .. using [i,n), current is j, min cost to achieve j=0 at i=n.
ll dp[55][50005];
int n;
vector<int> v;

ll solve(int i, int cur) {
  if (i >= n) { // reached to last
    if (cur == 0) { // ok
      return 0;
    } else { // ng
      return INF;
    }
  }
  if (dp[i][cur] != -1) { return dp[i][cur]; } // already calculated
  dp[i][cur] = INF;
  rep(add, 1001) {
    chmin(dp[i][cur], solve(i+1, cur^(v[i]+add)) + add);
  }
  return dp[i][cur];
}

class EllysNimDiv2 {
public:
  int getMin(vector<int>& a) {
    n = a.size();
    v = a; // copy
    memset(dp,-1,sizeof(dp));
    ll ans = INF;
    rep(add, 1001) { // loop in [0,1000]
      chmin(ans, solve(1,v[0]+add)+add);
    }
    return ans;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  vector<int> input = {42, 13, 123, 55, 666, 17};
  // vector<int> input = {42, 13+11, 123+389, 55+73, 666+6, 17+1};
  EllysNimDiv2 a0;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(input) << "\"" << std::endl;
  // std::cout << "a0: Expected ~, Got \"" << setprecision(10) << a0.method() << "\"" << std::endl;
}
