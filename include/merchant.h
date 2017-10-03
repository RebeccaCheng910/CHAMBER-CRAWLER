#ifndef _MERCHANT_H_
#define _MERCHANT_H_
   
#include "enemy.h"
#include <string>
    
   
class Merchant: public Enemy {
	static bool isHostile; 
public:
	Merchant(int, int, char);
	~Merchant();
	bool getHostility();
	void setHostility(bool status);
}; 

#endif
