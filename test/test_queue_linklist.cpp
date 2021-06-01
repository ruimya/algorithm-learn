// @Author       Raim.Yan
// @Date         2021/5/23 3:15 下午
// @Description

#include "queue_linklist.h"
#include <iostream>
using namespace std;

void testQueueLinkList() {
  QueueLinkList<int> q;

  q.Push(1);
  q.Push(2);
  q.Push(3);

  q.Print();
  cout << ">> 队列长度 " << q.Len() << endl;

  int out;
  STATUS status;

  status = q.Pop(out);
  cout << ">> 出队元素 " << (status ? -1 : out) << endl;
  cout << ">> 队列长度 " << q.Len() << endl;

  status = q.Pop(out);
  cout << ">> 出队元素 " << (status ? -1 : out) << endl;
  cout << ">> 队列长度 " << q.Len() << endl;

  status = q.Pop(out);
  cout << ">> 出队元素 " << (status ? -1 : out) << endl;

  status = q.Pop(out);
  cout << ">> 出队元素 " << (status ? -1 : out) << endl;

  q.Print();

  q.Push(3);
  q.Clear();
  q.Print();
  cout << ">> 队列长度 " << q.Len() << endl;
}