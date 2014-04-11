
/*
  b.cpp
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

int main(int argc, char *argv[])
{
  int t = 0;
  cin >> t;

  UPTO(tt, 1, t) {
    int e, r, n;
    cin >> e >> r >> n;
    vector<int> v;
    v.push_back(0);

    TIMES(nn, n) {
      int tmp;
      cin >> tmp;
      v.push_back(tmp);
    }

    // DUMP(e);DUMP(r);DUMP(n);DUMP(v);

    
    vector< vector<ll> > dp(n + 1, vector<ll>(e + 1, 0));

    UPTO(nn, 1, n) {
      dp[nn][e] = dp[nn - 1][max(e - r, 0)];
      DOWNTO(ee, e - 1, 0) {
        int rr = min(e - ee, r);
        dp[nn][ee] = max(dp[nn][ee], dp[nn][ee + rr] + rr * v[nn]);
        if(r <= ee) {
          dp[nn][ee] = max(dp[nn][ee], dp[nn - 1][ee - r]);
        }
      }
    }

    ll result = 0;
    UPTO(ee, 0, e) {
      result = max(result, dp[n][ee]);
    }

    //DUMP(v);
    //DUMP(dp);
    
    cout << "Case #" << tt << ": " << result << endl;
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
