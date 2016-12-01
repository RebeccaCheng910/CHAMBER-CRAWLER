#include <iostream>
#include <vector>

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
public:
	char getTD (int, int); 
  TextDisplay(std::istream *) ;  // read in a file and initialize 
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
