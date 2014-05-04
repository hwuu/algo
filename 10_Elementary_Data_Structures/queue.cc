//
// Chapter 10. Elementary Data Structures
//
// Queue Implementation using Linked List
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
struct QueueElem
{
  T x;
  QueueElem* prev;
  QueueElem* next;
};

//
///
//

template<class T>
class Queue
{
public:
  Queue();
  ~Queue();
  //
  void Push(const T& x);
  const T& Top() const;
  void Pop();
  int Size() const;
private:
  QueueElem<T>* head_;
  QueueElem<T>* tail_;
  int n_;
};

//

template<class T>
Queue<T>::Queue()
{
  head_ = new QueueElem<T>();
  tail_ = new QueueElem<T>();
  head_->prev = NULL;
  head_->next = tail_;
  tail_->prev = head_;
  tail_->next = NULL;
  n_ = 0;
}

//

template<class T>
Queue<T>::~Queue()
{
  while (n_ > 0) {
    Pop();
  }
  delete head_;
  delete tail_;
}

//

template<class T>
void Queue<T>::Push(const T& x)
{
  QueueElem<T>* p = new QueueElem<T>();
  p->x = x;
  p->prev = head_;
  p->next = head_->next;
  p->prev->next = p;
  p->next->prev = p;
  n_++;
}

//

template<class T>
const T& Queue<T>::Top() const
{
  return tail_->prev->x;
}

//

template<class T>
void Queue<T>::Pop()
{
  if (n_ == 0) {
    return;
  }
  QueueElem<T>* p = tail_->prev;
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  n_--;
}

//

template<class T>
int Queue<T>::Size() const
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
  Queue<int> q;
  for (int i = 0; i < n; i++) {
    q.Push(a[i]);
  }
  while (q.Size() > 0) {
    int x = q.Top();
    cout << x << endl;
    q.Pop();
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

