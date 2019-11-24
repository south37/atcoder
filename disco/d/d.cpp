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

ll ans = 0;

const ll LOGM = 60; // 2**50 ~ 10**15
vector< vector<ll> > trans(10, vector<ll>(LOGM, -1));
vector< vector<ll> > steps(10, vector<ll>(LOGM, -1));

void constract_doubling() {
  for (ll exp = 1; exp < LOGM; ++exp) {
    for (ll i = 0; i <= 9; ++i) {
      // doubling of trans
      trans[i][exp] = trans[trans[i][exp-1]][exp-1];

      // doubling of step
      // trans[6][0] => 3. (6 => 3), steps[6][0] => 2. 66 => 3
      // 6666 => 33 => 6
      //     2 * 2  1
      // (6666)(6666) => 66 =>
      //            (steps[i][exp-1] * 2)
      // e.g. steps[3][1] = steps[
      steps[i][exp] = steps[i][exp-1] * 2 + steps[trans[i][exp-1]][0];

      cout << "trans["<<i<<"]["<<exp<<"]: " << trans[i][exp] << endl;
      cout << "steps["<<i<<"]["<<exp<<"]: " << steps[i][exp] << endl;
    }
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll m; // 2e5
  cin >> m;
  vector<ll> ds(m);
  vector<ll> cs(m);
  rep(i, m) {
    cin >> ds[i] >> cs[i];
  }

  // Next, wet treact ieach d, c pair.
  // we consider them as independent.

  // We make a translation table
  trans[0][0] = 0; steps[0][0] = 1;
  trans[1][0] = 2; steps[1][0] = 1;
  trans[2][0] = 4; steps[2][0] = 1;
  trans[3][0] = 6; steps[3][0] = 1;
  trans[4][0] = 8; steps[4][0] = 1;
  trans[5][0] = 1; steps[5][0] = 2;
  trans[6][0] = 3; steps[6][0] = 2;
  trans[7][0] = 5; steps[7][0] = 2;
  trans[8][0] = 7; steps[8][0] = 2;
  trans[9][0] = 9; steps[9][0] = 2;

  // We make doubling table.
  constract_doubling();

  ll steps_ans= 0;
  vector<ll> rests_d; // The d

  rep(i, m) {
    ll d = ds[i];
    ll c = cs[i];

    for (ll exp = LOGM-1; exp >= 0; --exp) {
      if (c & (1LL<<(exp+1))) { // c contains the exp bit.
        // cout << "d: " << d << endl;
        // cout << "c: " << c << endl;
        // cout << "(1<<(exp+1)): " << (1LL<<(exp+1)) << endl;
        // cout << "exp: " << exp << endl;
        // cout << "steps[d][exp]: " << steps[d][exp] << endl;

        steps_ans += steps[d][exp];
        rests_d.push_back(trans[d][exp]);
        c -= (1LL<<(exp+1));
      }
    }
    if (c > 0) {
      assert(c == 1);
      rests_d.push_back(d);
    }
  }

  // cout << "steps_ans: " << steps_ans << endl;
  // cout << "rests_d.size(): " << rests_d.size() << endl;

  // Now, rests_contains small. We can simulate it.
  ll rest = 0;
  while (rests_d.size() > 1) {
    ll a = rests_d.back(); rests_d.pop_back();
    ll b = rests_d.back(); rests_d.pop_back();
    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    if (a + b >= 10) {
      rests_d.push_back(1);
      rests_d.push_back((a+b)%10);
      ++rest;
    } else {
      rests_d.push_back((a+b)%10);
      ++rest;
    }
  }

  cout << steps_ans + rest << endl;
}
