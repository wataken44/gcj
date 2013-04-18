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

string solve(int n, int m, vector<vector<int> > lawn)
{

  while(true) {
    int h_min = 101;
    int h_max = -1;

    TIMES(y, n) {
      TIMES(x, m) {
        h_min = min(h_min, lawn[y][x]);
        h_max = max(h_max, lawn[y][x]);
      }
    }
    if(h_min == h_max) return "YES";

    bool ok = true;
    TIMES(y, n) {
      TIMES(x, m) {
        if(lawn[y][x] == h_min) {
          bool y_ok = true;
          TIMES(yy, n) {
            if(lawn[yy][x] != h_min) {
              y_ok = false;
            }
          }

          bool x_ok = true;
          TIMES(xx, m) {
            if(lawn[y][xx] != h_min) {
              x_ok = false;
            }
          }
          
          if(y_ok || x_ok) {
            
          }else {
            ok = false;
          }
        }
      }
    }
    if(ok) {
      TIMES(y, n) {
        TIMES(x, m) {
          if(lawn[y][x] == h_min) {
            lawn[y][x] += 1;
          }
        }
      }
    }else {
      return "NO";
    }
  }

  return "NO";
}

int main(int argc, char *argv[])
{

  int t;
  cin >> t;

  UPTO(tt, 1, t) {
    cout << "Case #" << tt << ": ";

    int n, m;
    cin >> n >> m;

    vector< vector<int> > lawn;
    TIMES(nn, n) {
      lawn.push_back(vector<int>());
      TIMES(mm, m) {
        int h;
        cin >> h;
        lawn[nn].push_back(h);
      }
    }
    
    cout << solve(n, m, lawn) <<  endl;
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
