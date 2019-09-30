#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long int

int main(int argc, char** argv) {
  ll n;
  std::cin >> n;
  std::vector<ll> a(n+1);
  std::vector<ll> b(n);
  for (ll i = 0; i < n+1; ++i) {
    std::cin >> a[i];
    // std::cout << "a[" << i << "]: " << a[i] << std::endl;
  }
  for (ll i = 0; i < n; ++i) {
    std::cin >> b[i];
    // std::cout << "b[" << i << "]: " << b[i] << std::endl;
  }

  ll sum = 0;
  for (ll i = 0; i < n; ++i) {
    ll f = std::min(a[i], b[i]);
    a[i] -= f;
    b[i] -= f;
    sum += f;

    ll f2 = std::min(a[i + 1], b[i]);
    a[i + 1] -= f2;
    b[i] -= f2;
    sum += f2;
  }

  std::cout << sum << std::endl;
}
