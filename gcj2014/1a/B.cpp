
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

template<typename T> vector<T> read_vector(int n);

bool is_binary_tree(int n, vector<int> x, vector<int> y, int mask)
{
  vector<int> node;
  list< pair<int, int> > edge;
  TIMES(i, x.size()) {
    if( (mask & (1 << x[i])) == 0 && (mask & (1 << y[i])) == 0 ) {
      edge.push_back(make_pair(x[i], y[i]));
    }
  }
  TIMES(i, n) {
    if((mask & (1 << i)) == 0) {
      node.push_back(i);
    }
  }
  //cout << "" << endl ;
  //DUMP(x); DUMP(y); DUMP(mask);DUMP(node);DUMP(edge);
  
  vector<int> ne(n, 0);
  EACH(edge, e) {
    ++ne[ e->first ];
    ++ne[ e->second ];
  };
  
  int head = -1;
  TIMES(i, n) {
    if(ne[i] == 2) {
      if(head != -1) { return false; }
      head = i;
    }
  }
  if(head == -1) { return false; };
  //DUMP(head);

  vector<int> used(n, 0);
  TIMES(i, n) {
    if( (mask & (1 << i)) != 0 ) { used[i] = 1; }
  }

  list<int> queue;
  queue.push_back(head);
  while(!queue.empty()) {
    int front = queue.front();
    queue.pop_front();
    used[front] = 1;
    
    int cnt = 0;
    EACH(edge, e) {
      if(e->first == front || e->second == front) {
        ++cnt;
      }
    }
    //DUMP(front);DUMP(cnt);DUMP(edge);
    if(!(cnt == 0 || cnt == 2)) {
      return false;
    }
    for(typename list< pair<int, int> >::iterator e = edge.begin(); e != edge.end();) {
      if(e->first == front || e->second == front) {
        if(e->first != front) {
          queue.push_back(e->first);
        }else {
          queue.push_back(e->second);
        }
        e = edge.erase(e);
      }else {
        ++e;
      }
    }
  }

  TIMES(i, used.size()) {
    if(used[i] == 0) { return false; }
  }
  
  return true;
}

int main(int argc, char *argv[])
{
  int t;
  cin >> t;

  UPTO(tt, 1, t) {
    cout << "Case #" << tt << ": " ;
    int n;
    cin >> n;
    int r = n;
    vector<int> x, y;
    TIMES(nn, n-1) {
      int xi, yi;
      cin >> xi>> yi;
      x.push_back(xi-1); y.push_back(yi-1);
    }
    TIMES(m, 1 << n) {
      bool can = is_binary_tree(n, x, y, m);
      if(can) {
        int c = 0;
        int mm = m;
        while(mm > 0) {
          c += (mm & 1);
          mm /= 2;
        }
        r = min(c, r);
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
