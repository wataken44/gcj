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

template<typename T> vector<T> read_vector(int n);

void split(const string& s, vector<string>& v)
{
  v.clear();
  char prev = 0;

  TIMES(k, s.size()) {
    if(prev != s[k]) {
      v.push_back(string(1, s[k]));
    }else {
      v[v.size() - 1] += s[k];
    }
    prev = s[k];
  }
}

int main(int argc, char *argv[])
{
  int t;
  cin >> t;
  UPTO(tt, 1, t) {
    cout << "Case #" << tt << ": " ;

    int n;
    cin >> n;

    vector< string > in = read_vector<string>(n);
    vector< vector< string > > ss(n);
    TIMES(nn, n) {
      split(in[nn], ss[nn]);
    }
    //DUMP(ss);

    bool ok = true;
    TIMES(nn, n) {
      if(ss[nn].size() != ss[0].size()) {
        ok = false;
        break;
      }
      TIMES(k, ss[0].size()) {
        if(ss[nn][k][0] != ss[0][k][0]) { ok = false; }
      }
    }
    if(ok) {
      int r = 0;
      TIMES(k, ss[0].size()) {
        int u = 0;
        TIMES(nn, n) {
          u = max(u, (int)ss[nn][k].size());
        }
        int m = u * n + 1000000;
        UPTO(d, 1, u) {
          int y = 0;
          TIMES(nn, n) {
            y += abs((int)ss[nn][k].size() - d);
          }
          m = min(m, y);
        }
        r += m;
      }
      cout << r;
    } else {
      cout << "Fegla Won" ;
    };
    
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

template<typename T> vector<T> read_vector(int n) {
  vector<T> r(n);
  TIMES(nn, n) { T tmp; cin>>tmp; r[nn] = tmp; };
  return r;
}
