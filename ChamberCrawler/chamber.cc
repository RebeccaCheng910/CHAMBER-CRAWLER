#include "chamber.h"
#include "object.h"
#include <memory>
#include <cstdlib>
#include "info.h"

using namespace std;

void Chamber::addObjects(shared_ptr<Object> o) {
  theChamber.emplace_back(o);
}

// return the size of chamber
int Chamber::getSize() {
  return theChamber.size();
}

// random generate a chember's position
void Chamber::generatePosition(Object *o) {
  int n = rand() % theChamber.size();
  int row = theChamber[n]->getInfo().row;
  int col = theChamber[n]->getInfo().col;
  o->setCords(row, col);
  theChamber.erase(theChamber.begin() + n);    // delete object ptr
}
