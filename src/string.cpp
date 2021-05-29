// @Author       Raim.Yan
// @Date         2021/5/25 9:57 下午
// @Description

#include "mstring.h"

// 蛮力搜索算法
static int findSubstr_bf(const string &s, const string &d) {
  int i = 0, j = 0; // 长串索引, 短串索引
  size_t l1 = s.length();
  size_t l2 = d.length(); // 长串长度, 短串长度

  while (i < l1 && j < l2) {
    if (s[i] == d[j]) {
      // 匹配情况: 短串向后移动一位，长串向后移动一位
      i++;
      j++;
    } else {
      // 不匹配情况: 短串重置为0, 长串向后移动一位
      // TODO: 当长串剩余长度小于短串时跳过
      i = i - j + 1;
      j = 0;
    }
  }

  // 成功情况：短串索引到最后一位
  return j == l2 ? i - j : -1;
}

// 生成 next 表
// 计算每个位置的最长前缀数
static int *genNext(const string &s) {
  size_t len = s.length();
  // 特殊情况：零个字符
  if (len == 0)
    return nullptr;

  int *next = (int *)calloc(sizeof(int), len);

  // next数组的第 0 个位置一定是 -1
  next[0] = -1;

  int i = 0, j = -1; // 长串索引, 短串索引
  while (i < len) {
    if (j == -1 || s[i] == s[j]) {
      // 匹配情况
      i++;
      j++;
      next[i] = j;
    } else {
      // 不匹配情况
      j = next[j];
    }
  }

  return next;
}

// KMP搜索算法
static int findSubstr_kmp(const string &s, const string &d) {
  int i = 0, j = 0;         // 长串索引, 短串索引
  int l1 = int(s.length()); // 长串长度
  int l2 = int(d.length()); //  短串长度

  // 从短串生成 next 表
  int *next = genNext(d);
  while (i < l1 && j < l2) {
    if (j == -1 || s[i] == d[j]) {
      // 短串向后移动一位，长串向后移动一位
      i++;
      j++;
    } else {
      // 不匹配情况: 仅需要重置短串索引
      j = next[j];
    }
  }

  free(next);
  return j == l2 ? i - j : -1;
}

int String::FindSubstr(const string &s) { return findSubstr_kmp(*this, s); }
