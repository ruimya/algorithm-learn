// @Author       Raim.Yan
// @Date         2021/5/29 9:04 上午
// @Description  B-树

#ifndef ALGORITHM_LEARN_BTREE_H
#define ALGORITHM_LEARN_BTREE_H
#include "errcode.h"
#include "queue_linklist.h"
#include <iostream>
using namespace std;

// B 树结点
template <class T> class BNode {
public:
  size_t Num;        // 关键字个数
  T *Keys;           // 关键字数组 (容量为 m+1)
  BNode<T> **Childs; // 子树指针数组 (容量为 m+1)
  BNode<T> *Parent;  // 双亲指针
  bool IsLeaf;       // 是否为终端节点

  // 结点构造函数
  explicit BNode(size_t m) {
    Num = 0;
    Parent = nullptr;
    Childs = (BNode<T> **)malloc(sizeof(BNode<T> *) * (m + 2));
    Keys = (T *)malloc(sizeof(T) * (m + 1));
    IsLeaf = false;
  }

  // 结点析构函数
  ~BNode() {
    free(Childs);
    free(Keys);
  }
};

// B 树
template <class T> class BTree {
public:
  explicit BTree(size_t order);
  ~BTree();

  // 结点处理回调函数
  typedef void (*Callbak)(BNode<T> *);

  void Print();

  STATUS Remove(T key) {
    BNode<T> *res = nullptr;
    int nindex = -1, findex = -1;
    STATUS err = _find(root, key, res, nindex, findex);
    return err ? ERR_NOT_EXIST : remove(res, nindex, findex);
  }

  STATUS Insert(T key) {
    BNode<T> *res = nullptr;
    int nindex = -1, findex = -1;
    STATUS err = _find(root, key, res, nindex, findex);
    return err ? insert(res, key, nullptr) : ERR_DUPLICATE;
  }

  BNode<T> *Search(T key) {
    BNode<T> *res = nullptr;
    int nindex = -1, findex = -1;
    STATUS err = _find(root, key, res, nindex, findex);
    return err ? nullptr : res;
  }

  void Traverse(Callbak f) { _traverse(root, f); }

  int Depth() { return (int)depth; }

private:
  size_t m;       // B 树阶数
  size_t maxNum;  // 结点最大关键字数量
  size_t minNum;  // 结点最小关键字数量
  BNode<T> *root; // 根节点
  size_t depth;   // 数深度

  // 初始化新结点
  BNode<T> *newNode() { return new BNode<T>(m); }

  STATUS insert(BNode<T> *node, T key, BNode<T> *right);
  STATUS remove(BNode<T> *node, int nindex, int findex);
  STATUS split(BNode<T> *node);
  STATUS merge(BNode<T> *node, int findex);
  STATUS _find(IN BNode<T> *node, IN T key, OUT BNode<T> *&res, OUT int &nindex,
               OUT int &findex);
  void _traverse(BNode<T> *node, Callbak f);
};

// 初始化 m 阶 B 树
template <class T> BTree<T>::BTree(size_t order) {
  m = order;
  maxNum = m - 1;
  minNum = (m - 1) / 2;
  root = nullptr;
  depth = 0;
}

// 析构函数
template <class T> BTree<T>::~BTree() {}

/**
 * 指定结点插入关键字
 * @param node 指定终端结点
 * @param key 指定关键字（必需）
 * @param right 指定关键字的右子树（可选）
 * @return 错误码
 */
template <class T>
STATUS BTree<T>::insert(BNode<T> *node, T key, BNode<T> *right) {
  // 判断指定结点是否存在
  if (node == nullptr) {
    // 空树情况
    root = newNode();
    root->IsLeaf = true;
    root->Keys[0] = key;
    root->Num = 1;
    depth++;
    return OK;
  }

  // 直接插入（将大于 key 的关键字的元素右移）
  int i = node->Num - 1;
  for (; i >= 0 && node->Keys[i] > key; i--)
    node->Keys[i + 1] = node->Keys[i];
  node->Keys[i + 1] = key;
  node->Num++;
  LOG_DEBUG(">> 插入结点: %p\n", node);

  // 如果插入的结点为非终端结点, 则插入该结点后, 需要同时设置该结点的新右子树
  if (!node->IsLeaf) {
    if (right == nullptr)
      return ERR_NULL;

    // 对孩子结点同样进行拆分右移操作
    for (int j = node->Num; j > i + 2; j--) {
      node->Childs[j] = node->Childs[j - 1];
    }
    // 设置新插入结点的右侧子树
    node->Childs[i + 2] = right;
    LOG_DEBUG(">> 设置右子树结点: %p\n", right);
  }

  // 判断关键字个数是否超出最大值, 如果超出则分裂该结点
  if (node->Num > maxNum) {
    LOG_DEBUG(">> 分裂结点: %p\n", node);
    return split(node);
  }

  return OK;
}

/**
 * 删除指定结点的关键字
 * @param node 指定开始查找的结点
 * @param nindex 指定目标关键字在指定结点关键字数组中的索引
 * @param findex 指定指定结点在其父节点孩子数组中的索引（仅用于终端节点）
 * @return
 */
template <class T>
STATUS BTree<T>::remove(BNode<T> *node, int nindex, int findex) {
  // 情况1；非终端结点
  if (!node->IsLeaf) {
    int i = nindex;
    BNode<T> *p;

    // 找到前驱关键字
    p = node->Childs[i]; // 左孩子结点
    while (!p->IsLeaf && p) {
      i = p->Parent->Num;
      p = p->Childs[i]; // 最右孩子结点
    }

    // 使用前驱关键字替换目标关键字
    LOG_DEBUG(">> 使用前驱关键字 %d 替换 %d\n", p->Keys[p->Num - 1],
              node->Keys[nindex]);
    node->Keys[nindex] = p->Keys[p->Num - 1];

    // 删除前驱关键字
    return remove(p, p->Num - 1, i);
  }

  // 情况2；终端结点
  // 直接删除
  for (int i = node->Num - 1; i > nindex; i--) {
    node->Keys[i - 1] = node->Keys[i];
  }
  node->Num--;

  // 若删除后关键字个数小于最小值, 则需要合并该结点
  if (node->Num < minNum) {
    merge(node, findex);
  }
  return OK;
}

/**
 * 搜索指定关键字
 * @param key 指定关键字
 * @param res 返回目标节点的地址 (未找到时返回最末终端结点地址)
 * @param nindex 返回目标关键字在目标结点关键字数组的索引（需初始化为 -1）
 * @param findex 返回目标结点在其父节点孩子数组中的索引（需初始化为 -1）
 * @return 错误码（0 找到, 1 未找到）
 */
template <class T>
STATUS BTree<T>::_find(IN BNode<T> *node, IN T key, OUT BNode<T> *&res,
                       OUT int &nindex, OUT int &findex) {
  res = node;

  if (node == nullptr) {
    nindex = -1;
    return ERROR;
  }

  int i = 0;
  while (i < node->Num && node->Keys[i] < key)
    i++;

  if (node->Keys[i] == key) {
    nindex = i;
    LOG_DEBUG(">> 搜索操作 找到 key=%d\n", key);
    return OK;
  }

  // 判断是否为终端结点（无子节点）
  if (node->IsLeaf) {
    LOG_DEBUG(">> 搜索操作 未找到 key=%d\n", key);
    return ERROR;
  }

  // i == node->Num 或 node->Keys[i] > key 两种情况 操作相同
  findex = i;
  return _find(node->Childs[i], key, res, nindex, findex);
}

/**
 * 前序遍历
 * @param node 递归当前结点
 * @param f 回调函数
 */
template <class T> void BTree<T>::_traverse(BNode<T> *node, Callbak f) {
  if (node == nullptr)
    return;

  f(node);

  // 对于分支结点遍历子树
  if (!node->IsLeaf) {
    for (int i = 0; i <= node->Num; i++) {
      LOG_DEBUG(">> 进入结点 %p 的子树[%d]\n", node, i);
      _traverse(node->Childs[i], f);
    }
  }
}

/**
 * 层序遍历
 */
template <class T> void BTree<T>::Print() {
  LOG_DEBUG(">> 打印树\n");

  if (root == nullptr) {
    LOG_DEBUG("空树");
    return;
  }

  QueueLinkList<BNode<T> *> queue;
  BNode<T> *tmp = nullptr;
  int level = 0;

  // 将根节点入队
  queue.Push(root);
  while (!queue.IsEmpty()) {
    level++;

    // 为了将每层分开，需要从队列中提取全部结点
    int len = queue.Len();
    for (; len > 0; len--) {
      queue.Pop(tmp);

      if (!tmp->IsLeaf) {
        // 将当前节点的所有孩子结点依次入队
        for (int j = 0; j <= tmp->Num; j++) {
          queue.Push(tmp->Childs[j]);
        }
      }

      // 处理当前元素
      printf("[");
      for (int j = 0; j < tmp->Num - 1; j++) {
        printf("%d,", tmp->Keys[j]);
      }
      printf("%d] ", tmp->Keys[tmp->Num - 1]);
    }
    printf("\n");
  }
}

/**
 * 分裂指定结点（一般用于处理关键字数目大于最大值的情况）
 * 将中间关键字插入到父节点, 其余关键字分裂为左子树
 * @param node 指定结点
 * @return 错误码
 */
template <class T> STATUS BTree<T>::split(BNode<T> *node) {
  if (node == nullptr)
    return ERR_NULL;

  // 找到中间关键字位置
  int mid = node->Num / 2;

  // 创建新结点
  BNode<T> *tmp = newNode();
  tmp->Num = node->Num - mid - 1;
  tmp->IsLeaf = node->IsLeaf;

  // 将分割后的右侧关键字移动到新结点
  for (int i = 0; i < tmp->Num; i++) {
    tmp->Keys[i] = node->Keys[i + mid + 1];
  }

  // 判断是否为分支结点
  if (!node->IsLeaf) {

    for (int i = 0; i < node->Num - mid; i++) {
      // 更新所有孩子结点的父节点
      node->Childs[i + mid + 1]->Parent = tmp;

      // 将分割后的右侧孩子结点移动到新结点
      tmp->Childs[i] = node->Childs[i + mid + 1];
    }
  }

  // 缩短左侧
  node->Num = mid;

  // 情况1；父节点存在（当前结点非根节点）
  if (node->Parent) {
    // 将中间关键字插入到父节点中并指定其右子树
    tmp->Parent = node->Parent;
    return insert(node->Parent, node->Keys[mid], tmp);
  }

  // 情况2：父节点不存在（当前结点为根节点）
  root = newNode();
  depth++;
  // 指定为非终端节点
  root->IsLeaf = false;
  // 指定左子树
  root->Childs[0] = node;
  // 更新父节点
  node->Parent = root;
  tmp->Parent = root;
  // 将中间关键字插入到父节点中并指定其右子树
  return insert(root, node->Keys[mid], tmp);
}

/**
 * 合并指定结点（一般用于处理关键字数目小于最小值的情况）
 * 情况1：左/右兄弟结点关键字数目大于最小值，父下移，兄弟上移
 * 情况2：左/右兄弟结点关键字数目均等于最小值，父下移，兄弟左移
 * @param node 指定结点（必需）
 * @param findex 指定结点在其父结点孩子数组的索引
 * @return 错误码
 */
template <class T> STATUS BTree<T>::merge(BNode<T> *node, int findex) {
  BNode<T> *parent = node->Parent; // 父节点指针

  // 根节点情况
  if (parent == nullptr)
    return ERROR;

  // 左兄弟结点指针
  BNode<T> *left = (findex - 1 >= 0) ? parent->Childs[findex - 1] : nullptr;
  // 右兄弟结点指针
  BNode<T> *right =
      (findex + 1 >= parent->Num) ? parent->Childs[findex + 1] : nullptr;

  if (left != nullptr && left->Num > minNum) {
    // 情况1: 左兄弟结点结点数大于最小值, 向左兄弟结点借其最大关键字
    // 将该节点与左兄弟结点之间的双亲关键字插入目标结点
    node->Keys[node->Num] = parent->Keys[findex - 1];
    // 左兄弟结点最大关键字替换双亲关键字
    parent->Keys[findex - 1] = left->Keys[left->Num - 1];
    // 删除左兄弟结点最大关键字
    return remove(left, left->Num - 1, findex - 1);
  } else if (right != nullptr && right->Num > minNum) {
    // 情况2: 右兄弟结点结点数大于最小值, 向右兄弟结点借其最小关键字
    // 将该节点与左兄弟结点之间的双亲关键字插入目标结点
    insert(node, parent->Keys[findex], nullptr);
    // 右兄弟结点最小关键字替换双亲关键字
    parent->Keys[findex] = right->Keys[0];
    // 删除右兄弟结点最小关键字
    return remove(right, 0, findex + 1);
  } else {
    // 情况3: 左右兄弟结点结点数均等于最小值
    // 将双亲关键字和选择的兄弟结点中的关键字都合并到左侧
    // (左侧结点可能为当前结点或其左兄弟结点)
    BNode<T> *tleft = (left == nullptr) ? node : left;
    BNode<T> *tright = (left == nullptr) ? right : node;
    int index = (left == nullptr) ? findex : findex - 1;

    // 将双亲结点合并到左侧结点
    tleft->Keys[tleft->Num] = parent->Keys[index];
    tleft->Num++;

    // 将右侧结点合并到左侧结点
    for (int i = 0; i < tright->Num; i++) {
      tleft->Keys[tleft->Num + i] = tright->Keys[i];
      tleft->Childs[tleft->Num + i] = tright->Childs[i];
    }
    tleft->Num += tright->Num;
    tleft->Childs[tleft->Num] = tright->Childs[tright->Num];

    // 释放右侧结点
    free(tright);

    // 删除双亲结点的关键字及其右孩子
    for (int i = parent->Num - 1; i > index; i--) {
      parent->Keys[i - 1] = parent->Keys[i];
      parent->Childs[i] = parent->Childs[i + 1];
    }

    // 特殊情况：双亲结点的为根节点
    if (parent->Parent == nullptr) {
      parent->Num--;

      // 判断双亲结点中的元素个数是否已经为 0
      if (parent->Num == 0) {
        // 重置根节点
        tleft->Parent = nullptr;
        root = tleft;

        // 释放原根节点
        free(parent);
        depth--;
      }
      return OK;
    }

    // 找到双亲结点在其父节点中的索引
    node = parent;
    for (int i = 0; i <= node->Parent->Num; i++) {
      if (node->Parent->Childs[i] == node) {
        findex = i;
        break;
      }
    }
    node->Num--;

    // 判断双亲结点的关键字是否小于最小值
    if (node->Num < minNum)
      return merge(node, findex);
  }
  return OK;
}

#endif // ALGORITHM_LEARN_BTREE_H
