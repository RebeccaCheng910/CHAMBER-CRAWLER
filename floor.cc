#include "floor.h"
#include "textdisplay.h"
#include <iostream>
#include "object.h"
#include "chamber.h"
#include <memory>
#include "info.h"


using namespace std;

const int numChambers = 5;
   

// constructor 
Floor::Floor(istream *in) {
  td = new TextDisplay{in};
  // initialize vector of chamber pointers
  for (int i = 0; i < numChambers; ++i) {
    theChambers.emplace_back(make_unique<Chamber>());
  }
  // initilize default objects without populated items
  for (int i = 0; i < row; ++i) {
    vector <shared_ptr<Object>> v;
    theGrid.emplace_back(v);
    string line;
    getline(*in, line);
    for (int j = 0; j < col; ++j) {
      char c;
      if (line[j] != '-' || line[j] != '|' || line[j] != ' ' || line[j] != '#' || line[j] != '.'){ 
        c = '.';
      } else {
        c = line[j];
      }
      theGrid[i].emplace_back(make_shared<Object>(c));
    }
  }
  // set position of objects
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      theGrid[i][j]->setCords(i,j);
    }
  }
  // set up chamber
  findChamber();
  for (int i = 0; i < 5; ++i) {
  cout << "i: size is " << theChambers[i]->getSize()<< endl; 
  }
} 



Floor::~Floor() {
  delete td;
} 


// set up chamber, add floor tiles to chamber
void Floor::findChamber() {
  int chamberNum = 0;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (theGrid[i][j]->getInfo().type == '.' && visited[i][j] == false) {
        findWall (chamberNum, i, j); 
        ++chamberNum;
     }
   } 
 }

}


// recursive call, add Object ptr to Chamber until hit wall
void Floor::findWall(int chamberNum,int i, int j) {
  if (visited[i][j] == false || i < 0 || i > row || j < 0 || j > col) 
    return;
  visited[i][j] = true;
  if (theGrid[i][j]->getInfo().type != '.') return;
  if (theGrid[i][j]->getInfo().type == '.') { // add to Chamber
    theChambers[chamberNum]->addObjects(theGrid[i][j]);
  }
  findWall(chamberNum, i-1, j); // find upper
  findWall(chamberNum, i+1, j); // find below
  findWall(chamberNum, i, j-1); // find left
  findWall(chamberNum, i, j+1); /// find right
}
  
  
  
// test





// output floor
ostream &operator<< (ostream &out, const Floor &f) {
  out << *f.td;
  return out;
}
