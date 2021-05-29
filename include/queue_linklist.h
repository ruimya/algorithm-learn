// @Author       Raim.Yan
// @Date         2021/5/23 2:37 下午
// @Description  链式队列（带头结点）

#ifndef ALGORITHM_LEARN_QUEUE_LINKLIST_H
#define ALGORITHM_LEARN_QUEUE_LINKLIST_H
#include "errcode.h"
#include "linklist.h"
#include "queue.h"
#include <iostream>
using namespace std;

template <class T> class QueueLinkList : public Queue<T> {
private:
  Node<T> *front, *rear;

public:
  QueueLinkList();
  ~QueueLinkList();
  STATUS Push(T elem) override; // 入队
  STATUS Pop(T &elem) override; // 出队
  size_t Len() override;        // 元素个数
  void Print() override;        // 打印元素
  void Clear() override;        // 清空元素
  bool IsEmpty() override;      // 清空元素
};

template <class T> QueueLinkList<T>::QueueLinkList() {
  // 初始化头结点
  front = (Node<T> *)malloc(sizeof(Node<T>));
  front->data = 0; // 充当 len
  front->next = nullptr;
  rear = front;
}

template <class T> QueueLinkList<T>::~QueueLinkList() { free(front); }

// 入队操作
template <class T> STATUS QueueLinkList<T>::Push(T elem) {
  // 尾插法
  Node<T> *node = (Node<T> *)malloc(sizeof(Node<T>));
  node->data = elem;
  node->next = nullptr;
  rear->next = node;
  rear = node;
  front->data++;
  return SUCCESS;
}

// 出队操作
template <class T> STATUS QueueLinkList<T>::Pop(T &elem) {
  if (IsEmpty()) {
    return ERR_EMTPY;
  }

  // 删除第一个结点
  Node<T> *tmp;
  tmp = front->next->next;
  free(front->next);
  front->next = tmp;

  // 特殊情况：只有一个结点，删除后便为空，需要更新尾结点
  if (front->next == NULL) {
    rear = front;
  }

  front->data--;
  return SUCCESS;
}
template <class T> size_t QueueLinkList<T>::Len() { return front->data; }
template <class T> void QueueLinkList<T>::Print() {}
template <class T> void QueueLinkList<T>::Clear() {}
template <class T> bool QueueLinkList<T>::IsEmpty() { return front == rear; }

#endif // ALGORITHM_LEARN_QUEUE_LINKLIST_H
