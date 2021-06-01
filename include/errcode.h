// @Author       Raim.Yan
// @Date         2021/5/22 7:28 下午
// @Description

#ifndef ALGORITHM_LEARN_ERRCODE_H
#define ALGORITHM_LEARN_ERRCODE_H

#define IN
#define OUT
#define LEN_ARRAY(a) ((int)(sizeof(a) / sizeof(a[0])))

// 错误码定义
typedef enum {
  OK = 0,
  ERROR = 1,
  ERR_NULL,
  ERR_DUPLICATE,
  ERR_NOT_EXIST,
  ERR_EMTPY,
  ERR_FULL,
  ERR_OUT_OF_RANGE,
  ERR_MALLOC,
} STATUS;

// 输出信息
#define LOG_INFO(format, ...) printf(format, ##__VA_ARGS__)

// 输出数组
#define LOG_ARRAY(array)                                                       \
  {                                                                            \
    int len = sizeof(array) / sizeof(array[0]);                                \
    for (int i = 0; i < len; i++) {                                            \
      printf("%d\t", array[i]);                                                \
    }                                                                          \
    printf("\n");                                                              \
  }

// 调试模式
#ifdef DEBUG
#define LOG_DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#define LOG_DEBUGF(format, ...)                                                \
  printf("FILE: %s, LINE: %d: " format, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#define LOG_DEBUG(format, ...)
#define LOG_DEBUGF(format, ...)
#endif

#endif // ALGORITHM_LEARN_ERRCODE_H
