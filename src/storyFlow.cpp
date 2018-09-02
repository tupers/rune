#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>

#include "rapidjson/document.h"

#include "storyFlow.h"

#define checkMember(obj,name)						\
       do{								\
		if((!obj.IsObject()) || (!obj.HasMember(name)))	\
			return RUNE_PARSEERR;				\
       }while(0)


#define checkArray(obj,name)						\
       do{								\
		if((!obj.IsObject())					\
		|| (!obj.HasMember(name))				\
	        || (!obj[name].IsArray()))					\
			return RUNE_PARSEERR;				\
       }while(0)

StoryFlow::StoryFlow(string filePath)
{
	lastIdx = 0;
	load(filePath);
}

StoryFlow::~StoryFlow()
{
	return;
}

int StoryFlow::load(string filePath)
{
	//file>>string
	ifstream jsonFile;
	string jsonString;

	jsonFile.open(filePath.data(),ifstream::in);
	if(!jsonFile.is_open())
		return RUNE_OPENFILEERR;
	string line;
	while( getline(jsonFile,line))
		jsonString.append(line + "\n");
	jsonFile.close();
	
	//parse string to json obj
	rapidjson::Document obj;
	obj.Parse(jsonString.c_str());
	
	checkMember(obj, "title");
	flow.title = obj["title"].GetString();
	
	checkMember(obj, "elapse");
	flow.elapse = obj["elapse"].GetInt();
	
	checkArray(obj, "content");
	rapidjson::Value &content = obj["content"];

	for(size_t i = 0; i < content.Size(); i++)
	{
		textUnit unit;
		rapidjson::Value &u = content[i];
		
		checkMember(u, "elapse");
		unit.elapse = u["elapse"].GetInt();

		checkArray(u, "text");
		rapidjson::Value &text = u["text"];
		for(size_t j = 0; j < text.Size(); j++)
			unit.text.push_back(text[j].GetString());

		flow.paragraph.push_back(unit);
	}

	return RUNE_SUCCESS;
}

void StoryFlow::playTitle()
{
	display(flow.title);
	sleep(flow.elapse);
}

void StoryFlow::playParagraph(int index)
{
	if(index > (flow.paragraph.size() - 1))
		return;

	lastIdx = index;
	textUnit u = flow.paragraph[index];
	for(auto text : u.text)
	{
		display(text);
		sleep(u.elapse);
	}
}

void StoryFlow::play()
{
	if(lastIdx == 0)
	{
		playTitle();
		if(flow.paragraph.size() > 0)
			playParagraph(0);
	}
	else
		playParagraph(lastIdx + 1);
}

void StoryFlow::display(string text)
{
	cout << text << endl;
}
