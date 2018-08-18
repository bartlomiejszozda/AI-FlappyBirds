#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "BirdsGroup.h"
using namespace std;

#include "olcConsoleGameEngine.h"

constexpr int numOfBirds = 100;

class OneLoneCoder_FlappyBird : public olcConsoleGameEngine
{
public:
	OneLoneCoder_FlappyBird():fGravity(130.0f), birds(numOfBirds, ScreenHeight() / 2.0f, 0.0f, fGravity)
	{
		m_sAppName = L"Flappy Bird";
	}

private:

	float fGravity;
	BirdsGroup birds;
	float fLevelPosition = 0.0f;

	float fSectionWidth;
	list<int> listSection;

	//bool bHasCollided = false;
	bool bResetGame = false;

	int nAttemptCount = 0;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		listSection = { 0, 0, 0, 0, 0 };
		bResetGame = true;
		fSectionWidth = (float)ScreenWidth() / (float)(listSection.size() - 1);
		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		if (bResetGame)
		{
			//bHasCollided = false;
			bResetGame = false;
			listSection = { 0, 0, 0, 0, 0 };
			birds.reborn(ScreenHeight() / 2.0f, 0.0f);
			nAttemptCount++;
		}

		// Game
		if (birds.allBirdsDied())
		{
			// Do nothing until user releases space
			if (m_keys[VK_SPACE].bReleased)
				bResetGame = true;
		}
		else
		{

			if (m_keys[VK_SPACE].bPressed )//&& fBirdVelocity >= fGravity / 10.0f)
			{
				birds.flap();
			}

			birds.updatePosition(fElapsedTime);
			fLevelPosition += 14.0f * fElapsedTime;

			if (fLevelPosition > fSectionWidth)
			{
				fLevelPosition -= fSectionWidth;
				listSection.pop_front();
				int i = rand() % (ScreenHeight() - 20);
				if (i <= 10) i = 0;
				listSection.push_back(i);
			}

			// Display
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

			// Draw Sections
			int nSection = 0;
			for (auto s : listSection)
			{
				if (s != 0)
				{
					Fill(nSection * fSectionWidth + 10 - fLevelPosition, ScreenHeight() - s, nSection * fSectionWidth + 15 - fLevelPosition, ScreenHeight(), PIXEL_SOLID, FG_GREEN);
					Fill(nSection * fSectionWidth + 10 - fLevelPosition, 0, nSection * fSectionWidth + 15 - fLevelPosition, ScreenHeight() - s - 15, PIXEL_SOLID, FG_GREEN);
				}
				nSection++;
			}

			int nBirdX = (int)(ScreenWidth() / 3.0f);
			for (int i = 0; i < numOfBirds; ++i) {
				// Collision Detection if bird is alive
				if (birds[i].isAlive()) {
					bool birdHasCollision = birds[i].getPosition() < 2 || birds[i].getPosition() > ScreenHeight() - 2 ||
						m_bufScreen[(int)(birds[i].getPosition() + 0) * ScreenWidth() + nBirdX].Char.UnicodeChar != L' ' ||
						m_bufScreen[(int)(birds[i].getPosition() + 1) * ScreenWidth() + nBirdX].Char.UnicodeChar != L' ' ||
						m_bufScreen[(int)(birds[i].getPosition() + 0) * ScreenWidth() + nBirdX + 3].Char.UnicodeChar != L' ' ||
						m_bufScreen[(int)(birds[i].getPosition() + 1) * ScreenWidth() + nBirdX + 3].Char.UnicodeChar != L' ';
					if (birdHasCollision) {
						birds.birdDie(i);
					}
				}
			}
			for (int i = 0; i < numOfBirds; ++i) {
				if (birds[i].isAlive()) {
					// Draw Bird if is alive
					if (birds[i].getVelocity() > 0)
					{
						DrawString(nBirdX, birds[i].getPosition() + 0, L"\\");
						DrawString(nBirdX, birds[i].getPosition() + 1, L"<\\Q");
					}
					else
					{
						DrawString(nBirdX, birds[i].getPosition() + 0, L"</Q");
						DrawString(nBirdX, birds[i].getPosition() + 1, L"/");
					}
				}
			}			
			DrawString(1, 1, L"Attempt: " + to_wstring(nAttemptCount) + L"Best Bird Score: " + to_wstring(birds.getBestFlapCount()) + L" Best High Score: " + to_wstring(birds.getMaxBestFlapCount()));


		}

		return true;
	}
};


int main()
{
	// Use olcConsoleGameEngine derived app
	OneLoneCoder_FlappyBird game;
	game.ConstructConsole(80, 52, 16, 16);
	game.Start();

	return 0;
}