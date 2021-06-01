// @Author       Raim.Yan
// @Date         2021/5/25 4:45 下午
// @Description  静态链表

#ifndef ALGORITHM_LEARN_STATICLIST_H
#define ALGORITHM_LEARN_STATICLIST_H
#include "errcode.h"
#include "linearlist.h"
#include <iostream>
using namespace std;

template <class T> struct Component {
  T data;  // 数据域
  int cur; // 游标（指向下一个元素位置）
};

template <class T> class StaticList : public LinearList {
private:
  size_t cap, len;    // 容量, 长度
  Component<T> *data; // 静态链表数组
  int pback, pdata;   //  备用链表头索引, 数据链表头索引
  int tail;           // 数据链表尾指针（头指针=Keys[pdata].cur）

public:
  explicit StaticList(size_t size);
  ~StaticList();

  size_t Len() override;
  void Clear() override;
  void Print() override;
  bool IsEmpty() override; // 判断是否为空

  STATUS Append(T elem);
  STATUS Insert(T elem);
  STATUS Insert(int loc, T elem);
  T *Index(int loc);
  int Find(T elem);
  STATUS Delete(int loc);
};

// 初始化静态链表
template <class T> StaticList<T>::StaticList(size_t size) {
  // 分配空间（多余两个位置用于数据链表和备用链表的头结点）
  data = (Component<T> *)malloc(sizeof(Component<T>) * (size + 2));
  cap = size;
  for (int i = 0; i < cap; i++) {
    data[i].cur = i + 1;
  }
  pback = 0;           // 将第一个元素作为备用链表头结点
  pdata = cap + 1;     // 将最后一个元素作为数据链表头结点
  data[cap].cur = 0;   // 初始化备用链表最后一个元素的游标
  data[pdata].cur = 0; // 初始化数据链表的游标
  tail = 0;            // 初始化数据链表尾指针
  len = 0;
}

template <class T> StaticList<T>::~StaticList() {
  // 释放空间
  free(data);
}
template <class T> size_t StaticList<T>::Len() { return len; }

template <class T> void StaticList<T>::Print() {
  int p = data[pdata].cur;
  if (!p) {
    cout << "Empty" << endl;
    return;
  }

  while (data[p].cur) {
    cout << data[p].data << " ";
    p = data[p].cur;
  }
  cout << data[p].data << endl;
}

template <class T> STATUS StaticList<T>::Append(T elem) {
  // 备用链表指向的第一个可用位置
  int avail = data[pback].cur;

  // 判断备用链表为否为空 (已满)
  if (!avail)
    return ERR_FULL;

  // 将备用链表头指针指向的第一位置作为新结点
  data[avail].data = elem;

  // 将该结点从备用链表剔除
  data[pback].cur = data[avail].cur;

  // 将新结点接入到数据链表末尾
  // 找到前驱结点（如果尾结点不存在则找头结点）
  int prev = tail ? tail : pdata;
  data[avail].cur = data[prev].cur;
  data[prev].cur = avail;

  // 更新尾指针
  tail = avail;
  len++;
  return OK;
}

// 插入元素（第一个位置）
template <class T> STATUS StaticList<T>::Insert(T elem) {
  // 备用链表指向的第一个可用位置
  int avail = data[pback].cur;

  // 判断备用链表为否为空 (数据链表已满)
  if (!avail)
    return ERR_FULL;

  // 将备用链表头指针指向的第一位置作为新结点
  data[avail].data = elem;

  // 判断数据链表是否为空
  if (!data[pdata].cur) {
    // 特殊情况：插入第一个元素
    tail = avail;
  }

  // 将该结点从备用链表剔除
  data[pback].cur = data[avail].cur;

  // 将新结点接入到数据链表头部
  data[avail].cur = data[pdata].cur;
  data[pdata].cur = avail;

  len++;
  return OK;
}

// 删除元素
template <class T> STATUS StaticList<T>::Delete(int loc) {
  // 判断是否为空
  if (!data[pdata].cur)
    return ERR_EMTPY;

  // 找到目标位置的前驱结点索引 p
  int p = pdata;
  for (int i = 0; i < loc && p; i++)
    p = data[p].cur;

  // 特殊情况：索引范围超出 或 前驱节点即尾结点
  if (!p || !data[p].cur)
    return ERR_OUT_OF_RANGE;

  // 删除指定结点
  int t = data[p].cur;
  data[p].cur = data[t].cur;

  // 特殊情况：删除结点为尾结点, 需要更新 tail 指针
  if (!data[t].cur)
    tail = p;

  // 将被删除结点插入备用链表
  data[t].cur = data[pback].cur;
  data[pback].cur = t;

  len--;
  return OK;
}

template <class T> void StaticList<T>::Clear() {
  for (int i = 0; i < cap; i++) {
    data[i].cur = i + 1;
  }
  data[cap].cur = 0;   // 初始化备用链表最后一个元素的游标
  data[pdata].cur = 0; // 初始化数据链表的游标
  tail = 0;            // 初始化数据链表尾指针
  len = 0;
}

template <class T> STATUS StaticList<T>::Insert(int loc, T elem) { return OK; }

template <class T> int StaticList<T>::Find(T elem) { return -1; }

template <class T> bool StaticList<T>::IsEmpty() {
  return data[pdata].cur == 0;
}

template <class T> T *StaticList<T>::Index(int loc) { return nullptr; }

#endif // ALGORITHM_LEARN_STATICLIST_H
