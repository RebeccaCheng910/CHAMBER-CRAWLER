#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"
#include <string>
#include "gold.h"
#include <memory>


class Dragon: public Enemy {
	std::shared_ptr<Gold> g;
public:
	Dragon(int, int, char);
  ~Dragon();
	void setHoard (const std::shared_ptr<Gold> &);
  std::shared_ptr<Gold> getHoard();
};

#endif 

