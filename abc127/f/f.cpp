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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

template<typename T> void print_queue(T& q) {
  vector<ll> tmp;
  while(!q.empty()) {
    ll v = q.top();
    cout << v << " ";
    q.pop();
    tmp.push_back(v);
  }
  for (auto v : tmp) {
    q.push(v);
  }
  cout << endl;
}

// The size of "smaller" is equal or larger by 1.
priority_queue<ll> smaller; // decreasing order
priority_queue<ll, vector<ll>, greater<ll>> larger; // increasing order

void balance() {
  while (1) {
    ll s_size = smaller.size();
    ll l_size = larger.size();
    if ((s_size == l_size) || (s_size == l_size+1)) { return; }

    if (s_size > l_size) {
      ll v = smaller.top(); smaller.pop();
      larger.push(v);
    } else { // s_size < l_size
      ll v = larger.top(); larger.pop();
      smaller.push(v);
    }
  }
}

void add(ll v) {
  if (smaller.size() == 0) {
    smaller.push(v);
    return;
  }

  if (v <= smaller.top()) {
    smaller.push(v);
  } else {
    larger.push(v);
  }

  balance();

  // For Debug
  // cout << "smaller: " << endl;
  // print_queue(smaller);
  // cout << "larger: " << endl;
  // print_queue(larger);
}

ll current() {
  return smaller.top();
}

int main(int argc, char** argv) {
  ll Q;
  cin >> Q;

  bool updated = false;
  ll f_min = 0; // The minimum f(x) of each step.

  rep(i, Q) {
    int t;
    cin >> t;
    if (t == 1) { // update
      ll a, b;
      cin >> a >> b;

      if (!updated) { // first state.
        updated = true;
        f_min = b;
        add(a);
      } else {
        bool prev_balanced = (smaller.size() == larger.size());
        ll old_x = current();
        add(a);
        ll new_x = current();

        // from prev
        if (prev_balanced) {
          if (new_x < old_x) {
            f_min += abs(new_x - old_x);
          } else {
            // Do nothing.
          }
        } else { // old_x is an unique minimum point.
          f_min += abs(new_x - old_x);
        }
        f_min += b + abs(new_x - a);
      }
    } else { // query
      cout << current() << " " << f_min << endl;
    }
  }
}
