#ifndef RANDOMCORE_H
#define RANDOMCORE_H

#include <iostream>
#include <random>
#include <ctime>

class RandomCore
{
private:
	std::default_random_engine engine;
	int randomCnt;
	void refresh();
public:
	RandomCore();
	int generate(int min, int max);
	float generate(float min, float max);
	virtual ~RandomCore();
};

#endif /* RANDOMCORE_H */
