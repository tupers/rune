#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <map>
#include <vector>

#include "type.h"
#include "randomCore.h"

using namespace std;

class Creature
{
public:
	typedef struct
	{
		float value;
	}propertyUnit;

	typedef struct
	{
		string id;
	}componentUnit;

	typedef struct
	{
		float value;
		//property
	}damageUnit;

	typedef struct
	{
		Creature* source;
		vector<damageUnit> list;
	}damageInfo;

	
private:
	string id;
	map<string, propertyUnit> propertyList;
	map<string, componentUnit> componentList;

	RandomCore randomEngine;

public:
	Creature(const string &s = "none"):id(s){
		propertyUnit b_hp = {
			.value = 1
		};
		propertyList["basic_health"] = b_hp;
	};

	virtual void refresh();
	virtual int load(string jsonPath, string id);
	
	string info();
	string getId(){return id;}

	virtual ~Creature();
	
	//action
	virtual damageInfo attack();
	virtual void defence(const damageInfo& damage);
	
};

#endif /* CREATURE_H */
