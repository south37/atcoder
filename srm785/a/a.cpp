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

class EllysPalMulDiv2 {
public:
  int getMin(int x) {
    for (ll y = 1; y <= 1000; ++y) {
      if (isPalindrom(y*x)) {
        return y;
      }
    }
    return -1;
  }

  bool isPalindrom(ll n) {
    vector<ll> ds;
    while (n>0){
      ds.push_back(n%10);
      n /= 10;
    }
    ll m = ds.size();

    rep(i,m) {
      if (ds[i] != ds[m-1-i]) {
        return false;
      }
    }
    return true;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  Class a0;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(42) << "\"" << std::endl;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(121) << "\"" << std::endl;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(1337) << "\"" << std::endl;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(13) << "\"" << std::endl;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(100) << "\"" << std::endl;
  std::cout << "a0: Expected ~, Got \"" << a0.getMin(39325) << "\"" << std::endl;
  // std::cout << "a0: Expected ~, Got \"" << setprecision(10) << a0.getMin() << "\"" << std::endl;
}
