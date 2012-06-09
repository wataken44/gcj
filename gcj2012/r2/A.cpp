
/*
  A.cpp
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


string solve(int n, vector<int> d, vector<int> l, int w)
{
  d.push_back(w);
  l.push_back(0);

  int dsz = d.size();

  vector<int> dp(dsz, -1);
  vector<int> rc(dsz, INT_MAX);
  
  TIMES(x, dsz - 1) {
    int y = x + 1;
    while(true) {
      if(d[x] + l[x] >= d[y]) {
        rc[y] = min(rc[y], x);
        ++y;
        if(y == dsz) break;
      }else {
        break;
      }
    }
  }

  dp[0] = d[0] + min(d[0], l[0]);
  
  FOR(x, 1, dsz) {
    if(rc[x] == INT_MAX) continue;
    DOWNTO(y, x - 1, rc[x]) {
      if(dp[y] == -1) continue;
      // if(y < 0) cout << "error" << endl; 
      if(dp[y] >= d[x]) {
        dp[x] = max(dp[x], min(l[x], d[x] - d[y]) + d[x]);
      }
    }
  }

  return dp[n] == -1 ? "NO" : "YES";
}

int main(int argc, char *argv[])
{

  int t;
  cin >> t;

  UPTO(tt, 1, t) {
    int n;
    cin >> n;

    vector<int> d;
    vector<int> l;

    TIMES(nn, n) {
      int dd, ll;
      cin >> dd >> ll;
      d.push_back(dd);
      l.push_back(ll);
    }

    int w;
    cin >> w;

    // DUMP(n);DUMP(d);DUMP(l);DUMP(w);
    
    cout << "Case #"<< tt << ": " << solve(n, d, l, w) << endl; 
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
