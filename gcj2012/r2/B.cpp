
/*
  B.cpp
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

string solve(int n, int w, int l, vector<int> r)
{

  bool swapped = false;
  if(w < l) {
    swap(w, l);
    swapped = true;
  }
  
  vector<int> x(n);
  vector<int> y(n);

  vector<int> order(n);

  TIMES(x, n) {
    int c = 0;
    FOR(y, 0, n) {
      if(r[x] < r[y] || (r[x] == r[y] && x < y)) {
        ++c;
      }
    }
    order[x] = c;
  }

  int k0 = order[0];
  x[k0] = 0;
  y[k0] = 0;

  int cx = r[k0];
  int cy = 0;

  vector<int> left;
  left.push_back(0);
  
  FOR(i, 1, n) {
    int k = order[i];

    int xx = cx + r[k];
    if(xx <= w) {
      x[k] = xx;
      cx = x[k] + r[k];
    }else {
      x[k] = 0;
      cx = 0;
      cy = 1;
      left.push_back(i);
    }

    if(cy == 0) {
      y[k] = 0;
    }else {

      
      FOR(t, left[left.size() - 2], left.back()) {
        int kk = order[t];
        
        if(x[kk] == 0) {
          if(x[kk] - r[kk] <= x[k] && x[kk] + r[kk] >= x[k]) {
            y[k] = y[kk] + r[kk] + r[k];
            break;
          }
        } else {
          // DUMP(k); DUMP(x[k]);
          // DUMP(kk); DUMP(x[kk]); DUMP(y[kk]); DUMP(r[kk]);
          if(x[kk] - r[kk] <= x[k] && x[kk] + r[kk] >= x[k]) {
            int kkk = order[t-1];
            if(x[kkk] + r[kkk] <= x[k] + r[k]) {
              y[k] = y[kk] + r[kk] + r[k];
            }else {
              y[k] = y[kkk] + r[kkk] + r[k];
            }
            
            break;
          }
        }
      }
    }
  }

  ostringstream oss;

  if(swapped) swap(w, l);
  
  TIMES(i, n) {
    if(swapped) {
      swap(x[i], y[i]);
    }
    oss << x[i] << " " << y[i] ;
    if(w < x[i] || l < y[i]) {
      DUMP(w);DUMP(l);DUMP(x);DUMP(y);DUMP(r);
    }
    if(i != n-1 ) oss << " "; 
  }
  
  return oss.str();
}

int main(int argc, char *argv[])
{

  int t;
  cin >> t;

  UPTO(tt, 1, t) {

    int n, w, l;
    cin >> n >> w >> l;

    vector<int> r;
    TIMES(k, n) {
      int rr;
      cin >> rr;
      r.push_back(rr);
    }
    
    cout << "Case #" << tt << ": " << solve(n, w, l, r) << endl;

    
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
