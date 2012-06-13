
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
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <time.h>

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

static const double EPS = 1e-4;

struct Person {
  int i;
  int r;
  double y;
  double x;
};

class IComp {
 public:
  IComp(){};
  bool operator()(const Person& lhs, const Person& rhs)
  {
    return lhs.i < rhs.i;
  }
};

class RComp {
 public:
  RComp(){};
  bool operator()(const Person& lhs, const Person& rhs)
  {
    return lhs.r > rhs.r;
  }
};

double drand()
{
  return rand() * 1.0 / ((unsigned long long)RAND_MAX + 1ULL);
}

double dist(double y0, double x0, double y1, double x1)
{
  double xx = x1 - x0;
  double yy = y1 - y0;
  return sqrt(yy * yy + xx * xx);
}

int nearest(int k, vector<Person>& p)
{
  int mi = k;
  double md = DBL_MAX;

  FOR(i, 0, k) {
    double d = dist(p[i].y, p[i].x, p[k].y, p[k].x);
    if(d < p[i].r + p[k].r + EPS) return -1;

    if(md < d) {
      mi = i;
      md = d;
    }
  }
  return mi;
}

void place(int k, int w, int l, vector<Person>& p)
{
  double xx = w * drand();
  double yy = l * drand();
  int ni = -1;
  
  while(true) {
    p[k].x = xx;
    p[k].y = yy;

    ni = nearest(k, p);
    if(ni != -1) break;
    xx = w * drand();
    yy = l * drand();
  }
}

string solve(int n, int w, int l, vector<int> r)
{  
  srand(time(0));
  
  vector<Person> p;
  TIMES(i, n) {
    Person pp = {i, r[i], 0, 0};
    p.push_back(pp);
  }

  sort(p.begin(), p.end(), RComp());

  p[0].x = 0;
  p[0].y = 0;

  FOR(k, 1, n) {
    place(k, w, l, p);
  }

  sort(p.begin(), p.end(), IComp());

  /*
  cout.setf(std::ios_base::fixed);
  DUMP(w);DUMP(l);
  TIMES(i, n) {
    cout << p[i].i << " " << p[i].r << " " << p[i].x << " " << p[i].y << endl;
  }
  TIMES(i, n) {
    FOR(k, i + 1, n) {
      if(i == k) continue;
      double d = dist(p[i].y, p[i].x, p[k].y, p[k].x);
      if(d < p[i].r + p[k].r + EPS) {
        cout << "NG: " << i << " " << k << " " << d << " " << p[i].r + p[k].r << endl;
        cout << p[i].i << " " << p[i].r << " " << p[i].x << " " << p[i].y << endl;
        cout << p[k].i << " " << p[k].r << " " << p[k].x << " " << p[k].y << endl;
        
      }
    }
  }
  */
  
  ostringstream oss;

  oss.setf(std::ios_base::fixed);
  TIMES(i, n) {
    oss << p[i].x << " " << p[i].y ;
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
