// @Author       Raim.Yan
// @Date         2021/5/21 11:47 上午
// @Description

#ifndef ALGORITHM_LEARN_BILINKLIST_H
#define ALGORITHM_LEARN_BILINKLIST_H
#include "linearlist.h"

// 双向结点
template <class T> typedef struct BiNode<T> {
  T data;        // 数据域，存储数据
  BiNode *next;  // 指针域, 指向下一个结点
  BiNode *prior; // 指针域, 指向上一个结点
} BiNode;

// 双链表（有头节点）
template <class T> class BiLinkList : public LinearList {
private:
  BiNode *head, *tail;
  int len;

public:
  BiLinkList();  // 构造函数
  ~BiLinkList(); // 析构函数

  size_t Len() override;
  void Clear() override;
  void Print() override;

  void Append(T elem);
  void Insert(inTt elem);
  bool Insert(int loc, T elem);
  int Index(T elem);
  int Delete(int loc);
  bool Pop();
};

template <class T> BiLinkList<T>::BiLinkList() {}
template <class T> BiLinkList<T>::~BiLinkList() {}
template <class T> size_t BiLinkList<T>::Len() { return 0; }
template <class T> void BiLinkList<T>::Clear() {}
template <class T> void BiLinkList<T>::Print() {}
template <class T> void BiLinkList<T>::Append(T elem) {}
template <class T> void BiLinkList<T>::Insert(inTt elem) {}
template <class T> bool BiLinkList<T>::Insert(int loc, T elem) { return false; }
template <class T> int BiLinkList<T>::Index(T elem) { return 0; }
template <class T> int BiLinkList<T>::Delete(int loc) { return 0; }
template <class T> bool BiLinkList<T>::Pop() { return false; }

#endif // ALGORITHM_LEARN_BILINKLIST_H
