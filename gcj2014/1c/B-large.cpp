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

bool is_valid(string& tr)
{
  vector<int> oc(256, 0);

  char prev = ' ';
  TIMES(k, tr.size()) {
    if(prev != tr[k]) {
      if(oc[tr[k]] != 0) {
        // second occurence
        return false;
      }
      oc[tr[k]] = 1;
    }
    prev = tr[k];
  }
  
  return true;
}

/*
  vector of
    map< pair<start char, end char>, pair<mid_vec(ull), count> >
 */

typedef unsigned long long ull;
typedef pair<char, char> key_type;
typedef pair<ull, ull> val_type;
typedef map<key_type, val_type> dp_type;

const long long mod = 1000000007LL;

ull mask(char c) {
  return 1ULL << (c - 'a');
}

ull mid_info(string& train)
{
  ull r = 0;
  int sz = train.size();
  TIMES(k, sz) {
    if(train[k] != train[0] && train[k] != train[sz-1]) {
      r = r | mask(train[k]);
    }
  }
  return r;
}

bool is_connectable(char s0, ull m0, char e0, char s1, ull m1, char e1)
{
  if( m0 & mask(s1) ) { return false; }
  if( m0 & mask(e1) ) { return false; }
  if( m1 & mask(s0) ) { return false; }
  if( m1 & mask(e0) ) { return false; }
  if( m0 & m1 ) { return false; };
  if( s0 == e1 ) {
    if( s0 == e0 && m0 == 0 && s1 == s0 && m1 == 0) {
      return true;
    }else {
      return false;
    }
  }
  return true;
}

ull connect(char s0, ull m0, char e0, char s1, ull m1, char e1)
{
  ull r = m0 | m1 | mask(e0) | mask(s1);
  r = r & (~mask(s0));
  r = r & (~mask(e1));
  return r;
}

int main(int argc, char *argv[])
{
  int t;
  cin >> t;

  UPTO(tt, 1, t) {
    cout << "Case #" << tt << ": " ;

    int n;
    cin >> n;
    vector<string> train = read_vector<string>(n);
    sort(train.begin(), train.end());
    //DUMP(train);
    long long r = 0;
    ALL(train, it, is_valid(*it), ok) ;
    if(ok) {
      vector<dp_type> dp(n);
      char s0 = train[0][0];
      char e0 = train[0][train[0].size() - 1];
      dp[0][make_pair(s0,e0)] = make_pair(mid_info(train[0]), 1);

      UPTO(nn, 1, n - 1) {
        char sn = train[nn][0];
        char en = train[nn][train[nn].size() - 1];
        ull mn = mid_info(train[nn]);

        //DUMP(dp[nn-1]);
        
        EACH(dp[nn-1], it) {
          char sp = it->first.first;
          char ep = it->first.second;
          ull mp = it->second.first;

          ull cp = it->second.second;

          //DUMP(sn);DUMP(en);DUMP(mn);
          //DUMP(sp);DUMP(ep);DUMP(mp);
          //DUMP(is_connectable(sn, mn, en, sp, mp, ep));
          //DUMP(is_connectable(sp, mp, ep, sn, mn, en));
          if(is_connectable(sn, mn, en, sp, mp, ep)) {
            char sc = sn;
            char ec = ep;
            ull mc = connect(sn, mn, en, sp, mp, ep);
            pair<char, char> key = make_pair(sc, ec);
            if(dp[nn].find(key) == dp[nn].end()) {
              dp[nn][key] = make_pair(mc, 0);
            }
            dp[nn][key].second = (dp[nn][key].second + cp) % mod;
          }


          if(is_connectable(sp, mp, ep, sn, mn, en)) {
            if(!(sn == sp && ep == en)) {
              char sc = sp;
              char ec = en;
              ull mc = connect(sp, mp, ep, sn, mn, en);
              pair<char, char> key = make_pair(sc, ec);
              if(dp[nn].find(key) == dp[nn].end()) {
                dp[nn][key] = make_pair(mc, 0);
              }
              dp[nn][key].second = (dp[nn][key].second + cp) % mod;
            }
          }

        }
      }
      EACH(dp[n-1], it) {
        r = ((r % mod) + (it->second.second % mod) % mod);
      }
      //DUMP(dp[n-1]);
    }
    //DUMP(r);

    map<string, int> cnt;
    TIMES(k, n) {
      if( cnt.find(train[k]) == cnt.end()) {
        cnt[train[k]] = 0;
      }
      ++cnt[train[k]];
    }
    EACH(cnt, it) {
      UPTO(j, 1, it->second) {
        r = ((r % mod) * (j % mod)) % mod;
      }
    }
    cout << r << endl;
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
