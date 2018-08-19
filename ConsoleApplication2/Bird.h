#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Bird {
	bool imAlive = 1;
	float position;
	float velocity;
	const float acceleration;
	int flapCount = 0;
	int maxFlapCount = 0;
public:
	Bird(float pos, float vel, float acc) :position(pos), velocity(vel), acceleration(acc) {}

	float getPosition() { return position; }
	float getVelocity() { return velocity; }
	int getFlapCount() { return flapCount; }
	int getMaxFlapCount() { return maxFlapCount; }
	float getAcceleration() { return acceleration; }
	bool isAlive() { return imAlive; }

	void updatePosition(float elapsedTime);
	void flap();
	void reborn(float pos, float vel);
	void die();
};
