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

int main(int argc, char *argv[])
{
  int t;
  cin >> t;
  TIMES(tt, t) {
    cout << "Case #" << tt + 1 << ": " ;
    int n, l;
    cin >> n >> l;

    vector<string> ini = read_vector<string>(n);
    vector<string> rec = read_vector<string>(n);

    sort(ini.begin(), ini.end());

    int r = l + 100;

    TIMES(nn, n) {
      list<string> win;
      win.push_back(ini[nn]);
      TIMES(kk, n) {
        if(kk != nn) {
          win.push_back(ini[kk]);
        }
      };
      list<string> wre(rec.begin(), rec.end());
      //DUMP(win); DUMP(wre); 

      string fin = win.front();win.pop_front();
      string fre = wre.front();wre.pop_front();

      unsigned long long mask = 0;
      //DUMP(ini); DUMP(rec);
      TIMES(ll, l) {
        if(fin[ll] != fre[ll]) {
          mask = mask | (1ULL << ll);
        }
      }
      //DUMP(mask);

      while(!win.empty()) {
        string in = win.front();
        win.pop_front();

        string dest = in;
        TIMES(ll, l) {
          if( 0 < (mask & (1ULL << ll)) ) {
            // should be different
            dest[ll] = (in[ll] == '0' ? '1' : '0');
          }
        }
        //DUMP(in); DUMP(dest);

        list<string>::iterator it = find(wre.begin(),wre.end(),dest);
        if(it != wre.end()) {
          wre.erase(it);
        }else {
          break;
        }
        
      }


      if(wre.empty()) {
        int rr = 0;
        TIMES(ll, l) {
          if(fin[ll] != fre[ll]) {
            ++rr;
          }
        }
        r = min(r, rr);
      }
      
    }
    
    if(r > l) {
      cout << "NOT POSSIBLE";
    }else {
      cout << r;
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

template<typename T> vector<T> read_vector(int n) {
  vector<T> r(n);
  TIMES(nn, n) { T tmp; cin>>tmp; r[nn] = tmp; };
  return r;
}
