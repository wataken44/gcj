
/*
  A.cpp
 */

#include <algorithm>
#include <cassert>
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


int main(int argc, char *argv[])
{

  int t;
  cin >> t;
  string buf;
  getline(cin, buf);
  
  UPTO(tt, 1, t) {
    cout << "Case #" << tt<< ": ";

    vector<string> bx;
    vector<string> bo;

    TIMES(i, 4) {
      getline(cin, buf);
      bx.push_back(buf);
      bo.push_back(buf);
    }
    getline(cin, buf);

    TIMES(y, 4) {
      TIMES(x, 4) {
        if(bx[y][x] == 'T') {
          bx[y][x] = 'X';
        }
        if(bo[y][x] == 'T') {
          bo[y][x] = 'O';
        }
      }
    }

    vector<int> ret;

    TIMES(y, 4) {
      if(bx[y] == "XXXX") ret.push_back(0);
      if(bo[y] == "OOOO") ret.push_back(1);
    }

    TIMES(x, 4) {
      bool all = true;
      TIMES(y, 4) {
        if(bx[y][x] != 'X') all = false;
      }
      if(all) ret.push_back(0);
    }

    TIMES(x, 4) {
      bool all = true;
      TIMES(y, 4) {
        if(bo[y][x] != 'O') all = false;
      }
      if(all) ret.push_back(1);
    }

    bool all = true;
    TIMES(w, 4) {
      if(bx[w][w] != 'X') all = false;
    }
    if(all) ret.push_back(0);

    all = true;
    TIMES(w, 4) {
      if(bo[w][w] != 'O') all = false;
    }
    if(all) ret.push_back(1);

    all = true;
    TIMES(w, 4) {
      if(bx[w][3-w] != 'X') all = false;
    }
    if(all) ret.push_back(0);

    all = true;
    TIMES(w, 4) {
      if(bo[w][3-w] != 'O') all = false;
    }
    if(all) ret.push_back(1);
    
    all = true;
    TIMES(y, 4) {
      TIMES(x, 4) {
        if(bx[y][x] == '.') all = false;
      }
    }

    //assert(ret.size() <= 1);
    
    if(all) {
      ret.push_back(2);
    }else {
      ret.push_back(3);
    }
    
    if(ret[0] == 0) {
      cout << "X won";
    }else if(ret[0] == 1) {
      cout << "O won";
    }else if(ret[0] == 2) {
      cout << "Draw";
    }else if(ret[0] == 3) {
      cout << "Game has not completed";
    }
    
    cout << endl;
   
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
