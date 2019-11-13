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

// Run Length Encoding
// e.g. issii -> (i1)(s2)(i2)
vector< pair<char, ll> > run_length(const string& s) {
  ll n = s.size();
  vector< pair<char, ll> > res;
  rep(i, n) {
    ll cnt = 1;
    while (i < n - 1 && s[i] == s[i+1]) {
      ++cnt;
      ++i;
    }
    res.emplace_back(s[i], cnt);
  }
  return res;
}

int main(int argc, char** argv) {
  string s = "issii";

  vector< pair<char, ll> > cnts = run_length(s);
  for (auto x : cnts) {
    cout<<"("<<x.fr<<","<<x.sc<<")";
  }
  cout << endl;
}
