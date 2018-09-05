#ifndef DRAMA_H
#define DRAMA_H

#include "creature.h"

/* this class can implement whole play.
 * scenario is a big tank for whole things. this class can hold or make few scenarios and make a list for stage to play
 * event is kind of carrier for few relative actions
 * action is the smallest unit for interaction between creatures or characters
 * trigger is a condition or interuption in the event.It can call or be called by action
*/

typedef struct
{
	Creature *sender;
	Creature *receiver;
}actionParams;

class Drama
{
private:
	void action_battle(actionParams &params);


public:
	Drama();
	virtual ~Drama();
};

#endif /* DRAMA_H */
