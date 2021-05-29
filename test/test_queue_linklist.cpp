// @Author       Raim.Yan
// @Date         2021/5/23 3:15 下午
// @Description

#include "queue_linklist.h"
#include <iostream>
using namespace std;

void testQueueLinkList() {
  QueueLinkList<int> q;

  cout << "入队1: " << q.Push(1) << endl;
  cout << "入队2: " << q.Push(2) << endl;
  cout << "入队3: " << q.Push(3) << endl;

  cout << "打印队列: ";
  q.Print();

  cout << "队列长度: " << q.Len() << endl;

  int out;
  cout << "出队: " << q.Pop(out) << " " << out << endl;
  cout << "入队3: " << q.Push(3) << endl;

  cout << "打印队列: ";
  q.Print();

  cout << "出队: " << q.Pop(out) << " " << out << endl;
  cout << "出队: " << q.Pop(out) << " " << out << endl;
  cout << "是否为空: " << q.IsEmpty() << endl;
}