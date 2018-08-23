#pragma once
#include "Bird.h"

void Bird::setDistanceHorizontally(float distance) {
	distanceHorizontally = distance;
}

float Bird::getDistanceHorizontally() {
	return distanceHorizontally;
}

void Bird::actualiseDistanceVertically(float levelHigh) {
	distanceVertically = position - (levelHigh);
}

float Bird::getDistanceVertically() {
	return distanceVertically;
}

void Bird::updatePosition(float elapsedTime) {
	if (imAlive) {
		velocity += acceleration * elapsedTime;
		position += velocity * elapsedTime;
	}
}

bool Bird::checkIfBirdHasMovedFromLastCheck(float levelPosition) {
	if ((int)levelPosition != (int)lastLevelPosition) {
		lastLevelPosition = levelPosition;
		return true;
	}
	return false;
}

void Bird::flap() {
	if (imAlive) {
		velocity = -50.0f + (rand() % 2);
		++flapCount;
	}
}

void Bird::reborn(float pos, float vel) {
	if (!imAlive) {
		imAlive = true;
		position = pos;
		velocity = vel;
		flapCount = 0;
		fitnessPoint = 0;
	}
}

void Bird::die() {
	imAlive = false;
	if (flapCount > maxFlapCount) {
		maxFlapCount = flapCount;
	}
	if (fitnessPoint > maxfitnessPoint) {
		maxfitnessPoint = fitnessPoint;
	}
}

