// @Author       Raim.Yan
// @Date         2021/5/20 6:43 下午
// @Description  单链表（含头结点）

#ifndef ALGORITHM_LEARN_LINKLIST_H
#define ALGORITHM_LEARN_LINKLIST_H
#include "errcode.h"
#include "linearlist.h"
#include <iostream>
using namespace std;

// 单向结点
template <class T> struct Node {
  T data;     // 数据域，存储数据
  Node *next; // 指针域
};

// 单链表（有头节点）
template <class T> class LinkList : public LinearList {
private:
  int len;              // 长度
  Node<T> *head, *tail; // 头指针, 尾指针
  Node<T> *newNode();

public:
  LinkList();
  ~LinkList();

  size_t Len() override;
  void Clear() override;
  void Print() override;

  STATUS Append(T elem);
  STATUS Insert(T elem);
  STATUS Insert(int loc, T elem);
  STATUS Delete(int loc);
  int Index(T elem);

  void Sort();              // 排序链表
  void Extend(LinkList *l); // 合并链表（在末尾追加）
  void Merge(LinkList *l);  // 合并链表（按顺序合并）
};

template <class T> LinkList<T>::LinkList() {
  // 初始化头结点
  head = newNode();
  head->data = 0;
  head->next = nullptr;

  // 默认头指针和尾指针指向都指向头结点
  tail = head;
  len = 0;
}

template <class T> LinkList<T>::~LinkList() {
  // 释放数据结点
  LinkList::Clear();

  // 释放头结点
  head->next = nullptr;
  free(head);
}

template <class T> Node<T> *LinkList<T>::newNode() {
  return (Node<T> *)malloc(sizeof(Node<T>));
}

// 获取长度
template <class T> size_t LinkList<T>::Len() { return len; }

// 新增元素 尾插法
template <class T> STATUS LinkList<T>::Append(T elem) {
  Node<T> *node = newNode();
  node->data = elem;
  node->next = nullptr;
  tail->next = node;
  tail = node;
  len++;
  return OK;
}

// 新增元素 头插法
template <class T> STATUS LinkList<T>::Insert(T elem) {
  Node<T> *node = newNode();
  node->data = elem;
  node->next = head->next;
  head->next = node;
  len++;
  return OK;
}

// 插入元素
template <class T> STATUS LinkList<T>::Insert(int loc, T elem) { return OK; }

// 打印链表（无头结点）
template <class T> void LinkList<T>::Print() {
  if (head->next == nullptr) {
    cout << "Empty" << endl;
    return;
  }

  Node<T> *p = head->next;
  while (p->next) {
    cout << p->data << " ";
    p = p->next;
  }
  cout << p->data << endl;
}

// 根据元素查找索引
template <class T> int LinkList<T>::Index(T elem) {
  if (head->next == nullptr) {
    return -1;
  }

  int index = 0;
  Node<T> *p = head->next;
  while (p) {
    if (p->data == elem) {
      return index;
    }
    p = p->next;
    index++;
  }
  return -1;
}

// 清空链表（不包括头结点）
template <class T> void LinkList<T>::Clear() {
  Node<T> *p, *tmp;

  if (head->next == nullptr)
    return;

  p = head->next;
  while (p) {
    tmp = p->next;
    free(p);
    p = tmp;
  }

  // 重置头结点
  head->next = nullptr;
  len = 0;
  tail = head;
}

template <class T> STATUS LinkList<T>::Delete(int loc) {
  Node<T> *p, *tmp;

  // 指向头指针（因为第一个数据结点也可能被删除, 头指针相当于第一个前驱结点）
  p = head;

  // 找到目标位置的前驱结点 (p为目标删除结点的前驱结点)
  for (int i = 0; i < loc && p; i++)
    p = p->next;

  // 特殊情况：指定索引越界 或 前驱结点无后继结点
  if (p == nullptr || p->next == nullptr) {
    return ERR_OUT_OF_RANGE;
  }

  // 删除目标结点
  tmp = p->next->next;
  free(p->next);
  p->next = tmp;

  // 特殊情况：目标结点为最后一个结点，需要更新尾指针
  if (tmp == nullptr)
    tail = p;

  len--;
  return OK;
}

template <class T> void LinkList<T>::Sort() {}

template <class T> void LinkList<T>::Extend(LinkList *l) {}

template <class T> void LinkList<T>::Merge(LinkList *l) {}

#endif // ALGORITHM_LEARN_LINKLIST_H
