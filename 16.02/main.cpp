#include <iostream>

template< class T > struct BiList {
  T val;
  BiList<T> * next;
  BiList<T> * prev;
};

template< class T > BiList<T>* addHead(BiList<T>* h, const T& d)
{
  BiList<T>* head = new BiList<T>{d, h, nullptr};
  if (h) {
    h->prev = head;
  }
  return head;
}

template< class T > BiList<T>* addTail(BiList<T>* t, const T& d)
{
  BiList<T>* tail = new BiList<T>{d, nullptr, t};
  if (t) {
    t->next = tail;
  }
  return tail;
}

template< class T > BiList<T>* insertAfter(BiList<T>* left, const T& d)
{
  BiList<T>* right = left->next;
  BiList<T>* ins = new BiList<T>{d, right, left};
  left->next = ins;
  if (right) {
    right->prev = ins;
  }
  return ins;
}

template< class T > BiList<T>* insertBefore(BiList<T>* right, const T& d)
{
  BiList<T>* left = right->prev;
  BiList<T>* ins = new BiList<T>{d, right, left};
  right->prev = ins;
  if (left) {
    left->next = ins;
  }
  return ins;
}

template< class T > BiList<T>* cutHead(BiList<T>* h) noexcept
{
  BiList<T>* ret = h->next;
  if (ret) {
    ret->prev = nullptr;
  }
  delete h;
  return ret;
}

template< class T > BiList<T>* cutTail(BiList<T>* t) noexcept
{
  BiList<T>* ret = t->prev;
  if (ret) {
    ret->next = nullptr;
  }
  delete t;
  return ret;
}

template< class T > BiList<T>* eraseAfter(BiList<T>* h) noexcept
{
  BiList<T>* n = cutHead(h->next);
  h->next = n;
  if (n) {
    n->prev = h;
  }
  return n;
}

template< class T > BiList<T>* eraseBefore(BiList<T>* t) noexcept
{
  BiList<T>* n = cutTail(t->prev);
  t->prev = n;
  if (n) {
    n->next = t;
  }
  return n;
}

template< class T > BiList<T>* clear(BiList<T>* h, BiList<T>* t) noexcept
{
  while (h != t) {
    h = cutHead(h);
  }
  return h;
}

template< class T, class F > F traverse(F f, BiList<T>* h, BiList<T>* t)
{
  for (; h != t; h = h->next) {
    f(h->val);
  }
  return f;
}
struct sum {
  std::string result = "";
  void operator()(char c) {
    result += c;
  }
};

int main()
{
  int n = 5;
  int* mass = new int[n];
  for (size_t i = 0; i < n; i++) {
    mass[i] = i + 1;
  }

  BiList<int>* tail = new BiList<int>{mass[0], nullptr, nullptr};
  BiList<int>* head = tail;
  BiList<int>* nil = nullptr;

  for (size_t i = 1; i < n; i++) {
    tail = addTail(tail, mass[i]);
  }
  sum s = traverse(sum{}, head, nil);

  delete[] mass;
}
