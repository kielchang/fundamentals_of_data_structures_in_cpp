#include <iostream> // std::cout
#include <numeric>  // std::accumulate

using namespace std;

template <class T>
class Chain;
template <class T>
class ChainIterator;

template <class T>
class ChainNode
{
  friend class Chain<T>;
  friend class ChainIterator<T>;

public:
  ChainNode<T>(T e) { data = e; }

private:
  T data;
  ChainNode<T> *link;
};

template <class T>
class Chain
{
public:
  Chain() { first = 0; }
  void InsertBack(const T &e);
  void Concatenate(Chain<T> &b);
  void Reverse();

  void PrintChain();

  ChainIterator<T> begain() { return ChainIterator<T>(first); }
  ChainIterator<T> end() { return ChainIterator<T>(0); }

private:
  ChainNode<T> *first;
  ChainNode<T> *last;
};

template <class T>
void Chain<T>::InsertBack(const T &e)
{
  if (first)
  {
    last->link = new ChainNode<T>(e);
    last = last->link;
  }
  else
  {
    first = last = new ChainNode<T>(e);
  }
}

template <class T>
void Chain<T>::Concatenate(Chain<T> &b)
{
  if (first)
  {
    last->link = b.first;
    last = b.last;
  }
  else
  {
    first = b.first;
    last = b.last;
  }
  b.first = b.last = 0;
}

template <class T>
void Chain<T>::Reverse()
{
  ChainNode<T> *current = first, *previous = 0;

  while (current)
  {
    ChainNode<T> *r = previous;
    previous = current;
    current = current->link;
    previous->link = r;
  }
  first = previous;
}

// use to print result of Chain Operations
template <class T>
void Chain<T>::PrintChain()
{

  // 12 2 5
  // ChainIterator<T> f1 = begain();

  // cannot new ??
  // ChainIterator<T> f2 = new ChainIterator<T>();

  // what diff between new ChainIterator and ChainIterator??

  // cout << "*f1++: " << *f1++ << endl;
  // cout << "*f1++: " << *f1 << endl;

  ChainIterator<T> current = begain();
  // cout << "f1 == current: " << (f1 == current) << endl;
  ChainIterator<T> e = end();
  while (current != e)
  {
    cout << *current << " -> ";
    current++;
  }
  cout << endl;
};

template <class T>
class ChainIterator
{
public:
  ChainIterator(ChainNode<T> *startNode = 0) { current = startNode; }

  T &operator*() const { return current->data; }
  T *operator->() const { return &current->data; }

  ChainIterator &operator++()
  {
    current = current->link;
    return *this;
  }
  ChainIterator operator++(int)
  {
    ChainIterator old = *this;
    current = current->link;
    return old;
  }

  bool operator!=(const ChainIterator right) const
  {
    return current != right.current;
  }
  bool operator==(const ChainIterator right) const
  {
    return current == right.current;
  }

private:
  ChainNode<T> *current;
};

int main()
{
  // create Chain c1: 1 -> 2 -> 3
  Chain<int> c1;
  c1.InsertBack(1);
  c1.InsertBack(2);
  c1.InsertBack(3);

  cout << "c1: ";
  c1.PrintChain();

  // use STL accumulate function to get c1 summary
  int sum = accumulate(c1.begain(), c1.end(), 0);
  cout << "c1 sum is " << sum << endl;

  // create Chain c2: 4 -> 5 -> 6
  Chain<int> c2;
  c2.InsertBack(4);
  c2.InsertBack(5);
  c2.InsertBack(6);

  cout << "c2: ";
  c2.PrintChain();

  // concatenate c1 and c2
  c1.Concatenate(c2);
  cout << "c1: ";
  c1.PrintChain();
  cout << "c2: ";
  c2.PrintChain();

  // reverse c1
  c1.Reverse();
  cout << "c1: ";
  c1.PrintChain();
}