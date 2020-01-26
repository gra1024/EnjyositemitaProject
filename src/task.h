#pragma once

#include "config.h"

#define SPEED_MOVE_CAR 20
#define BUFSIZE 5000

using namespace std;

struct Coordinate {
	int x;
	int y;
};

struct SaveData {
	int played;
	string sPlayed;
	int score[6];
	string sScore[6];
};

struct Car {
	int genus;
	int species;
	int currentHP;
	int maxHP;
	Coordinate coordinate;
};

struct GameSystem {
	int timeLimit;
	int selectScene;
	int totalScore;
};

struct Game{
	int flameCountExplosion = 10;
	int flameCountSmork = 20;
	int repetitionCorrectionList[3];
	int checkAppearLighttruck;
	int confirmationPreliminaryOperationMotionMagic;
	Car carData;
	Coordinate craneData;
	Coordinate explosionData[3][2];
	Coordinate smorkData[2];
};

struct Advertising {
	Coordinate skipButton;
};

struct InputFromRemoteControl {
	int com;
	int r;
	char buf[1000];
};

class Task
{
public:
	void setup();
	int sceneChoice();

private:
	int showMenu();
	void showAdvertisement();
	void showGame();
	void showResult();

	void gameDraw();
	void gameCalcCarDamage(int motion);
	void gameAddScore(int destruction, int car, int motion);
	int gameDrawStatusBar();

	int saveDataUpdate(int type, int score);

	void HitLag(int num);
	int drawTimeLimitBar(int currentTime, int maxTime, int color);
	string formatScore(int num, int type);

	int imageHandle_background[11];
	int imageHandle_effect[5];
	int imageHandle_car[13];
	int soundHandle[3];
	int movieHandle[2];
	int fontHandle[4];

	int scene;
	int selector;
	int close;
	int LagCounter;
	int checkHit;
	int countTimer;
	Advertising advertising;
	GameSystem gameSystem;
	Game game;
	SaveData saveData;
	InputFromRemoteControl inputFromRemoteControl;

	int colorBlack = GetColor(0, 0, 0);
	int colorRed = GetColor(255, 0, 0);
	int colorWhite = GetColor(255, 255, 255);
	int colorLightOrange = GetColor(255, 110, 50);
	int colorLightBlue = GetColor(187, 225, 248);
	int colorYellow = GetColor(255, 225, 0);
	int colorBlue = GetColor(39, 156, 233);
	int colorGreen = GetColor(0, 255, 0);
	int colorDarkGray = GetColor(36, 36, 36);
	int colorHandleForNumberOfPlayed = GetColor(157, 157, 157);
};


