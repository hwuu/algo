//
// Chapter 10. Elementary Data Structures
//
// Stack Implementation using Linked List
//
// Hao Wu, 05/04/2014
//

#include <iostream>
//
using namespace std;

//
///
//

template<class T>
struct StackElem
{
  T x;
  StackElem* prev;
  StackElem* next;
};

//
///
//

template<class T>
class Stack
{
public:
  Stack();
  ~Stack();
  //
  void Push(const T& x);
  const T& Top() const;
  void Pop();
  int Size() const;
private:
  StackElem<T>* head_;
  StackElem<T>* tail_;
  int n_;
};

//

template<class T>
Stack<T>::Stack()
{
  head_ = new StackElem<T>();
  tail_ = new StackElem<T>();
  head_->prev = NULL;
  head_->next = tail_;
  tail_->prev = head_;
  tail_->next = NULL;
  n_ = 0;
}

//

template<class T>
Stack<T>::~Stack()
{
  while (head_->next != tail_) {
    Pop();
  }
  delete head_;
  delete tail_;
}

//

template<class T>
void Stack<T>::Push(const T& x)
{
  StackElem<T>* p = new StackElem<T>();
  p->x = x;
  p->prev = tail_->prev;
  p->next = tail_;
  p->prev->next = p;
  p->next->prev = p;
  n_++;
}

//

template<class T>
const T& Stack<T>::Top() const
{
  return tail_->prev->x;
}

//

template<class T>
void Stack<T>::Pop()
{
  if (n_ == 0) {
    return;
  }
  StackElem<T>* p = tail_->prev;
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  n_--;
}

//

template<class T>
int Stack<T>::Size() const
{
  return n_;
}

//
///
//

int main()
{
  int n = 7;
  int a[] = {1, 7, 3, 5, 9, 4, 8};
  Stack<int> s;
  for (int i = 0; i < n; i++) {
    s.Push(a[i]);
  }
  while (s.Size() > 0) {
    int x = s.Top();
    cout << x << endl;
    s.Pop();
  }
}

//
///
////
///
//
//
///
////
///
//
//
///
////
///
//
//
///
////
///
//

