#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <iostream>

#include "creature.h"

using namespace std;

class Event
{
public:
	typedef struct
	{
		Creature *sender;
		Creature *receiver;
	}actionParams;
	
	Event();
	virtual ~Event();
private:

	typedef void (*actionFun)(actionParams&);

	void action_battle(actionParams &params);

	static map<string, actionFun> actionRegister;
};

#endif /* EVENT_H */
