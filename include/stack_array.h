// @Author       Raim.Yan
// @Date         2021/5/21 6:27 下午
// @Description

#ifndef ALGORITHM_LEARN_STACK_ARRAY_H
#define ALGORITHM_LEARN_STACK_ARRAY_H
#include "stack.h"
#include <iostream>
using namespace std;

// 顺序栈
template <class T> class StackArray : public Stack<T> {
private:
  int cap; // 容量
  int top; // 栈顶指针（默认-1）
  T *data; // 数据区域

public:
  explicit StackArray(int size);
  ~StackArray();
  size_t Len() override; // 元素个数
  void Print() override; // 打印元素
  void Clear() override; // 清空元素
  int Push(T elem) override;
  T Pop() override;
};

template <class T> StackArray<T>::StackArray(int size) {
  top = -1;
  cap = size;
  data = (int *)malloc(sizeof(int) * cap);
}

template <class T> StackArray<T>::~StackArray() { free(data); }

template <class T> size_t StackArray<T>::Len() { return top + 1; }

template <class T> int StackArray<T>::Push(T elem) {
  // 判断是否已经存满
  if (top == cap - 1) {
    return false;
  }
  data[++top] = elem;
  return true;
}

template <class T> T StackArray<T>::Pop() {
  // 判断是否为空
  if (top == -1)
    return false;
  return data[top--];
}

template <class T> void StackArray<T>::Print() {
  if (top == -1)
    return;

  for (int i = 0; i < top; i++) {
    cout << data[i] << " -> ";
  }
  cout << data[top] << endl;
}

template <class T> void StackArray<T>::Clear() { top = -1; }

#endif // ALGORITHM_LEARN_STACK_ARRAY_H
