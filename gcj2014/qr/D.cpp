
/*
  D.cpp
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

int dec_war(list<double> p0, list<double> p1)
{
  p0.sort();
  p1.sort();

  int s0 = 0;
  int s1 = 0;

  while(!p0.empty()) {
    if(p0.front() <= p1.front()) {
      p0.pop_front();
      p1.pop_back();
      s1 += 1;
    }else {
      p0.pop_front();
      p1.pop_front();
      s0 += 1;
    }
  }
  return s0;
}

int war(list<double> p0, list<double> p1)
{
  p0.sort();
  p1.sort();

  int s0 = 0;
  int s1 = 0;

  while(!p0.empty()) {
    /*
    double w0 = p0.front();
    p0.pop_front();
    */
    double w0 = p0.back();
    p0.pop_back();

    
    list<double>::iterator it = upper_bound(p1.begin(), p1.end(), w0);
    if(it == p1.end()) {
      s0 += 1;
      p1.pop_front();
    }else {
      s1 += 1;
      p1.erase(it);
    }
  }
  return s0;
}

int main(int argc, char *argv[])
{
  int t = 0;
  cin >> t;

  UPTO(tt, 1, t) {
    cout << "Case #" << tt << ": ";

    int n = 0;
    cin >> n;
    list<double> nao;
    list<double> ken;

    TIMES(nn, n) {
      double tmp;
      cin >> tmp;
      nao.push_back(tmp);
    }
    TIMES(nn, n) {
      double tmp;
      cin >> tmp;
      ken.push_back(tmp);
    }

    int y = dec_war(nao, ken);
    int z = war(nao, ken);

    cout << y << " " << z << endl;
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
