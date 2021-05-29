// @Author       Raim.Yan
// @Date         2021/5/25 10:14 下午
// @Description

#include "mstring.h"
#include <iostream>
using namespace std;

void testString() {
  String s = "dbabcabcabdcc";

  cout << s(1, 3) << endl;

  int found = s.FindSubstr("cc");
  if (found != -1)
    cout << "Found at " << found << endl;
  else
    cout << "Not Found" << endl;
}