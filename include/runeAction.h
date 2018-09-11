#ifndef RUNEACTION_H
#define RUNEACTION_H

#include <string>
#include <map>

#include "creature.h"


namespace Rune
{
	using namespace Creature::propertyUnit propertyUnit;

       typedef void (*actionFunc)(Creature *src, Creature *dst, map<std::string, propertyUnit>& resultList);

       //actions:
       

       class actionRegister
       {
	       public:
		       static map<std::string, actionFunc> reg;
		       actionRegister();
		       ~actionRegister(){}
       };
		       
}

#endif /* RUNEACTION_H */
