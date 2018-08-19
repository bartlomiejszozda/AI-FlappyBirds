#pragma once
#include <vector>
#include "Bird.h"
class BirdsGroup {
	std::vector<Bird> birds;
	int numberOfBirds;
	int numberOfLivingBirds;
	int maxBestFlapCount = 0;
public:
	BirdsGroup(int numOfBirds, float pos, float vel, float acc);

	Bird& operator[](int birdNumber) {
		return birds[birdNumber];
	}

	int getMaxBestFlapCount() {
		return maxBestFlapCount;
	}

	int getBestFlapCount();

	bool allBirdsDied() {
		return numberOfLivingBirds == 0;
	}

	void updatePosition(float elapsedTime);

	void flap();
	void reborn(float pos, float vel);
	void birdDie(int birdNumber);
};