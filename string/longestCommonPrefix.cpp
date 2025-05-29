#include <bits/stdc++.h>

using namespace std;

string longestCommonPrefix(const vector<string> &strs) {
  string ans;
  if (strs.empty())
    return ans;
  int i = 0;
  while (true) {
    for (const string &str : strs) {
      if (i >= str.size() || str[i] != strs[0][i])
        return ans;
    }
    ans += strs[0][i++];
  }
}
