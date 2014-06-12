//
// Chapter 18. B-Trees
//
// Implementation of a demonstrative B-tree. Note that this B-tree
// is fully main-memory-based, and all keys and values are of
// string type, since the goal of this implementation is to show
// the basic structure and main operations of a B-tree.
//
// Hao Wu, 06/11/2014
//

#include <cstdio>   // sprintf()
//
#include <iostream>
#include <vector>
#include <string>
//
using namespace std;

//
///
//

const bool _DEBUG = true;

//

void DumpDebugMessage(const string& msg)
{
  if (_DEBUG) {
    cout << msg << endl;
  }
}

//
///
//

class BTree
{
public:
  //
  BTree(int m);
  //
  void Search(const string& key, string** pp_value);
  void Insert(const string& key, const string& value);
  void Delete(const string& key);
  void Dump();
  //
private:
  //
  struct Tuple
  {
    Tuple();
    Tuple(const string& key, const string& value);
    string key;
    string value;
  };
  //
  struct Node
  {
    Node(int m);
    //
    int     m; // maximum number of tuples. m = 2 * t - 1
    int     n; // current number of tuples.
    bool leaf;
    vector<Tuple> v_tuple;
    vector<Node*> v_child;
  };
  //
  void Split(Node* x, int i);
  void Insert(Node* x, const string& key, const string& value);
  void RotateLeft(Node* x, int i);
  void RotateRight(Node* x, int i);
  void Merge(Node* x, int i);
  void Delete(Node* x, const string& key);
  void Dump(Node* x, int level);
  //
  int      m_; // maximum number of tuples.
  Node* root_;
};

//
///
//

BTree::Tuple::Tuple()
{
}

//

BTree::Tuple::Tuple(const string& key, const string& value)
  : key(key), value(value)
{
}

//

BTree::Node::Node(int m)
  : m(m)
{
  n = 0;
  leaf = true;
  v_tuple.resize(m);
  v_child.resize(m + 1);
}

//
// class BTree: public methods
//

BTree::BTree(int m)
{
  m_ = m;
  root_ = new Node(m_);
}

//

void BTree::Search(const string& key, string** pp_value)
{
  Node* x = root_;
  while (true) {
    int i = 0;
    while (i < x->n && key > x->v_tuple[i].key) {
      i++;
    }
    if (i < x->n && key == x->v_tuple[i].key) {
      *pp_value = &(x->v_tuple[i].value);
      break;
    } else if (x->leaf) {
      *pp_value = NULL;
      break;
    } else {
      // DiskRead(x->v_child[i]);
      x = x->v_child[i];
    }
  }
}

//

void BTree::Insert(const string& key, const string& value)
{
  Node* r = root_;
  if (r->n == m_) {
    DumpDebugMessage(">>>> Root node split.");
    Node* s = new Node(m_);
    root_ = s;
    s->leaf = false;
    s->n = 0;
    s->v_child[0] = r;
    Split(s, 0);
    Insert(s, key, value);
  } else {
    Insert(r, key, value);
  }
}

//

void BTree::Delete(const string& key)
{
  Delete(root_, key);
}

//

void BTree::Dump()
{
  Dump(root_, 0);
}

//
// class BTree: private methods
//

void BTree::Split(Node* x, int i)
{
  //
  // Note that x->v_child[i] is guaranteed to
  // have exactly m tuples.
  //
  Node* z = new Node(m_);
  Node* y = x->v_child[i];
  z->leaf = y->leaf;
  int t = (m_ + 1) / 2;
  z->n = t - 1;
  for (int j = 0; j < t - 1; j++) {
    z->v_tuple[j] = y->v_tuple[j + t];
  }
  if (!y->leaf) {
    //
    for (int j = 0; j < t + 1; j++) {
      z->v_child[j] = y->v_child[j + t];
    }
  }
  y->n = t - 1;
  for (int j = x->n; j >= i + 1; j--) {
    x->v_child[j + 1] = x->v_child[j];
  }
  x->v_child[i + 1] = z;
  for (int j = x->n - 1; j >= i; j--) {
    x->v_tuple[j + 1] = x->v_tuple[j];
  }
  x->v_tuple[i].key = y->v_tuple[t - 1].key;
  x->n++;
  // DiskWrite(z)
  // DiskWrite(y)
  // DiskWrite(x)
}

//

void BTree::Insert(Node* x, const string& key, const string& value)
{
  //
  // Note that we can guarantee that either x is the root
  // or it has at most 2 * t - 2 (i.e. m - 1) tuples.
  //
  int i = x->n - 1;
  if (x->leaf) {
    DumpDebugMessage(">>>> Insert to leaf node.");
    while (i >= 0 && key < x->v_tuple[i].key) {
      x->v_tuple[i + 1] = x->v_tuple[i];
      i--;
    }
    i++;
    x->v_tuple[i].key = key;
    x->v_tuple[i].value = value;
    x->n++;
    // DiskWrite(x);
  } else {
    DumpDebugMessage(">>>> Insert to non-leaf node.");
    while (i >= 0 && key < x->v_tuple[i].key) {
      i--;
    }
    i++;
    // DiskRead(x->v_child[i]);
    if (x->v_child[i]->n == m_) {
      DumpDebugMessage(">>>> Node split.");
      Split(x, i);
      if (key > x->v_tuple[i].key) {
        i++;
      }
    }
    Insert(x->v_child[i], key, value);
  }
}

//

void BTree::RotateLeft(Node* x, int i)
{
  //
  // Let y = x->v_child[i] and z = x->v_child[i + 1].
  // Note that we can guarantee that:
  //   1) x has at least t tuples,
  //   2) y has t - 1 tuples, and
  //   3) z has at least t tuples.
  //
  Node* y = x->v_child[i];
  Node* z = x->v_child[i + 1];
  y->v_tuple[y->n] = x->v_tuple[i];
  y->v_child[y->n + 1] = z->v_child[0];
  y->n++;
  x->v_tuple[i] = z->v_tuple[0];
  for (int j = 0; j < z->n - 1; j++) {
    z->v_tuple[j] = z->v_tuple[j + 1];
  }
  for (int j = 0; j < z->n; j++) {
    z->v_child[j] = z->v_child[j + 1];
  }
  z->n--;
}

//

void BTree::RotateRight(Node* x, int i)
{
  //
  // Let y = x->v_child[i] and z = x->v_child[i + 1].
  // Note that we can guarantee that:
  //   1) x has at least t tuples,
  //   2) y has at least t tuples, and
  //   3) z has t - 1 tuples.
  //
  Node* y = x->v_child[i];
  Node* z = x->v_child[i + 1];
  for (int j = z->n - 1; j >= 1; j--) {
    z->v_tuple[j] = z->v_tuple[j - 1];
  }
  for (int j = z->n; j >= 1; j--) {
    z->v_child[j] = z->v_child[j - 1];
  }
  z->v_tuple[0] = x->v_tuple[i];
  z->v_child[0] = y->v_child[y->n];
  z->n++;
  x->v_tuple[i] = y->v_tuple[y->n - 1];
  y->n--;
}

//

void BTree::Merge(Node* x, int i)
{
  //
  // Let y = x->v_child[i] and z = x->v_child[i + 1].
  // Note that we can guarantee that:
  //   1) x is not a leaf node,
  //   2) x has at least t tuples,
  //   3) both y and z have t - 1 tuples, and
  //   4) both y and z have already been read out from disk.
  //
  Node* y = x->v_child[i];
  Node* z = x->v_child[i + 1];
  y->n = m_;
  int t = (m_ + 1) / 2;
  y->v_tuple[t - 1] = x->v_tuple[i];
  for (int j = t; j < m_; j++) {
    y->v_tuple[j] = z->v_tuple[j - t];
  }
  for (int j = t; j < m_ + 1; j++) {
    y->v_child[j] = z->v_child[j - t];
  }
  // DiskDelete(z);
  delete z;
  for (int j = i; j < x->n - 1; j++) {
    x->v_tuple[j] = x->v_tuple[j + 1];
  }
  for (int j = i + 1; j < x->n; j++) {
    x->v_child[j] = x->v_child[j + 1];
  }
  x->n--;
}

//

void BTree::Delete(Node* x, const string& key)
{
  //
  // Note that we can guarantee that either x is the root
  // or it has at least t (i.e. (m + 1) / 2) tuples.
  //
  int i = 0;
  while (i < x->n && key > x->v_tuple[i].key) {
    i++;
  }
  if (i < x->n && key == x->v_tuple[i].key) {
    if (x->leaf) {
      //
      // Case 1.
      //
      DumpDebugMessage(">>>> Delete case 1.");
      for (int j = i; j < x->n - 1; j++) {
        x->v_tuple[j] = x->v_tuple[j + 1];
      }
      x->n--;
    } else {
      // DiskRead(x->v_child[i]);
      Node* y = x->v_child[i];
      int t = (m_ + 1) / 2;
      if (y->n >= t) {
        //
        // Case 2a.
        //
        DumpDebugMessage(">>>> Delete case 2a.");
        Tuple tuple0 = y->v_tuple[y->n - 1];
        x->v_tuple[i] = tuple0;
        Delete(y, tuple0.key);
      } else {
        // DiskRead(x->v_child[i + 1]);
        Node* z = x->v_child[i + 1];
        if (z->n >= t) {
          //
          // Case 2b.
          //
          DumpDebugMessage(">>>> Delete case 2b.");
          Tuple tuple0 = z->v_tuple[0];
          x->v_tuple[i] = tuple0;
          Delete(z, tuple0.key);
        } else {
          //
          // Case 2c.
          //
          DumpDebugMessage(">>>> Delete case 2c.");
          Merge(x, i);
          Delete(y, key);
        }
      }
    }
  } else {
    if (x->leaf) {
      // Case 3: Not found, do nothing.
      DumpDebugMessage(">>>> Delete case 3.");
    } else {
      // DiskRead(x->v_child[i]);
      Node* y = x->v_child[i];
      int t = (m_ + 1) / 2;
      if (y->n >= t) {
        //
        // Case 4a.
        //
        DumpDebugMessage(">>>> Delete case 4a.");
        Delete(y, key);
      } else {
        Node* z;
        if (i < x->n) {
          // DiskRead(x->v_child[i + 1]);
          z = x->v_child[i + 1];
        } else {
          z = y;
          // DiskRead(x->v_child[i - 1]);
          y = x->v_child[i - 1];
          i--;
        }
        if (z->n >= t) {
          //
          // Case 4b-1. (3a in the book)
          //
          DumpDebugMessage(">>>> Delete case 4b-1.");
          RotateLeft(x, i);
          Delete(y, key);
        } else if (y->n >= t) {
          //
          // Case 4b-2. (3a in the book)
          //
          DumpDebugMessage(">>>> Delete case 4b-2.");
          RotateRight(x, i);
          Delete(z, key);
        } else {
          //
          // Case 4c. (3b in the book)
          //
          DumpDebugMessage(">>>> Delete case 4c.");
          Merge(x, i);
          if (root_->n == 0) {
            // DiskDelete(root_);
            delete root_;
            root_ = y;
          }
          Delete(y, key);
        }
      }
    }
  }
}

//

void BTree::Dump(Node* x, int level)
{
  for (int i = 0; i < level; i++) {
    cout << "  ";
  }
  for (int i = 0; i < x->n; i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << x->v_tuple[i].key;
  }
  cout << endl;
  if (x->leaf) {
    return;
  }
  for (int i = 0; i < x->n + 1; i++) {
    Dump(x->v_child[i], level + 1);
  }
}

//
///
//

void TestInsert(BTree& bt, const string& key, const string& value)
{
  cout << "Insert \'" << key << "\': " << endl;
  bt.Insert(key, value);
  bt.Dump();
  cout << "--" << endl;
}

//

void TestDelete(BTree& bt, const string& key)
{
  cout << "Delete \'" << key << "\': " << endl;
  bt.Delete(key);
  bt.Dump();
  cout << "--" << endl;
}

//

void TestSearch(BTree& bt, const string& key)
{
  cout << "Search \'" << key << "\': ";
  string* p_value;
  bt.Search(key, &p_value);
  if (p_value != NULL) {
    cout << "\'" << *p_value << "\'." << endl;
  } else {
    cout << "Not found." << endl;
  }
  cout << "--" << endl;
}

//

int main()
{
  //BTree bt(7);
  //BTree bt(15);
  BTree bt(5);
  //
  /*
  TestInsert(bt, "A", "");
  TestInsert(bt, "D", "");
  TestInsert(bt, "F", "");
  TestInsert(bt, "H", "");
  TestInsert(bt, "L", "");
  TestInsert(bt, "N", "");
  TestInsert(bt, "P", "");
  TestInsert(bt, "B", "");
  TestInsert(bt, "K", "");
  TestInsert(bt, "J", "");
  TestInsert(bt, "I", "");
  TestInsert(bt, "M", "");
  TestInsert(bt, "O", "");
  TestInsert(bt, "Q", "");
  */
  /*
  char buff_key[10];
  char buff_value[100];
  for (int i = 0; i < 1000; i++) {
    sprintf(buff_key, "%03d", i);
    sprintf(buff_value, "Data_%03d", i);
    TestInsert(bt, buff_key, buff_value);
  }
  TestSearch(bt, "574");
  TestSearch(bt, "1200");
  */
  string a[] = {
    "A", "B", "C", "D", "E", "G", "J", "K",
    "L", "M", "N", "O", "P", "Q", "R", "S",
    "T", "U", "V", "X", "Y", "Z"};
  int n = sizeof(a) / sizeof(string);
  char buff[10];
  for (int i = 0; i < n; i++) {
    sprintf(buff, "Data_%s", a[i].c_str());
    TestInsert(bt, a[i], buff);
  }
  //
  TestDelete(bt, "U"); // Case 2b
  TestDelete(bt, "S"); // Case 4b-1
  TestDelete(bt, "Q"); // Case 4c
  TestDelete(bt, "Z"); // Case 4c
  //
  TestSearch(bt, "X");
  TestSearch(bt, "F");
  //
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

