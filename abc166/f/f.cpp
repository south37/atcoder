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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,a, b, c;
  cin >> n >> a >> b >> c;
  vector<ll> rawVars(3); // 0..a, 1..b, 2..c
  rawVars[0] = a; rawVars[1] = b; rawVars[2] = c;
  vector<ll> vars(3); // 0 .. ab, 1..bc, 2..ca
  ll& ab = vars[0]; ll& bc = vars[1]; ll& ca = vars[2];
  ab = a+b, bc=b+c, ca=a+c;
  vector<ll> cnts(3); // 0 .. ab, 1..bc, 2..ca
  vector<ll> ops; // index
  rep(i,n) {
    string s;
    cin >> s;
    // ops.push_back(s);
    if (s == "AB") {
      ++cnts[0];
      ops.push_back(0);
    } else if (s == "BC") {
      ++cnts[1];
      ops.push_back(1);
    } else {
      ++cnts[2];
      ops.push_back(2);
    }
  }

  // printvec(vars);
  // printvec(ops);
  // printvec(cnts);

  vector<char> ans;
  rep(i,n) {
    ll op = ops[i];
    if (vars[op] == 0) { // we can not do this operation
      cout << "No" << endl;
      return 0;
    }
    --cnts[op]; // consume remaining.

    // Here, we can do this operation
    ll selectedOp = -1;
    ll larger = -1;
    rep(j,3) {
      if (j == op) { continue; }
      // Here, j is op. k is others

      if (op == 0) { // ab
        if (j == 1) { // bc. a->b
          if (rawVars[0] == 0) { continue; } // a is 0.
        } else { // ca. b->a.
          if (rawVars[1] == 0) { continue; } // b is 0.
        }
      } else if (op == 1) { // bc
        if (j == 2) { // ca. b->c.
          if (rawVars[1] == 0) { continue; }
        } else { // ab. c->b
          if (rawVars[2] == 0) { continue; }
        }
      } else { // ca
        if (j == 0) { // ab. c->a
          if (rawVars[2] == 0) { continue; }
        } else { // bc. a->c
          if (rawVars[0] == 0) { continue; }
        }
      }
      if (cnts[j] > larger) {
        larger = cnts[j];
        selectedOp = j; // select op with larger cnts.
      }
    }
    if (selectedOp == -1) {
      cout << "No" << endl;
      return 0;
    }
    // cout << "i: " << i << endl;
    // cout << "op: " << op << endl;
    // cout << "selectedOp: " << selectedOp << endl;
    // Here, selectedOp has "larger" info.
    rep(j,3) {
      if (j == op) { continue; }
      // Here, j != op
      if (j == selectedOp) {
        ++vars[j];
      } else {
        --vars[j];
      }
    }

    if (op == 0) { // ab
      if (selectedOp == 1) { // a<->b, bc is selected, a->b.
        ans.push_back('B');
      } else {
        ans.push_back('A');
      }
    } else if (op == 1) { // bc
      if (selectedOp == 2) { // b<->c. ca is selected. b->c.
        ans.push_back('C');
      } else {
        ans.push_back('B');
      }
    } else { // ca
      if (selectedOp == 0) { // c<->a. ab is selected. c->a.
        ans.push_back('A');
      } else {
        ans.push_back('C');
      }
    }
  }

  cout << "Yes" << endl;
  rep(i,n) {
    cout << ans[i] <<endl;
  }
}
