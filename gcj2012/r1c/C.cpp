
/*
  C.cpp
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

typedef pair<ll, ll> pll;

map<pll, ll> memo;

vector<ll> ga;
vector<ll> gA;
vector<ll> gb;
vector<ll> gB;

ll lcs(
    vector<ll> a, vector<ll> A, vector<ll> b, vector<ll> B)
{
  int n = a.size();
  int m = b.size();

  if(n == 0 || m == 0) return 0;

  pll key = make_pair(n, m);
  
  bool memoable = false;
  
  if(ga[n - 1] == a[n - 1] && gb[m - 1] == b[m - 1]) {
    memoable = true;

    if(memo.find(key) != memo.end()) {
      return memo[key];
    }
  }
  
  ll r = 0;
  if(A.back() == B.back()) {
    if(a.back() < b.back()) {
      b.back() = b.back() - a.back();
      r += a.back();
      a.pop_back();
      A.pop_back();
      r += lcs(a, A, b, B);
    }else if(a.back() > b.back()) {
      a.back() = a.back() - b.back();
      r += b.back();
      b.pop_back();
      B.pop_back();
      r += lcs(a, A, b, B);
    }else {
      r += b.back();
      a.pop_back();
      A.pop_back();
      b.pop_back();
      B.pop_back();
      r += lcs(a, A, b, B);
    }
  }else {
    vector<ll> aa(a);
    vector<ll> AA(A);
    aa.pop_back();
    AA.pop_back();
        
    vector<ll> bb(b);
    vector<ll> BB(B);
    bb.pop_back();
    BB.pop_back();

    r += max(lcs(a, A, bb, BB), lcs(aa, AA, b, B));
  }

  if(memoable) {
    memo[key] = r;
  }
  
  return r;
}

int main(int argc, char *argv[])
{

  int tt;
  cin >> tt;

  TIMES(ttt, tt) {
    int n, m;
    cin >> n;
    cin >> m;

    vector<ll> a;
    vector<ll> A;
    TIMES(k, n) {
      ll t, u;
      cin >> t >> u;
      a.push_back(t);
      A.push_back(u);
    }

    vector<ll> b;
    vector<ll> B;
    TIMES(k, m) {
      ll t, u;
      cin >> t >> u;
      b.push_back(t);
      B.push_back(u);
    }

    // DUMP(a);DUMP(A);DUMP(b);DUMP(B);

    memo.clear();
    ga = a;
    gA = A;
    gb = b;
    gB = B;
    ll r = lcs(a, A, b, B);
    
    cout << "Case #" << ttt + 1 << ": " << r << endl;
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
