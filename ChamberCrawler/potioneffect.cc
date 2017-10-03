#include "potioneffect.h"
#include "decorator.h"
#include "player.h"
#include "drow.h"

using namespace std;

// constructor
PotionEffect::PotionEffect(int type, shared_ptr<Player> p): Decorator{p} {
// set effects of potion
  if (type == 0) {  // Restore Health (RH)
      if (dynamic_pointer_cast<Drow>(p->getBase())) {
        HP += 10 * 1.5;
      } else {
      HP += 10;
      }
      if (HP > maxHP) {HP = maxHP;}
   } else if (type == 1) {  // Boost Attack (BA) 
      effectAtk = 5;
   } else if (type == 2) {  // Boost Defence (BD)
      effectDef = 5;
   } else if (type == 3) {  // Poison Health (PH) 
      if (dynamic_pointer_cast<Drow>(p->getBase())) {
         HP -=10 * 1.5;
       } else {
         HP -= 10;
       }
      if (HP < 0) {HP = 0;}
   } else if (type == 4) {  // Wound Attack (WA)
      effectAtk = -5;
   } else if (type == 5) {  // Wound Defence (WD)
      effectDef = -5;
   }

}

int PotionEffect::getHP() {return HP;}
int PotionEffect::getAtk() {
  if (dynamic_pointer_cast<Drow>(component->getBase())) {
    return component->getAtk() + 1.5 * effectAtk;
}
  return component->getAtk() + effectAtk;
}
int PotionEffect::getDef() {
  if (dynamic_pointer_cast<Drow>(component->getBase())){
    return component->getDef() + 1.5 * effectDef;
}
return component->getDef() + effectDef;}


shared_ptr<Player> PotionEffect::getBase() {return component->getBase();}
