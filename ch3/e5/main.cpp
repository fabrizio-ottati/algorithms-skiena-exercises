/*
 * We have seen how dynamic arrays enable arrays to grow while still achiev- ing
 * constant-time amortized performance. This problem concerns extending dynamic
 * arrays to let them both grow and shrink on demand.
 *
 * (a) Consider an underflow strategy that cuts the array size in half whenever
 * the array falls below half full. Give an example sequence of insertions and
 * deletions where this strategy gives a bad amortized cost.
 *
 * (b) Then, give a better underflow strategy than that suggested above, one
 * that achieves constant amortized cost per deletion.
 */

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>

using namespace std;

template <typename T> class Vector {
public:
  Vector(int64_t n = 1024) : _size(n), _capacity(n) {
    _data = (T *)malloc(sizeof(T) * n);
    if (_data == nullptr)
      throw runtime_error("ERROR: Could not allocate the vector.");
  }
  ~Vector(void) { free(_data); }

  virtual void pop_back(void) = 0;

  void push_back(T val) {
    if (_size + 1 >= _capacity) {
      _capacity *= 2;
      _data = (T *)realloc(_data, sizeof(T) * _capacity);
      if (_data == nullptr)
        throw runtime_error("ERROR: Could not enlarge the vector.");
      _data[_size++] = val;
    }
  }

  T operator[](int64_t i) const { return _data[i]; }
  T &operator[](int64_t i) { return _data[i]; }

protected:
  T *_data = nullptr;
  int64_t _size, _capacity;
};

template <typename T> class DumbVector : public Vector<T> {
  void pop_back(void) {
    this->_size--;
    if (this->_size < this->_capacity / 2) {
      this->_capacity /= 2;
      this->_data = (T *)realloc(this->_data, sizeof(T) * this->_capacity);
      if (this->_data == nullptr)
        throw runtime_error("ERROR: Could not shrink the vector.");
    }
  }
};

template <typename T> class SmartVector : public Vector<T> {
  void pop_back(void) {
    this->_size--;
    // We shrink only if _size < _capacity / 4, so that we do not enlarge and
    // shrink the vector when we perform multiple push_back and pop_back
    // one after the other.
    if (this->_size < this->_capacity / 4) {
      this->_capacity /= 4;
      this->_data = (T *)realloc(this->_data, sizeof(T) * this->_capacity);
      if (this->_data == nullptr)
        throw runtime_error("ERROR: Could not shrink the vector.");
    }
  }
};

int main(void) {
  SmartVector<int> smart;
  DumbVector<int> dumb;
  return 0;
}
