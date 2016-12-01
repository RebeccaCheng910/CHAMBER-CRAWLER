#include "textdisplay.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

TextDisplay::TextDisplay(istream *in) {
  for (int i = 0; i < 25; ++i) {
    vector<char> v;
    theDisplay.emplace_back(v);
    string line;
    getline(*in, line);
    for (int j = 0; j < 79; ++j) {
      char c;
      // translate numbers to items
      if (line[j]>='0' && line[j] <= '5') { 
        c = 'P';
      } else if (line[j] >='6' && line[j] <= '9') { 
        c = 'G';
      } else {
        c = line[j];
      }
      theDisplay[i].emplace_back(c);
    }
  }
}

char TextDisplay::getTD (int row, int col) {
	return theDisplay[row][col];
}

ostream &operator<<(ostream&out, const TextDisplay &td) {
  for (int i = 0; i < 25; ++i) {
    for (int j = 0; j < 79; ++j) {
      out << td.theDisplay[i][j];
     }
    out << endl;
   }
  return out;
}
