#ifndef STORYFLOW_H
#define STORYFLOW_H

#include <string>
#include <vector>

#include "type.h"

using namespace std;

class StoryFlow
{
private:
	typedef struct
	{
		int elapse;
		vector<string> text;
	}textUnit;


	typedef struct
	{
		string title;
		int elapse;
		vector<textUnit> paragraph;
	}content;

	content flow;
	int lastIdx;
	

public:
	StoryFlow(){lastIdx = 0;}
	StoryFlow(string filePath);
	int load(string filePath);
	void playTitle();
	void playParagraph(int index);
	void play();
	virtual void display(string text);
	virtual ~StoryFlow();
};

#endif /* STORYFLOW_H */
