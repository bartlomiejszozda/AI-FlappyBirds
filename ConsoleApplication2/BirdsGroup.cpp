#pragma once
#include "BirdsGroup.h"

BirdsGroup::BirdsGroup(int numOfBirds, float pos, float vel, float acc) {
	srand(time(NULL));
	birds = std::vector<Bird>(numOfBirds, Bird(pos, vel, acc));
	numberOfBirds = numberOfLivingBirds = numOfBirds;
}

void BirdsGroup::updatePosition(float elapsedTime) {
	for (Bird& b : birds) {
		b.updatePosition(elapsedTime);
	}
}

void BirdsGroup::setDistanceHorizontally(float distance) {
	for (Bird& b : birds) {
		b.setDistanceHorizontally(distance);
	}
}

void BirdsGroup::actualiseDistanceVertically(float levelHigh) {
	for (Bird& b : birds) {
		b.actualiseDistanceVertically(levelHigh);
	}
}

void BirdsGroup::flap() {
	for (Bird& b : birds) {
		b.flap();
	}
}

void BirdsGroup::reborn(float pos, float vel) {
	numberOfLivingBirds = numberOfBirds;
	for (Bird& b : birds) {
		b.reborn(pos, vel);
	}
}

void BirdsGroup::birdDie(int birdNumber) {
	if (birds[birdNumber].getFlapCount() > maxBestFlapCount) {
		maxBestFlapCount = birds[birdNumber].getFlapCount();
	}
	if (birds[birdNumber].getFitnessPoint() > maxBestFitnessPoint) {
		maxBestFitnessPoint = birds[birdNumber].getFitnessPoint();
	}
	birds[birdNumber].die();
	if (numberOfLivingBirds > 0) {
		--numberOfLivingBirds;
	}
	else
		throw exception();
}

int BirdsGroup::getBestFlapCount() {
	for (Bird& b : birds) {
		if (b.isAlive())
			return b.getFlapCount();
	}
}

int BirdsGroup::getBestFitnessPoint() {
	for (Bird& b : birds) {
		if (b.isAlive())
			return b.getFitnessPoint();
	}
	return 0;
}