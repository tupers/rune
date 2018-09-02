#include <iostream>

#include "creature.h"
#include "version.h"
#include "logo.h"
#include "storyFlow.h"

int main(int argc, char **argv)
{
	cout<<"test started ..."<<endl;
	Creature* a = new Creature("AA");
	Creature* b = new Creature("BB");	

	cout<<a->info()<<endl;
	cout<<b->info()<<endl;

	string path = "/home/tupers/rune/char/darkIsland.json";
	auto ret = a->load(path, "Coast Walker");
	if(ret)
		cout<<"err: "<<ret<<endl;
	ret = b->load(path, "Coast Walker");
	if(ret)
		cout<<"err: "<<ret<<endl;

	cout<<"start attack !!!"<<endl;
	auto dmg = a->attack();
	b->defence(dmg);

	cout<<"launch version "<<RUNE_VERSION<<"..."<<endl;
	cout<<gLogo;

	StoryFlow* flow = new StoryFlow("/home/tupers/rune/story/01_onTheBeach.json");

	flow->play();	


	return 0;
}
