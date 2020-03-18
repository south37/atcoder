// ref. https://www.youtube.com/watch?v=9MphwmIsO7Q

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

// Morris-Pratt (MP, KMP)
// https://youtu.be/9MphwmIsO7Q?t=7283
template<typename T>
struct MP {
  int n;
  T t;
  vector<int> a;
  MP() {}
  MP(const T& t): t(t) {
    n = t.size();
    a = vector<int>(n+1);
    a[0] = -1;
    int j = -1;
    for (int i = 0; i < n; ++i) {
      while (j != -1 && t[j] != t[i]) j = a[j];
      j++;
      a[i+1] = j;
    }
  }
  int operator[](int i) { return a[i];}
  vector<int> findAll(const T& s) {
    vector<int> res;
    int j = 0;
    for (int i = 0; i < s.size(); ++i) {
      while (j != -1 && t[j] != s[i]) j = a[j];
      j++;
      if (j == n) {
        res.push_back(i-j+1);
        j = a[j];
      }
    }
    return res;
  }
};

// int main(int argc, char** argv) {
//   string t, s;
//   cin >> t;
//   cin >> s;
//
//   // Find all t in s. |t| <= |s|
//   MP<string> mp(t);
//   rep(i, t.size()+1) {
//     cout << mp[i] << ' ';
//   }
//   cout << endl;
//
//   vector<int> ans = mp.findAll(s);
//   for (int i : ans) {
//     cout << i << endl;
//   }
// }

vector<int> f(vector<int>& a) {
  int n = a.size();
  vector<int> res(n);
  rep(i, n) {
    res[i] = a[i]^a[(i+1)%n];
  }
  return res;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<int> a(n), b(n);
  rep(i, n) { cin >> a[i]; }
  rep(i, n) { cin >> b[i]; }

  vector<int> xa = f(a);
  vector<int> xb = f(b);
  xa.insert(xa.end(), xa.begin(), prev(xa.end()));

  // find all xb in (xa+xa[0..n-1))
  MP<vector<int>> mp(xb);
  vector<int> ks = mp.findAll(xa);
  for (int k : ks) {
    int x = a[k]^b[0];
    cout << k << " " << x << endl;
  }
}
