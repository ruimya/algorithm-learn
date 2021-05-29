// @Author       Raim.Yan
// @Date         2021/5/21 6:38 下午
// @Description

#ifndef ALGORITHM_LEARN_QUEUE_H
#define ALGORITHM_LEARN_QUEUE_H
#include "linearlist.h"

template <class T> class Queue : public LinearList {
public:
  virtual STATUS Push(T elem) = 0; // 入队
  virtual STATUS Pop(T &elem) = 0; // 出队
};

#endif // ALGORITHM_LEARN_QUEUE_H
