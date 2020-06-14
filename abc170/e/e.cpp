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

const ll ROOM_MAX = 2e5 + 5;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n,q;
  cin >> n >> q;
  vector<ll> vs(n); // idx => value
  vector<ll> roomMap(n); // idx => roomId
  vector<set<P>> rooms(ROOM_MAX); // rooms. rooms[i] is set. pair of <value,idx>
  rep(i,n) {
    ll v, room;
    cin >> v >> room;
    --room; // 0-indexed
    vs[i] = v;
    roomMap[i] = room;
    rooms[room].emplace(v,i);
  }

  set<P> ms; // max set of each rooms. <value,idx>. room has one child.
  for (auto & room : rooms) {
    if (room.size() == 0) { continue; } // skip empty room
    P child = *prev(room.end());
    ms.insert(child);
  }

  // printvec(vs);
  // printvec(roomMap);

  rep(iter,q) {
    ll idx, toRoom;
    cin >> idx >> toRoom;
    --idx; --toRoom; // 0-indexed

    // Check from
    P child = P(vs[idx],idx);
    ll f = roomMap[idx];

    // 1. remove from f.
    if (*prev(rooms[f].end()) == child) { // child is max. must update.
      ms.erase(child);
    }
    rooms[f].erase(child);
    // Here, rooms[f] is ok.
    if (rooms[f].size() > 0) {
      ms.insert(*prev(rooms[f].end()));
    }

    // 2. move to toRoom.
    if (rooms[toRoom].size() == 0) { // rooms[toRoom] is empty
      rooms[toRoom].insert(child);
      ms.insert(child);
    } else {
      if ((*prev(rooms[toRoom].end())).first < child.first) { // child is large. must update.
        // Here, Update max of rooms[toRoom]
        P prevMax = *prev(rooms[toRoom].end());
        ms.erase(prevMax);
        ms.insert(child);
      } else { // child is smaller. don't need to update
        rooms[toRoom].insert(child);
      }
    }

    roomMap[idx] = toRoom;

    // print min-max
    cout << (*ms.begin()).first << endl;
  }
}
