
/*
  c.cpp
 */

#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

typedef int int_type;

// -- utility --
// C-style loop
#define FOR(x, a, b) for(int_type x = static_cast<int_type>(a); x < static_cast<int_type>(b); ++x)
#define FORN(x, n) FOR(x, 0, n)
// Ruby-style loop
#define TIMES(x, n) FOR(x, 0, n)
#define STEP(x, a, b, s) for(int_type x = static_cast<int_type>(a); s > 0 ? x <= static_cast<int_type>(b) : x >= static_cast<int_type>(b); x += static_cast<int_type>(s) )
#define UPTO(x, a, b) for(int_type x = static_cast<int_type>(a); x <= static_cast<int_type>(b); ++x)
#define DOWNTO(x, a, b) for(int_type x = static_cast<int_type>(a); x >= static_cast<int_type>(b); --x)
#define EACH(c, i) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALL(cont, it, cond, ret) \
  bool ret = true; EACH(cont, it) { if(!(cond)) {ret=false;break;} }
#define ANY(cont, it, cond, ret) \
  bool ret = false; EACH(cont, it) { if(cond) {ret=true;break;} }


// debug
#define DUMP(x) std::cout << #x << " = " << to_s(x) << std::endl;

using namespace std;

template<typename T> string to_s(const T& v);
template<> string to_s(const string& v);
template<> string to_s(const bool& v);
template<typename T> string to_s(const vector<T>& v);
template<typename T> string to_s(const list<T>& v);
template<typename T> string to_s(const set<T>& v);
template<typename F, typename S> string to_s(const pair<F,S>& v);
template<typename K, typename V> string to_s(const map<K,V>& v);

typedef long long ll;

ll power(ll n, ll k) {
  ll r = 1;
  TIMES(kk, k) {
    r *= n;
  }
  return r;
}

template<typename T>
T gcd(T a, T b)
{
  if(a > b) swap(a, b);
  while(a != 0) {
    T t = b % a;
    b = a;
    a = t;
  }
  return b;
}

template<typename T>
T lcg(T a, T b)
{
  return (a / gcd(a, b)) * b;
}

int main(int argc, char *argv[])
{
  int t = 0;
  cin >> t;
  UPTO(tt, 1, t) {
    
    int r, n, m, k;
    cin >> r >> n >> m >> k;

    cout << "Case #" << tt << ":" << endl;

    TIMES(rr, r) {
      vector<ll> prod;
      ll lc = 1;
      TIMES(kk, k) {
        ll tmp;
        cin >> tmp;
        prod.push_back(tmp);

        lc = lcd(tmp, lc);
      }
      sort(prod.begin(), prod.end());

      //DUMP(prod);
      int digits = m - 2 + 1;
      ll pow = power(digits, n);

      for(ll g = 0; g < pow; ++g) {
        ll gg = g;
        ll aprod = 1;
        vector<int> a;
        
        TIMES(nn, n) {
          int aa = 2 + (gg % digits);
          a.push_back(aa);
          gg /= digits;

          aprod *= aa;
        }

        
        bool ok = true;
        TIMES(kk, prod.size()) {
          if(aprod % prod[kk] != 0) {
            ok = false;
            break;
          }
        }
        if(ok) {
          TIMES(nn, a.size()) {
            cout << a[nn];
          }
          cout << endl;
          break;
        }
      }
    }
    
  }
  
  return 0;
}


template<typename T> string to_s(const T& v) { ostringstream oss; oss << v; return oss.str(); }
template<> string to_s(const string& v) { ostringstream oss; oss << '"' << v << '"'; return oss.str(); }
template<> string to_s(const bool& v) { ostringstream oss; oss << ( v ? "true" : "false") ; return oss.str(); } 
template<typename T> string to_s(const vector<T>& v) { ostringstream oss; oss << "["; EACH(v,i) oss << to_s(*i) << ","; oss << "]"; return oss.str(); }
template<typename T> string to_s(const list<T>& v) { ostringstream oss; oss << "("; EACH(v,i) oss << to_s(*i) << ","; oss << ")"; return oss.str(); }
template<typename T> string to_s(const set<T>& v) { ostringstream oss; oss << "{"; EACH(v,i) oss << to_s(*i) << ","; oss << "}"; return oss.str(); }
template<typename F, typename S> string to_s(const pair<F,S>& v) { ostringstream oss; oss << "<" << to_s(v.first) << " " << to_s(v.second) << ">"; return oss.str(); }
template<typename K, typename V> string to_s(const map<K,V>& v) { ostringstream oss; oss << "{"; EACH(v,i) oss << to_s(i->first) << " => " << to_s(i->second) << ","; oss << "}"; return oss.str(); }
