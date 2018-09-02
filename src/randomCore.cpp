#include "randomCore.h"

RandomCore::RandomCore()
{
	engine.seed(time(0));

	randomCnt++;
	
	return;
}

RandomCore::~RandomCore()
{
	return;
}

void RandomCore::refresh()
{
	if(randomCnt > 10)
		engine.seed(time(0));
	engine();

	return;
}

int RandomCore::generate(int min, int max)
{
	refresh();
	std::uniform_int_distribution<signed> u(min,max);
	return u(engine);
}

float RandomCore::generate(float min, float max)
{
	refresh();
	std::uniform_real_distribution<float> u(min,max);
	return u(engine);
}
