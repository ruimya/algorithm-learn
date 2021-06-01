// @Author       Raim.Yan
// @Date         2021/5/21 6:48 下午
// @Description  顺序循环队列

#ifndef ALGORITHM_LEARN_QUEUE_ARRAY_H
#define ALGORITHM_LEARN_QUEUE_ARRAY_H
#include "errcode.h"
#include "queue.h"
#include <iostream>
using namespace std;

template <class T> class QueueArray : public Queue<T> {
private:
  int front;  // 队首指针（默认 0）
  int rear;   // 队尾指针
  T *data;    // 数据区域
  size_t cap; // 数据容量

public:
  explicit QueueArray(size_t size);
  ~QueueArray();
  STATUS Push(T elem) override; // 入队
  STATUS Pop(T &elem) override; // 出队
  size_t Len() override;        // 元素个数
  void Print() override;        // 打印元素
  void Clear() override;        // 清空元素
  bool IsEmpty() override;      // 判断是否为空
  bool IsFull();                // 判断是否已满
};

template <class T> QueueArray<T>::QueueArray(size_t size) {
  rear = 0;
  front = 0;

  // 采用牺牲1个单元的方式，实现循环队列
  cap = size + 1;
  data = (T *)malloc(sizeof(T) * cap);
}

template <class T> QueueArray<T>::~QueueArray() { free(data); }

// 入队操作
template <class T> STATUS QueueArray<T>::Push(T elem) {
  // 判断是否已满
  if (IsFull()) {
    return ERR_FULL;
  }
  data[rear] = elem;
  rear = ++rear % cap;
  return OK;
}

template <class T> STATUS QueueArray<T>::Pop(T &elem) {
  // 判断是否为空
  if (IsEmpty()) {
    elem = 0;
    return ERR_EMTPY;
  }
  elem = data[front];
  front = ++front % cap;
  return OK;
}

template <class T> size_t QueueArray<T>::Len() {
  return (rear + cap - front) % cap;
}

// 打印数据区域（剔除牺牲单元）
template <class T> void QueueArray<T>::Print() {
  if (IsEmpty()) {
    return;
  }

  // 遍历元素（从front开始到rear-1）
  int end = (rear - 1 + cap) % cap;
  for (int i = front; i != end; i = (i + 1) % cap) {
    cout << data[i] << " -> ";
  }
  cout << data[end] << endl;
}

template <class T> void QueueArray<T>::Clear() {
  front = 0;
  rear = 0;
}

template <class T> bool QueueArray<T>::IsFull() {
  return (rear + 1) % cap == front;
}

template <class T> bool QueueArray<T>::IsEmpty() { return rear == front; }

#endif // ALGORITHM_LEARN_QUEUE_ARRAY_H
