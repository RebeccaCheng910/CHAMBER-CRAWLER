#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include <string>
#include <memory>

class Enemy;

// abstract class
class Player: public Character {
  int goldValue = 0;
  std::string action;
  bool isDead = false;
protected:
  int maxHP;

public:
  Player(); // constructor
 // int getHP() override;
 // int getAtk() override;
//  int getDef() override;
  std::string getAction();
  void setAction(std::string);
  virtual int getGold();   // goblin needs to overload
  virtual void setGold(int); 
  virtual bool getStatus();   
  virtual void beAttackedBy(const std::shared_ptr<Enemy> &);
  virtual ~Player() = 0;   // to make Player abstract
};

#endif
