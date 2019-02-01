#include "List.h"
#include <iostream>
using namespace std;
int main() {
  List<int> l1, l2;
  l1.insertBack(1);
  l1.insertBack(3);
  l1.insertBack(4);
  l1.insertBack(6);
  l2.insertBack(2);
  l2.insertBack(5);
  l2.insertBack(7);
  l1.mergeWith(l2);
  l1.print(cout);
  return 0;
}
