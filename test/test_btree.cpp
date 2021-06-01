#include "btree.h"
#include "errcode.h"
#include <iostream>
using namespace std;

template <typename T> void PrintNode(BNode<T> *node) {
  if (node == nullptr)
    return;

  for (int i = 0; i < node->Num - 1; i++) {
    cout << node->Keys[i] << " ";
  }
  cout << node->Keys[node->Num - 1] << endl;
}

template <typename T> void test_Remove(BTree<T> &t) {
  // 情况1；删除右多余关键字情况的终端关键字
  //  t.Remove(5);

  // 情况2：删除无多余关键字的终端关键字
  // 情况2.1: 左右结点有剩余
  //  t.Remove(3);

  // 情况2.2：左右结点无剩余
  //  t.Remove(12);
  //  t.Remove(16);
  //  t.Remove(3);
  //  t.Remove(5);

  t.Remove(14);
}

void testBTree() {
  BTree<int> t(3);

  int arr[7] = {4, 8, 12, 14, 16, 5, 3};
  //  int arr[3] = {8, 4, 14};
  for (int i : arr) {
    t.Insert(i);
  }

  test_Remove(t);

  //  t.Search(16);
  //  t.Search(20);

  LOG_DEBUG(">> 树深度: %d\n", t.Depth());
  t.Print();
}