// @Author       Raim.Yan
// @Date         2021/5/25 10:18 下午
// @Description

#ifndef ALGORITHM_LEARN_MSTRING_H
#define ALGORITHM_LEARN_MSTRING_H

#include <iostream>
#include <string>
using namespace std;

class String : public string {
public:
  String() : string() {}
  String(const String &s) : string(s) {}
  String(const char *s) : string(s) {}
  String(const string &s) : string(s) {}

  int FindSubstr(const string &s);

  // 重载运算符
  String operator()(int n, int m) { return substr(n, m); }
};

#endif // ALGORITHM_LEARN_MSTRING_H
