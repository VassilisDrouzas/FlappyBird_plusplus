#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Player2.h"
#include "Pipe.h"
#include "Bomb.h"
#include "Friend.h"
#include "my_config.h"
#include "graphics.h"
#include <vector>
#include <iostream>
#include <fstream>

class Game {

	typedef enum { STATUS_START, STATUS_DIFFICULTY, STATUS_MODECHOICE, STATUS_HELP, STATUS_PLAYING1, STATUS_PLAYING2, STATUS_END1, STATUS_END2 } status_t;
	status_t status = STATUS_START;

	typedef enum { NORMAL, HARD } game_difficulty;
	game_difficulty difficulty;
	graphics::Brush br;
	Player* player1 = nullptr;
	Player2* player2 = nullptr;
	Friend* myfriend = nullptr;
	Bomb* bomb = nullptr;

	bool player1_initialized = false;
	bool player2_initialized = false;
	bool friend_initialized = false;
	bool bomb_initialized = false;

	bool player1_crashed = false;
	bool player2_crashed = false;


	int head_to_head_player1 = 0;
	int head_to_head_player2 = 0;



	Pipe* top1 = nullptr;
	Pipe* top2 = nullptr;
	Pipe* top3 = nullptr;
	Pipe* top4 = nullptr;
	Pipe* top5 = nullptr;
	

	Pipe* bot1 = nullptr;
	Pipe* bot2 = nullptr;
	Pipe* bot3 = nullptr;
	Pipe* bot4 = nullptr;
	Pipe* bot5 = nullptr;
	
	
	// std::vector <Pipe*> pipes;						//Creating a vector of objects of type 'Enemy'
	// void AddPipes();


	void Player1Death();
	void Player2Death();
	
	void spawnPipe(game_difficulty);
	void deletePipe();

	void updateStartScreen();
	void updateChoiceScreen();
	void updateDifficultyScreen();
	void updateHelpScreen();

	void updateLevelScreen1(game_difficulty);
	void updateLevelScreen2(game_difficulty);
	void updateEndScreen1();
	void updateEndScreen2();

	void drawStartScreen();
	void drawChoiceScreen();
	void drawDifficultyScreen();
	void drawHelpScreen();

	void drawLevelScreen1(game_difficulty);
	void drawLevelScreen2(game_difficulty);
	void drawEndScreen1();
	void drawEndScreen2();

	void checkCollision();

	void checkCollision1(game_difficulty);
	void checkCollision2(game_difficulty);


	void checkScore(game_difficulty);
	void resetPipes();


	void drawPlayer1Life();
	void drawPlayer2Life();

	int player1_score = 0;
	int player2_score = 0;
	bool collision = false;
	void updateHighScore();

	void drawHighScore();
	int getHighScore();



	bool collision_ground = false;
	bool collision_ground1 = false;
	bool collision_ground2 = false;



	bool round_winner1 = false;
	bool round_winner2 = false;
	float player1_life = 6.0f;
	float player2_life = 6.0f;
	void drainLife1(float amount) { player1_life = std::max < float>(0.0f, player1_life - amount); }
	void boostLife1(float amount) {
		player1_life = player1_life + amount;
		if (player1_life > 6.0f) {
			player1_life = 6.0f;
		}
	}
	void boostLife2(float amount) {
		player2_life = player2_life + amount;
		if (player2_life > 6.0f) {
			player2_life = 6.0f;
		}
	}
	void drainLife2(float amount) { player2_life = std::max < float>(0.0f, player2_life - amount); }

	void Life1Reset() { player1_life = 6.0f; }
	void Life2Reset() { player2_life = 6.0f; }

public:




	virtual void update();

	virtual void update_hard();
	virtual void draw();

	virtual void draw_hard();
	virtual void init();



	Game();
	~Game();



};

#endif