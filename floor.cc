#include "floor.h"
#include "textdisplay.h"
#include <iostream>
#include "object.h"
#include <memory>

using namespace std;

// constructor 
Floor::Floor(istream *in) {
  td = new TextDisplay{in};
  // initilize default objects without populated items
  for (int i = 0; i < row; ++i) {
    vector <unique_ptr<Object>> v;
    theGrid.emplace_back(move(v));

    string line;
    getline(*in, line);
    for (int j = 0; j < col; ++j) {
      char c;
      if (line[j] != '-' || line[j] != '|' || line[j] != ' ' || line[j] != '#' || line[j] != '.'){ 
        c = '.';
      } else {
        c = line[j];
      }
      theGrid[i].emplace_back(make_unique<Object>(i,j,c));
    }
  }
} 

Floor::~Floor() {
  delete td;
} 

// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}
