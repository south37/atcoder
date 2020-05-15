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

class SmallestRegular {
public:
  vector<int> findLexSmallest(string S) {
    int n = S.size();
    vector<int> ans;
    while (true) {
      // cout << "S: " << S << endl;

      // First, find ')('
      int openPos = -1;
      rep(i,n-1) {
        if (S[i] == ')' && S[i+1] == '(') {
          openPos = i+1;
          break;
        }
      }
      if (openPos == -1) { // not found. S is already valid.
        break;
      }
      // Here, openPos is found. scan from right.
      int i = openPos - 1;
      int cnt = 0;
      while (i >= 0) {
        if (S[i] == ')') {
          ++cnt;
        } else { // S[i] == '('
          --cnt;
        }
        if (cnt == 0) { // pair is found
          // Here, we should swap [i,openOos-1],[openPos, openPos]
          int a = i, b = openPos-1, c = openPos;
          S = swapS(S, a, b, c);
          ans.push_back(i); ans.push_back(openPos-1); ans.push_back(openPos);
          break;
        }
        --i;
      }
    }
    return ans;
  }

  string swapS(string& S, int a, int b, int c) {
    string pre = S.substr(0,a);
    string suf = S.substr(c+1);
    string aa = S.substr(a,b+1-a);
    string bb = S.substr(b+1,c-b);
    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;
    // cout << "c: " << c << endl;
    // cout << "S: " << S << endl;
    // cout << "pre: " << pre << endl;
    // cout << "suf: " << suf << endl;
    // cout << "aa: " << aa << endl;
    // cout << "bb: " << aa << endl;
    string ans = pre + bb + aa + suf;
    assert(ans.size() == S.size());
    return ans;
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  SmallestRegular a0;
  printvec(a0.findLexSmallest("(()())"));
  printvec(a0.findLexSmallest("()()()"));
  printvec(a0.findLexSmallest("()()()()"));
  printvec(a0.findLexSmallest("(()()()())"));
  printvec(a0.findLexSmallest("(()(()())())"));
  printvec(a0.findLexSmallest("((()))"));
  // std::cout << "a0: Expected ~, Got \"" << setprecision(10) << a0.getMin() << "\"" << std::endl;
}
