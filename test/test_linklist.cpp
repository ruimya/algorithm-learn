// @Author       Raim.Yan
// @Date         2021/5/21 11:50 上午
// @Description
#include "linklist.h"
#include <iostream>
using namespace std;

void testLinkList() {
  LinkList<int> l;
  l.Append(3);
  l.Append(4);
  l.Append(5);
  l.Insert(2);
  l.Insert(1);
  l.Delete(1);
  l.Print();

  l.Clear();
  l.Print();

  l.Append(3);
  l.Print();

  if (l.Delete(2) != OK)
    cout << "FAIL" << endl;

  cout << "Len: " << l.Len() << endl;

  if (l.Delete(0) != OK)
    cout << "FAIL" << endl;

  l.Print();
}