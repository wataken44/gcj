
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

typedef long long ll;
const ll mod = 1000002013;

ll cost(ll n, ll d) {
  ll c = 0;
  if(d > 0) {
    c = ((d * n) % mod) - ((d * (d - 1) / 2) % mod);
    if(c < 0) c += mod;
  }
  return c;
}

int main(int argc, char *argv[])
{
  
  int t;
  cin >> t;

  UPTO(tt, 1, t) {
    int n, m;
    cin >> n >> m;
    vector<ll> o, e, p;
    TIMES(mm, m) {
      int oo, ee, pp;
      cin >> oo >> ee >> pp;
      o.push_back(oo);
      e.push_back(ee);
      p.push_back(pp);
    }

    // DUMP(n);DUMP(m);DUMP(o);DUMP(e);DUMP(p);
        
    ll total = 0;
    set<ll> dists;

    TIMES(mm, m) {
      ll d = e[mm] - o[mm];
      total = (total + ((p[mm] * cost(n, d)) % mod)) % mod;
      dists.insert(e[mm]);
      dists.insert(o[mm]);
    }
    ll cheat = 0;
    vector< pair<ll, ll> > ticket; // from, p
    
    EACH(dists, it) {
      ll nn = *it;
      TIMES(mm, m) {
        if(o[mm] == nn) {
          ticket.push_back(make_pair(nn, p[mm]));
        }
      }
      // DUMP(ticket);
      TIMES(mm, m) {
        if(e[mm] == nn) {
          ll pp = p[mm];
          while(pp > 0) {
            int back = ticket.size() - 1;
            ll d = nn - ticket[back].first;
            ll cc = cost(n, d); 

            // DUMP(ticket);DUMP(cheat);
            
            if(ticket[back].second > pp) {
              ticket[back].second -= pp;
              cheat = (cheat + (pp * cc) % mod) % mod;
              pp = 0;
            }else {
              cheat = (cheat + (ticket[back].second * cc) % mod) % mod;
              pp -= ticket[back].second;
              ticket.pop_back();
            }
            // DUMP(ticket);DUMP(cheat);
          }
        }
      }
    }

    // DUMP(total);
    // DUMP(cheat);
    
    ll loss = (total - cheat) % mod;
    if(loss < 0) loss += mod; 
    
    cout << "Case #" << tt << ": " << loss << endl;
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
