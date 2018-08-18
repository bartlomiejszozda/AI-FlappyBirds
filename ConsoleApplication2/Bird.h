#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Bird {
	//static float initialPosition;
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

	void updatePosition(float elapsedTime) {
		if (imAlive) {
			velocity += acceleration * elapsedTime;
			position += velocity * elapsedTime;
		}
	}

	void flap() {
		if (imAlive) {
			velocity = -50.0f + (rand() % 10);
			++flapCount;
		}
	}
	void reborn(float pos, float vel) {
		if (!imAlive) {
			imAlive = true;
			position = pos;
			velocity = vel;
			flapCount = 0;
		}
	}
	void die() {
		imAlive = false;
		if (flapCount > maxFlapCount) {
			maxFlapCount = flapCount;
		}
	}
};

//float Bird::initialPosition = 0;
//int Bird::maxFlapCount = 0;
