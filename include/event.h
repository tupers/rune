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
		Creature *attacker;
		Creature *defender;
	}actionParams;
	
	Event();
	virtual ~Event();

	void eventLog(string &str);
private:

	typedef void (Event::*pActionFun)(actionParams&);
	
	//action: battle
	void action_battle(actionParams &params);
	

	static map<string, pActionFun> actionRegister;
};

#endif /* EVENT_H */
