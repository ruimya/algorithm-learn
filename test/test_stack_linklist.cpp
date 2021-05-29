// @Author       Raim.Yan
// @Date         2021/5/21 5:31 下午
// @Description
#include "stack_linklist.h"
#include <iostream>
using namespace std;

void testStackLinkList() {
  StackLinkList<int> s;
  s.Push(2);
  s.Push(3);
  s.Push(4);
  s.Print();
  cout << s.Pop() << endl;
  s.Print();
  cout << s.Pop() << endl;
  s.Print();
  s.Push(2);
  s.Push(3);
  s.Push(4);
  s.Clear();
}