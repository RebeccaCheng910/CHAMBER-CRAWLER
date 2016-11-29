#include "floor.h"
#include "textdisplay.h"
#include <iostream>

using namespace std;

Floor::Floor(istream *in) {
//  char c;
//  for (int i = 0; i < row; ++i) {
//    vector <Object> v;
//    theGrid.emplace_back(v);
//    for (int j = 0; j < col; ++j) {
  std::unique_ptr<TextDisplay> td(new TextDisplay(in));
} 

Floor::~Floor() {
  delete td;
} 

// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}
