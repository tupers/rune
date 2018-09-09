#ifndef RUNEACTION_H
#define RUNEACTION_H

#include <string>
#include <map>

#include "creature.h"


namespace Rune
{
       typedef void (*actionFunc)(int);


       class actionRegister
       {
	       public:
		       static map<std::string, actionFunc> reg;
		       actionRegister();
		       ~actionRegister(){}
       };
		       
}

#endif /* RUNEACTION_H */
