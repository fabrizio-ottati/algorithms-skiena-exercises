#include <iostream>
#include <map>
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
    if (openPars.find(par) != std::string::npos) {
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
