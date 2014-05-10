//
// Chapter 12. Binary Search Trees
//
// Implementation of a Binary Search Tree
//
// Hao Wu, 05/10/2014
//

#include <iostream>
#include <string>
//
using namespace std;

//
///
//

template<class K, class V>
struct Node
{
  K           key;
  V           value;
  Node<K, V>* p_left_child;
  Node<K, V>* p_right_child;
  Node<K, V>* p_parent;
};

//

template<class K, class V>
class BinarySearchTree
{
public:
  BinarySearchTree();
  ~BinarySearchTree();
  void Add(const K& key, const V& value);
  void Remove(const K& key);
  void Find(const K& key, V** pp_value) const;
private:
  //void Destory(Node<K, V>* p_node);
  Node<K, V>* Minimum(Node<K, V>* p) const;
  void Transplant(Node<K, V>* u, Node<K, V>* v);
  //
  Node<K, V>* p_root_;
};

//
///
//

template<class K, class V>
BinarySearchTree<K, V>::BinarySearchTree()
  : p_root_(NULL)
{}

//

template<class K, class V>
BinarySearchTree<K, V>::~BinarySearchTree()
{
  //Destroy(p_root_);
}

//

template<class K, class V>
void BinarySearchTree<K, V>::Add(const K& key, const V& value)
{
  Node<K, V>* p_parent = NULL;
  Node<K, V>* p = p_root_;
  while (p != NULL) {
    p_parent = p;
    p = key < p->key ? p->p_left_child : p->p_right_child;
  }
  Node<K, V>* p_new_node = new Node<K, V>();
  p_new_node->key = key;
  p_new_node->value = value;
  p_new_node->p_left_child = NULL;
  p_new_node->p_right_child = NULL;
  p_new_node->p_parent = p_parent;
  if (p_parent == NULL) p_root_ = p_new_node;
  else if (key < p_parent->key) p_parent->p_left_child = p_new_node;
  else p_parent->p_right_child = p_new_node;
}

//

template<class K, class V>
void BinarySearchTree<K, V>::Remove(const K& key)
{
  Node<K, V>* p = p_root_;
  while (p != NULL && key != p->key)
    p = key < p->key ? p->p_left_child : p->p_right_child;
  if (p == NULL) return;
  if (p->p_left_child == NULL) Transplant(p, p->p_right_child);
  else if (p->p_right_child == NULL) Transplant(p, p->p_left_child);
  else {
    Node<K, V>* m = Minimum(p->p_right_child);
    if (m->p_parent != p) {
      Transplant(m, m->p_right_child);
      m->p_right_child = p->p_right_child;
      m->p_right_child->p_parent = m;
    }
    Transplant(p, m);
    m->p_left_child = p->p_left_child;
    m->p_left_child->p_parent = m;
  }
  delete p;
}

//

template<class K, class V>
void BinarySearchTree<K, V>::Find(const K& key, V** pp_value) const
{
  Node<K, V>* p = p_root_;
  while (p != NULL && key != p->key)
    p = key < p->key ? p->p_left_child : p->p_right_child;
  *pp_value = p == NULL ? NULL : &p->value;
}

//

template<class K, class V>
Node<K, V>* BinarySearchTree<K, V>::Minimum(Node<K, V>* p) const
{
  if (p == NULL) return NULL;
  while (p->p_left_child != NULL) p = p->p_left_child;
  return p;
}

//

template<class K, class V>
void BinarySearchTree<K, V>::Transplant(Node<K, V>* u, Node<K, V>* v)
{
  if (u->p_parent == NULL) p_root_ = v;
  else if (u == u->p_parent->p_left_child) u->p_parent->p_left_child = v;
  else u->p_parent->p_right_child = v;
  if (v != NULL) v->p_parent = u->p_parent;
}

//
///
//

int main()
{
  BinarySearchTree<int, string> bst;
  bst.Add(6, "123456");
  bst.Add(9, "123456789");
  bst.Add(7, "1234567");
  bst.Add(3, "123");
  bst.Add(5, "12345");
  bst.Add(2, "12");
  bst.Add(8, "12345678");
  string* p_value;
  bst.Find(5, &p_value);
  if (p_value != NULL) cout << *p_value << endl;
  else cout << "Not found." << endl;
  bst.Remove(5);
  bst.Find(5, &p_value);
  if (p_value != NULL) cout << *p_value << endl;
  else cout << "Not found." << endl;
  bst.Add(5, "New 12345");
  bst.Find(5, &p_value);
  if (p_value != NULL) cout << *p_value << endl;
  else cout << "Not found." << endl;
  bst.Find(7, &p_value);
  if (p_value != NULL) cout << *p_value << endl;
  else cout << "Not found." << endl;
  return 0;
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

