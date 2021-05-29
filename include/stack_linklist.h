// @Author       Raim.Yan
// @Date         2021/5/21 6:30 下午
// @Description

#ifndef ALGORITHM_LEARN_STACK_LINKLIST_H
#define ALGORITHM_LEARN_STACK_LINKLIST_H
#include "stack.h"
#include <iostream>
using namespace std;

// 链栈
template <class T> class StackLinkList : public Stack<T> {
private:
  int len;       // 元素个数
  Node<T> *head; // 栈顶指针

public:
  StackLinkList();
  ~StackLinkList();
  size_t Len() override; // 元素个数
  void Print() override; // 打印元素
  void Clear() override; // 清空元素

  int Push(T elem) override;
  T Pop() override;
};

template <class T> StackLinkList<T>::StackLinkList() {
  len = 0;

  // 初始化头结点
  head = (Node<T> *)malloc(sizeof(Node<T>));
  head->data = 0;
  head->next = nullptr;
}

template <class T> StackLinkList<T>::~StackLinkList() {}

template <class T> size_t StackLinkList<T>::Len() { return len; }

template <class T> int StackLinkList<T>::Push(T elem) {
  Node<T> *node = (Node<T> *)malloc(sizeof(Node<T>));
  node->data = elem;
  node->next = head->next;
  head->next = node;
  len++;
  return 0;
}

template <class T> T StackLinkList<T>::Pop() {
  int data;
  Node<T> *tmp;

  if (head->next == nullptr)
    return 0;
  data = head->next->data;
  tmp = head->next->next;
  free(head->next);
  head->next = tmp;
  len--;
  return data;
}

template <class T> void StackLinkList<T>::Print() {
  if (head->next == nullptr)
    return;

  Node<T> *p;
  p = head->next;
  while (p->next) {
    cout << p->data << " -> ";
    p = p->next;
  }
  cout << p->data << endl;
}

template <class T> void StackLinkList<T>::Clear() {}

#endif // ALGORITHM_LEARN_STACK_LINKLIST_H
