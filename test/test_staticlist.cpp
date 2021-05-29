// @Author       Raim.Yan
// @Date         2021/5/25 4:57 下午
// @Description
#include "staticlist.h"
#include <iostream>
using namespace std;

void testStaticList() {
  StaticList<int> l(5);
  l.Print();
  l.Insert(2);
  l.Insert(3);
  l.Append(4);
  l.Append(5);
  l.Append(6);
  l.Print();
  l.Delete(0);
  l.Print();
  cout << "Len: " << l.Len() << endl;
  l.Clear();
  l.Append(5);
  l.Print();
  cout << "Len: " << l.Len() << endl;
}