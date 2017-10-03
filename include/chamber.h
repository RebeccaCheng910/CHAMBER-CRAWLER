#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <memory>

class Object;

class Chamber {
  std::vector<std::shared_ptr<Object>> theChamber;
 
public:
   void addObjects(std::shared_ptr<Object>); // add an object to the chamberi
   int getSize(); // return the size of Chamber
   void generatePosition(Object *);
};

#endif
