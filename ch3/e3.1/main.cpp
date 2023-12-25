/*
 * A common problem for compilers and text editors is determining whether the
 * parentheses in a string are balanced and properly nested. For example, the
 * string ((())())() contains properly nested pairs of parentheses, while the
 * strings )()( and ()) do not. Give an algorithm that returns true if a string
 * contains properly nested and balanced parentheses, and false if otherwise.
 * For full credit, identify the position of the first offending parenthesis if
 * the string is not properly nested and balanced.
 */

#include <exception>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(const string &str);

int main(void) {
  const string strs[]{{"[()]()"}, {"({)))("}, {"(())[("}, {"[()]{}{[()()]()}"}};
  for (auto &str : strs) {
    cout << string(80, '-') << endl;
    if (isBalanced(str))
      cout << "\"" + str + "\" -> OK." << endl;
    else
      cout << "\"" + str + "\" -> Not OK." << endl;
  }

  return 0;
}

bool isBalanced(const string &str) {
  stack<char> S;
  const string openPars{"{[("}, closePars{"}])"};

  for (auto par : str) {
    if (openPars.find(par) != string::npos ||
        closePars.find(par) != string::npos)
      throw invalid_argument(
          "ERROR: The string must contain only parentheses.");
    if (openPars.find(par) != string::npos) {
      S.push(par);
    } else {
      if (S.empty()) {
        cerr << "String is not balanced at position " << str.find(par) << "."
             << endl;
        return false;
      } else if (S.top() != openPars[closePars.find(par)]) {
        cerr << "String is not balanced at position " << str.find(par) << "."
             << endl;
        return false;
      }
      S.pop();
    }
  }
  if (!S.empty()) {
    cerr << "String is not balanced at position " << str.size() - S.size()
         << "." << endl;
    return false;
  }
  return true;
}
