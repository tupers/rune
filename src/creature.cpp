#include <sstream>
#include <fstream>

#include "rapidjson/document.h"

#include "creature.h"

#define loadPropertyFromJson(propName,json)				\
	do{ 								\
		propertyUnit u;						\
		if(json.HasMember(propName))			\
		{							\
			u.value = json[propName].GetFloat();	\
			propertyList[propName] = u;			\
		}							\
	}while(0)	

Creature::~Creature()
{

}

void Creature::refresh()
{
	//process hp
	float hp_val = propertyList["basic_health"].value;
	if(propertyList.find("strength") != propertyList.end()
			&& propertyList.find("health_factor") != propertyList.end())
		hp_val += propertyList["strength"].value * propertyList["health_factor"].value;

	propertyUnit hp = {
		.value = hp_val
	};

	propertyList["health"] = hp;

	return;
}

int Creature::load(string jsonPath, string id)
{
	//file>>string
	ifstream jsonFile;
	string jsonString;

	jsonFile.open(jsonPath.data(),ifstream::in);
	if(!jsonFile.is_open())
		return RUNE_OPENFILEERR;
	string line;
	while( getline(jsonFile,line))
		jsonString.append(line + "\n");
	jsonFile.close();
	
	//parse string to json obj
	rapidjson::Document obj;
	obj.Parse(jsonString.c_str());
	if((!obj.IsObject()) || (!obj.HasMember("creature")))
		return RUNE_PARSEERR;
	rapidjson::Value &creatureGroup = obj["creature"];
	if(!creatureGroup.IsArray())
		return RUNE_PARSEERR;

	//find specified config and fill property
	bool isFind = false;
	for(size_t i = 0; i < creatureGroup.Size(); i++)
	{
		rapidjson::Value &creature = creatureGroup[i];
		if(creature.HasMember("id")
				&& creature["id"].IsString()
				&& (id.compare(creature["id"].GetString()) == 0))
		{
			isFind = true;

			loadPropertyFromJson("basic_health", creature);
			loadPropertyFromJson("basic_attack", creature);
			loadPropertyFromJson("basic_defence", creature);
			loadPropertyFromJson("basic_speed", creature);
		}
	}

	if(!isFind)
		return RUNE_LOADERR;

	//refresh all property
	refresh();

	return RUNE_SUCCESS;
}


string Creature::info()
{
	stringstream info;
	info << "creature name :"<<id;
	return info.str();
}

Creature::damageInfo Creature::attack()
{
	damageInfo info;
	info.source = this;

	damageUnit u;
	float b_atk = propertyList["basic_attack"].value;
	int range = b_atk * 0.01;
	range = range > 0 ? range : 1;
	u.value = b_atk + randomEngine.generate(-range, range);
	info.list.push_back(u);	
	
	return info;
}

void Creature::defence(const damageInfo &damage)
{
	int dmgs = 0;
	float b_def = propertyList["basic_defence"].value;
	
	for( auto u : damage.list)
	{
		float dmg = u.value - b_def;
		dmgs += dmg > 0 ? dmg : 0;
	}

	//cout << "total damage :" << dmgs << " ! " << "from " << damage.source->getId() << endl;
	//calculate
	propertyList["health"].value -= dmgs;
	return;
}
