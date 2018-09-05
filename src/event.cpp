#include "event.h"

map<string, Event::pActionFun> Event::actionRegister;

#define registerAction(name,fun)						\
	do{									\
		if(actionRegister.find(name) == actionRegister.end())		\
			actionRegister[name] = &Event::fun;			\
	}while(0)

Event::Event()
{
	//add or check actionRegister;
	registerAction("battle",action_battle);
	
}

void Event::action_battle(actionParams &params)
{
	//init things
	float attacker_interval = 1/params.attacker->getSpeed();
	float defender_interval = 1/params.defender->getSpeed();
	float attacker_timeline = 0.0;
	float defender_timeline = 0.0;

	//battle loop:
	while(true)//or else like trigger
	{
		bool reverse = false;
		//decide sequence
		if(attacker_timeline > defender_timeline)
			reverse = true;	

		Creature *cAttacker = reverse ? params.defender : params.attacker;
		Creature *cDefender = reverse ? params.attacker : params.defender;
		float &timeline = reverse ? defender_timeline : attacker_timeline;
		float &interval = reverse ? defender_interval : attacker_interval;

		//calculate forward damage
		//..
		if(cAttacker->getHealth() <= 0)
			break;

		//calculate strike damage
		auto dmg = cAttacker->attack();
		cDefender->defence(dmg);

		if(cDefender->getHealth() <= 0)
			break;

		if(cAttacker->getHealth() <= 0)
			break;

		//calculate backward damage
		//..
		if(cAttacker->getHealth() <= 0)
			break;

		//refresh timeline
		timeline += interval;
	}
}
