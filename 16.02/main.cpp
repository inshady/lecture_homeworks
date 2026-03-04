#include <iostream>

template< class T > struct BiList {
  T val;
  BiList<T> * next;
  BiList<T> * prev;
};

template< class T > BiList<T>* add(BiList<T>* h, const T& d)
{
  if (!h) {
    BiList<T>* list = new BiList<T>{d, nullptr, nullptr};
    list->next = list;
    list->prev = list;
    return list;
  }

  BiList<T>* after = h->next;
  BiList<T>* list = new BiList<T>{d, after, h};
  h->next = list;
  after->prev = list;
  return list;
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

template< class T > BiList<T>* cut(BiList<T>* h) noexcept
{
  BiList<T>* ret = h->next;
  if (ret == h) {
    delete h;
    return nullptr;
  }
  ret->prev = h->prev;
  h->prev->next = ret;
  delete h;
  return ret;
}

template< class T > BiList<T>* eraseAfter(BiList<T>* h) noexcept
{
  BiList<T>* n = cut(h->next);
  h->next = n;
  if (n) {
    n->prev = h;
  }
  return n;
}

template< class T > BiList<T>* eraseBefore(BiList<T>* t) noexcept
{
  BiList<T>* n = cut(t->prev);
  t->prev = n;
  if (n) {
    n->next = t;
  }
  return n;
}

template< class T > BiList<T>* clear(BiList<T>* h, BiList<T>* t) noexcept
{
  BiList<T>* end = t->next;
  while (h && h != end) {
      h = cut(h);
    }
  return h;
}

template< class T > size_t size(BiList<T>* h)
{
  size_t c = 0;
  BiList<T>* start = h;
  c++;
  h = h->next;

  while(h != start) {
    c++;
    h = h->next;
  }
  return c;
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
  void operator()(int c) {
    result += std::to_string(c);
  }
};

int main()
{
  int n = 5;
  int* mass = new int[n];
  for (size_t i = 0; i < n; i++) {
    mass[i] = i + 1;
  }

  BiList<int>* nil = nullptr;
  BiList<int>* list = nullptr;
  for (size_t i = 0; i < n; i++) {
    list = add(list, mass[i]);
  }
  sum s = traverse(sum{}, list, list->prev);

  std::cout << s.result << "\n";

  clear(list, list->prev);

  delete[] mass;
}
