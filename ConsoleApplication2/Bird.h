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
	float distanceHorizontally;
	float distanceVertically;

	int flapCount = 0;
	int maxFlapCount = 0;
	int fitnessPoint = 0;
	int maxfitnessPoint = 0;
	float lastLevelPosition = 0.0f;


public:
	Bird(float pos, float vel, float acc) :position(pos), velocity(vel), acceleration(acc) {}

	float getPosition() { return position; }
	float getVelocity() { return velocity; }
	int getFlapCount() { return flapCount; }
	int getMaxFlapCount() { return maxFlapCount; }
	float getAcceleration() { return acceleration; }
	bool isAlive() { return imAlive; }
	int getFitnessPoint() { return fitnessPoint; }

	void setDistanceHorizontally(float distance);
	float getDistanceHorizontally();
	void actualiseDistanceVertically(float levelHigh);
	float getDistanceVertically();


	void updatePosition(float elapsedTime);
	bool checkIfBirdHasMovedFromLastCheck(float levelPosition);
	void flap();
	void incrementFitnessPoint() { ++fitnessPoint; }
	void reborn(float pos, float vel);
	void die();
};
