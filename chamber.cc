#include "chamber.h"
#include <memory>

using namespace std;

void Chamber::addObjects(shared_ptr<Object> o) {
  theChamber.emplace_back(o);
}

// return the size of chamber
int Chamber::getSize() {
  return theChamber.size();
}

