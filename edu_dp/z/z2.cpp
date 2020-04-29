// ref. https://www.hamayanhamayan.com/entry/2019/01/12/161237

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

class ConvexHullTrick {
  typedef long long coef_t;
  typedef long long coord_t;
  typedef long long val_t;

  /*
  * Line 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
  * and 'xLeft' which is intersection with previous line in hull(first line has -INF)
  */
private:
  struct Line {
    coef_t a, b;
    double xLeft;

    enum Type {
      line, maxQuery, minQuery
    } type;
    coord_t val;

    explicit Line(coef_t aa = 0, coef_t bb = 0) : a(aa), b(bb), xLeft(-INFINITY), type(Type::line), val(0) {}

    val_t valueAt(coord_t x) const { return a * x + b; }

    friend bool areParallel(const Line &l1, const Line &l2) { return l1.a == l2.a; }

    friend double intersectX(const Line &l1, const Line &l2) { return areParallel(l1, l2) ? INFINITY : 1.0 * (l2.b - l1.b) / (l1.a - l2.a); }

    bool operator<(const Line &l2) const {
      if (l2.type == line) {
        return this->a < l2.a;
      } else if (l2.type == maxQuery) {
        return this->xLeft < l2.val;
      } else { // l2.type == minQuery
        return this->xLeft > l2.val;
      }
    }
  };

  bool isMax; //whether or not saved envelope is top(search of max value)
public:
  std::set< Line > hull;  //envelope itself

private:
  /*
  * INFO:        Check position in hull by iterator
  * COMPLEXITY:  O(1)
  */
  bool hasPrev(std::set< Line >::iterator it) { return it != hull.begin(); }

  bool hasNext(std::set< Line >::iterator it) { return it != hull.end() && std::next(it) != hull.end(); }

  /*
  * INFO:        Check whether line l2 is irrelevant
  * NOTE:        Following positioning in hull must be true
  *              l1 is next left to l2
  *              l2 is right between l1 and l3
  *              l3 is next right to l2
  * COMPLEXITY:  O(1)
  */
  bool irrelevant(const Line &l1, const Line &l2, const Line &l3) { return intersectX(l1, l3) <= intersectX(l1, l2); }

  bool irrelevant(std::set< Line >::iterator it) {
    return hasPrev(it) && hasNext(it)
      && ((isMax && irrelevant(*std::prev(it), *it, *std::next(it)))
          || (!isMax && irrelevant(*std::next(it), *it, *std::prev(it))));
  }

  /*
  * INFO:        Updates 'xValue' of line pointed by iterator 'it'
  * COMPLEXITY:  O(1)
  */
  std::set< Line >::iterator updateLeftBorder(std::set< Line >::iterator it)
  {
    if ((isMax && !hasPrev(it)) || (!isMax && !hasNext(it))) {
      return it;
    }

    double val = intersectX(*it, isMax ? *std::prev(it) : *std::next(it));
    Line buf(*it);
    it = hull.erase(it);
    buf.xLeft = val;
    it = hull.insert(it, buf);
    return it;
  }

public:
  explicit ConvexHullTrick(bool isMax = false) : isMax(isMax) {}

  /*
  * INFO:        Adding line to the envelope
  *              Line is of type 'y=a*x+b' represented by 2 coefficients 'a' and 'b'
  * COMPLEXITY:  Adding N lines(N calls of function) takes O(N*log N) time
  */
  void addLine(coef_t a, coef_t b)
  {
    //find the place where line will be inserted in set
    Line l3 = Line(a, b);
    auto it = hull.lower_bound(l3);

    //if parallel line is already in set, one of them becomes irrelevant
    if (it != hull.end() && areParallel(*it, l3)) {
      if ((isMax && it->b < b) || (!isMax && it->b > b)) {
        it = hull.erase(it);
      } else {
        return;
      }
    }

    //try to insert
    it = hull.insert(it, l3);
    if (irrelevant(it)) {
      hull.erase(it);
      return;
    }

    //remove lines which became irrelevant after inserting line
    while (hasPrev(it) && irrelevant(std::prev(it))) hull.erase(std::prev(it));
    while (hasNext(it) && irrelevant(std::next(it))) hull.erase(std::next(it));

    //refresh 'xLine'
    it = updateLeftBorder(it);
    if (hasPrev(it)) {
      updateLeftBorder(std::prev(it));
    }
    if (hasNext(it)) {
      updateLeftBorder(std::next(it));
    }
  }

  val_t getBest(coord_t x) const
  {
    Line q;
    q.val = x;
    q.type = isMax ? Line::Type::maxQuery : Line::Type::minQuery;

    auto bestLine = hull.lower_bound(q);
    if (isMax) {
      --bestLine;
    }
    return bestLine->valueAt(x);
  }
};

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, c;
  cin >> n >> c;
  vector<ll> h(n);
  rep(i,n) {
    cin >> h[i];
  }

  // dp[i] .. min cost of [0,i] when using i.
  vector<ll> dp(n);
  ConvexHullTrick cht;
  dp[0] = 0;
  cht.addLine(-2*h[0], h[0]*h[0]+dp[0]); // line: -2h[i]x + h[i]*h[i]+dp[i]

  for (ll i = 1; i < n; ++i) {
    dp[i] = cht.getBest(h[i]) + h[i]*h[i] + c;
    cht.addLine(-2*h[i], h[i]*h[i]+dp[i]);
  }
  cout << dp[n-1] << endl;
}
