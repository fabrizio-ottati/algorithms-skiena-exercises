/*
 * Give an algorithm to reverse the direction of a given singly linked list. In
 * other words, after the reversal all pointers should now point backwards. Your
 * algorithm should take linear time.
 */

#include <iostream>
#include <string>

using namespace std;

struct Node {
  Node(int data = 0, Node *next = nullptr) : data(data), next(next) {}

  int data;
  Node *next;
};

class List {

public:
  List(void) : _head(nullptr) {}

  ~List(void) { _deleteList(_head); }

  void pop(void) {
    if (_head == nullptr)
      return;

    auto pt = _head, ptPrev = _head;
    for (; pt->next != nullptr; ptPrev = pt, pt = pt->next)
      ;
    delete pt;
    ptPrev->next = nullptr;
    return;
  }

  void push(int data) {
    if (_head == nullptr) {
      _head = new Node{data, nullptr};
      return;
    }

    // Traverse the list until the end.
    auto pt = _head;
    for (; pt->next != nullptr; pt = pt->next)
      ;
    // Append node.
    pt->next = new Node{data, nullptr};
    return;
  }

  void print(void) {
    for (auto pt = _head; pt != nullptr; pt = pt->next)
      cout << pt->data << (pt->next == nullptr ? "." : " -> ");
    cout << endl;
    return;
  }

  void reverse(void) {
    auto oldHead = _reverse(_head);
    // The old _head becomes the last node.
    oldHead->next = nullptr;
  }

private:
  void _deleteList(Node *pt) {
    if (pt == nullptr)
      return;
    _deleteList(pt->next);
    delete pt;
  }

  Node *_reverse(Node *pt) {
    // Reaching last node.
    if (pt->next == nullptr) {
      // Old last node is the new _head.
      _head = pt;
      return pt;
    }
    auto nextPt = _reverse(pt->next);
    // Revert nodes connection.
    nextPt->next = pt;
    return pt;
  }

  Node *_head;
};

constexpr auto N = 20;

int main(void) {

  // Creating a list.
  List L;

  for (auto i = 0; i < N; i++)
    L.push(i);
  L.print();

  cout << string(80, '-') << "\nReverting the list...\n"
       << string(80, '-') << endl;
  L.reverse();
  L.print();
}
