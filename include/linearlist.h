// @Author       Raim.Yan
// @Date         2021/5/21 11:35 上午
// @Description

#ifndef ALGORITHM_LEARN_LINEARLIST_H
#define ALGORITHM_LEARN_LINEARLIST_H
#include <iostream>

// 线性表
class LinearList {
public:
  virtual bool IsEmpty() { // 判断是否为空
    return Len() == 0;
  }
  virtual size_t Len() = 0; // 元素个数
  virtual void Print() = 0; // 打印元素
  virtual void Clear() = 0; // 清空元素
};

#endif // ALGORITHM_LEARN_LINEARLIST_H
