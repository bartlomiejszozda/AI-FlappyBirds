#pragma once
#include <vector>
#include "Bird.h"
class BirdsGroup {
	std::vector<Bird> birds;
	int numberOfBirds;
	int numberOfLivingBirds;
	int maxBestFlapCount = 0;
public:
	BirdsGroup(int numOfBirds, float pos, float vel, float acc) {
		srand(time(NULL));
		birds = std::vector<Bird>(numOfBirds, Bird(pos, vel, acc));
		numberOfBirds = numberOfLivingBirds = numOfBirds;
	}

	int getMaxBestFlapCount() {
		return maxBestFlapCount;
	}

	void updatePosition(float elapsedTime) {
		for (Bird& b : birds) {
			b.updatePosition(elapsedTime);
		}
	}

	void flap() {
		for (Bird& b : birds) {
			b.flap();
		}
	}
	void reborn(float pos, float vel) {
		numberOfLivingBirds = numberOfBirds;
		for (Bird& b : birds) {
			b.reborn(pos, vel);
		}
	}
	Bird& operator[](int birdNumber) {
		return birds[birdNumber];
	}
	void birdDie(int birdNumber) {
		if (birds[birdNumber].getFlapCount() > maxBestFlapCount) {
			maxBestFlapCount = birds[birdNumber].getFlapCount();
		}
		birds[birdNumber].die();
		if (numberOfLivingBirds > 0) {
			--numberOfLivingBirds;
		}
		else
			throw exception();
	}
	bool allBirdsDied() {
		return numberOfLivingBirds == 0;
	}
	int getBestFlapCount() {
		for (Bird& b : birds) {
			if(b.isAlive())
				return b.getFlapCount();
		}
	}
};