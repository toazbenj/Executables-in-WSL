#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::tolower;

// Makes string all lowercase
string LowerStr(string input_str) {
  string build_str = "";
  for (auto ch : input_str) build_str += tolower(ch);

  return build_str;
}

// Compares each char inside text and pattern strings, handles % and # cases
bool SpecialFind(string text_str, string pattern_str) {
  for (int i = 0; i < (int)text_str.size(); i++) {
    for (int j = 0; j < (int)pattern_str.size(); j++) {

      // Error catching for maxing out text_str index
      if (i > (int)text_str.size() - 1) {
        return false;
      }

      bool is_number_wild_match =
          (pattern_str.at(j) == '#' && isdigit(text_str.at(i)));

      // If no match, check next char
      if (text_str.at(i) != pattern_str.at(j) && pattern_str.at(j) != '%' &&
          not is_number_wild_match) {
        break;
      }

      // Match found at all pattern indices => pattern found
      if (j == (int)pattern_str.size() - 1) {
        return true;
      }

      // if char is match, check next char in text and pattern
      i++;
    }
  }
  // No matches
  return false;
}

bool ImprovedContains(const string& text_str, const string& pattern_str,
                      const bool* is_case_insensitive) {

  string text_formatted_str = text_str;
  string pattern_formatted_str = pattern_str;

  if (*is_case_insensitive) {
    text_formatted_str = LowerStr(text_str);
    pattern_formatted_str = LowerStr(pattern_str);
  }

  if (SpecialFind(text_formatted_str, pattern_formatted_str))
    return true;
  else
    return false;
}

int ImprovedFindFirstOf(const string& text_str, const string& pattern_str,
                        const bool* is_case_insensitive) {

  string check_str = text_str;
  for (int i = 0; i < (int)text_str.size(); i++) {
    if (ImprovedContains(check_str.substr(0, (int)pattern_str.size()),
                         pattern_str, is_case_insensitive))
      return i;
    else
      check_str = check_str.substr(1, (int)check_str.size());
  }

  // No matches
  return -1;
}

int ImprovedMatches(const string& text_str, const string& pattern_str,
                    const bool* is_case_insensitive) {

  int pattern_cnt = 0;
  string check_str = text_str;
  for (int i = 0; i < (int)text_str.size(); i++) {
    if (ImprovedContains(check_str.substr(0, (int)pattern_str.size()),
                         pattern_str, is_case_insensitive))
      pattern_cnt++;

    // Guard against bad indexing after substr creation
    if ((int)check_str.size() < (int)pattern_str.size()) break;

    check_str = check_str.substr(1, (int)check_str.size());
  }

  return pattern_cnt;
}

void ImprovedReplace(string& text_str, const string& pattern_str,
                     const string& replace_str,
                     const bool* is_case_insensitive) {

  for (int i = 0;
       i < ImprovedMatches(text_str, pattern_str, is_case_insensitive); i++) {

    if (ImprovedFindFirstOf(text_str, pattern_str, is_case_insensitive) != -1) {
      int index =
          ImprovedFindFirstOf(text_str, pattern_str, is_case_insensitive);

      text_str = text_str.erase(
          ImprovedFindFirstOf(text_str, pattern_str, is_case_insensitive),
          pattern_str.length());

      text_str = text_str.insert(index, replace_str);
    }
  }
}

int ImprovedNumberOfDifferences(const string& str1, const string& str2,
                                const bool & is_case_insensitive) {

  int diff_cnt = 0;
  for (int i = 0; i < (int)str1.size(); i++) {
    string test1_str = "";
    string test2_str = "";

    test1_str += str1.at(i);
    test2_str += str2.at(i);

    if (not ImprovedContains(test1_str, test2_str, &is_case_insensitive)) {
      diff_cnt++;
    }
  }

  if (str1.size() != str2.size())
    diff_cnt += abs((int)str1.size() - (int)str2.size());

  return diff_cnt;
}

int main() {
  // Test inputs
  string text_str = "fnlaieualb?78";
  string pattern_str = "aie";
  bool is_case_insensitive = false;

  string replace_str = "aieou!";
  string str1 = "test1";
  string str2 = "Tes%#";

  // Test Outputs
  cout << std::boolalpha;
  cout << "ImprovedContains: "
       << ImprovedContains(text_str, pattern_str, &is_case_insensitive) << endl;

  cout << "ImprovedMatches: "
       << ImprovedMatches(text_str, pattern_str, &is_case_insensitive) << endl;

  cout << "ImprovedFindFirstOf: "
       << ImprovedFindFirstOf(text_str, pattern_str, &is_case_insensitive)
       << endl;

  ImprovedReplace(text_str, pattern_str, replace_str, &is_case_insensitive);
  cout << "ImprovedReplace: " << text_str << endl;

  cout << "ImprovedNumberOfDifferences: "
       << ImprovedNumberOfDifferences(str1, str2, &is_case_insensitive) << endl;

  return 0;
}