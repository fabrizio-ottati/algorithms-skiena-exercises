/*
 * Design a stack S that supports S.push(x), S.pop(), and S.findmin(), which
 * returns the minimum element of S. All operations should run in constant
 * time.
 */

#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

template <typename T> class FastStack {
public:
  T top(void) const { return _data.top(); }

  T findmin(void) const { return _mins.top(); }

  void push(T val) {
    if (_data.empty()) {
      _data.push(val);
      _mins.push(val);
    } else {
      if (val < _mins.top())
        _mins.push(val);
      _data.push(val);
    }
    return;
  }

  void pop(void) {
    if (_data.top() == _mins.top())
      _mins.pop();
    _data.pop();
    return;
  }

  bool empty(void) const { return _data.empty(); }

  stack<T>::size_type size(void) { return _data.size(); }

private:
  stack<T> _data, _mins;
};

int main(void) {
  FastStack<int> S;
  const int vals[]{1, 2, 3, -5, 4, 5, 6, -7, 7, 8, 80, -1, 2, 3};
  for (auto val : vals) {
    S.push(val);
    cout << "Pushed " << val << ", the minimum is " << S.findmin() << "."
         << endl;
  }
  cout << endl;
  while (!S.empty()) {
    cout << "Popping " << S.top() << ", with the minimum being " << S.findmin()
         << "." << endl;
    S.pop();
  }
  return 0;
}
