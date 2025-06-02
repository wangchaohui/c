#include <bits/stdc++.h>

using namespace std;

class Manacher {
public:
  explicit Manacher(const string &s)
      : s_(s), ps_(PreProcess(s)), lps_(ps_.size()) {
    int center = 1;
    int right_boundary = 1;

    for (int i = 2; i < ps_.size() - 2; i++) {
      // Check if we can expand LPS using existing information
      if (i < right_boundary) {
        // Mirror index from the current center
        const int mirror_index = 2 * center - i;
        lps_[i] = min(right_boundary - i, lps_[mirror_index]);
      }

      // Expand from the current center for odd length palindromes
      while (ps_[i + lps_[i] + 1] == ps_[i - lps_[i] - 1])
        lps_[i]++;

      // Update center and rightBoundary if a longer LPS is found
      if (i + lps_[i] > right_boundary) {
        center = i;
        right_boundary = i + lps_[i];
      }
    }
  }

  /** Find the longest palindrome in the original string */
  [[nodiscard]] string FindLongestPalindrome() const {
    const int center_index =
        max_element(lps_.begin(), lps_.end()) - lps_.begin();
    return FindLongestPalindrome(center_index);
  }

  /**
   * Find the longest palindrome in the original string with
   * [centerIndex].
   *
   *                 0     1     2     3     4     5     6     7
   *                 a     b     c     d     e     f     g     h
   * [centerIndex]   2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
   */
  [[nodiscard]] string FindLongestPalindrome(const int center_index) const {
    const int max_length = lps_[center_index];
    const int start = (center_index - max_length - 1) / 2;
    return s_.substr(start, max_length);
  }

private:
  const string &s_; // Reference to the original string
  string ps_;       // Processed string with sentinels and separators

  // Array to store the length of LPS centered at each position in ps_
  vector<int> lps_;

  static string PreProcess(const string &s) {
    string processed_string;
    processed_string.reserve(2 * s.length() + 3);
    processed_string += '^'; // Sentinel character at the start
    processed_string += '#';
    for (const char c : s) {
      processed_string += c;
      processed_string += '#';
    }
    processed_string += '$'; // Sentinel character at the end
    return processed_string;
  }
};
