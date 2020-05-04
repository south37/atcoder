// ref. https://codeforces.com/contest/1313/submission/71676206

#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; ++i)

vector<ll> build_z(const string& s) {
  ll n = s.size();
  vector<ll> z(n, 0);
  ll l = -1, r = -1;
  for (ll i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<ll>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

void search(const string& text, const string& pattern, vector<ll>& result) {
  vector<ll> z = build_z(pattern + "$" + text);

  ll p = pattern.length();
  for (ll i = p + 1; i < z.size(); ++i) {
    if (z[i] == p) {
      result.push_back(i-p-1);
    }
  }
}

int main(int argc, char** argv) {
  string s, t;
  cin >> s;
  cin >> t;

  vector<ll> matches;
  search(s, t, matches);

  for (ll idx : matches) {
    cout << idx << endl;
  }

  cout << s << endl;
  cout << t << endl;
}
