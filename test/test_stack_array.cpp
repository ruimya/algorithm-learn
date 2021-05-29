// @Author       Raim.Yan
// @Date         2021/5/21 4:38 下午
// @Description  顺序栈

#include "stack_array.h"
#include <iostream>
using namespace std;

void testStackArray() {
  StackArray<int> s(30);
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
