// @Author       Raim.Yan
// @Date         2021/5/21 3:58 下午
// @Description

#ifndef ALGORITHM_LEARN_STACK_H
#define ALGORITHM_LEARN_STACK_H
#include "linearlist.h"
#include "linklist.h"

template <class ElemType> class Stack : public LinearList {
public:
  virtual int Push(ElemType elem) = 0; // 压栈
  virtual ElemType Pop() = 0;          // 出栈
};

#endif // ALGORITHM_LEARN_STACK_H
