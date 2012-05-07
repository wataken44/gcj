
/*
  Cs.cpp
 */


#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

int log10i(int i)
{
  int r = 0;
  while(i >= 10) {
    ++r;
    i /= 10;
  }
  return r;
}

int rshift10(int n, int k)
{
  int rat = 1;

  for(int i = 0; i < k; ++i) {
    rat *= 10;
  }

  int r = n % rat;
  int l = n / rat;
  int c = log10i(n);

  for(int i = 0; i < c - k + 1; ++i) {
    r *= 10;
  }
  
  return r + l; 
}

int main(int argc, char *argv[])
{
  int tt = 0;
  
  string buf;

  cin >> tt;
  
  for(int t = 1; t <= tt; ++t) {
    int ret = 0;
    
    int a, b;

    cin >> a;
    cin >> b;

    for(int n = a; n <= b; ++n) {
      int l10n = log10i(n);
      vector<int> mm;
      for(int k = 0; k < l10n + 1; ++k) {
        int m = rshift10(n, k);
        if(n >= m) continue;
        if( m < a || m > b ) continue;
        if(find(mm.begin(), mm.end(), m) != mm.end()) continue;
        if(l10n != log10i(m)) continue;

        ++ret;
        mm.push_back(m);
      }
    }
              
    cout << "Case #" << t << ": " << ret << endl;
  }
  
  return 0;
}
