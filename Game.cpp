#include "Game.h"
#include "Game.h"


int Game::getHighScore() {			//returns the current high score from the txt file
	graphics::Brush br;
	std::ifstream ifs;
	ifs.open("highscore.txt");
	std::string highscore;
	getline(ifs, highscore);			//read highscore from ifs 
	ifs.close();
	int highScore = stoi(highscore);		//convert string highscore to integer
	return highScore;
}

void Game::drawHighScore() {			//prints the high score
	int highScore = getHighScore();

	if (player1_score >= highScore) {
		char info[40];
		sprintf_s(info, "New  High  Score : %i", highScore);
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 430, 30, info, br);
	}
	else {
		char info[40];
		sprintf_s(info, "High  Score : %i", highScore);
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 430, 30, info, br);
	}
}
void Game::updateHighScore() {			//updates the high score
	int highScore = getHighScore();

	if (player1_score > highScore) {
		std::ofstream ofs;
		ofs.open("highscore.txt");
		ofs << std::to_string(player1_score);
		ofs.close();
	}
}

void Game::Player1Death() {

	int temp2 = head_to_head_player2;
	graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
	delete player1;
	player1 = nullptr;
	player1_initialized = false;
	player1_crashed = true;
	collision = true;
	head_to_head_player2++;
	if (head_to_head_player2 != temp2 + 1) {			//if head_to_head_player_1 increased more than 1,fix it to increase only by one.Useful for the bug where this variable
		head_to_head_player2 = temp2 + 1;				// is increased by more than 1. Unfortunately sometimes it happens..
	}
	temp2 = head_to_head_player2;

	round_winner2 = true;

	graphics::playSound(std::string(ASSET_PATH) + "die.wav", 1.0f, false);		//play (only once) the 'die' sound effect
	if (status == STATUS_PLAYING1) {
		status = STATUS_END1;
	}
	else if (status == STATUS_PLAYING2) {
		status = STATUS_END2;
	}
}
void Game::Player2Death() {

	int temp1 = head_to_head_player1;
	graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
	delete player2;
	player2 = nullptr;
	player2_initialized = false;

	collision = true;
	head_to_head_player1++;
	if (head_to_head_player1 != temp1 + 1) {			//if head_to_head_player_1 increased more than 1,fix it to increase only by one.Useful for the bug where this variable
		head_to_head_player1 = temp1 + 1;				// is increased by more than 1. Without this fix unfortunately sometimes it happens..
	}
	temp1 = head_to_head_player1;
	round_winner1 = true;

	graphics::playSound(std::string(ASSET_PATH) + "die.wav", 1.0f, false);		//play (only once) the 'die' sound effect
	if (status == STATUS_PLAYING1) {
		status = STATUS_END1;
	}
	else if (status == STATUS_PLAYING2) {
		status = STATUS_END2;
	}
}

void Game::checkScore(game_difficulty difficulty) {
	if (player1_initialized) {
		float pos_x1 = player1->getposX();
		if (difficulty == HARD) {		//HARD
			if (pos_x1 == top1->getCoordinateXT1() || pos_x1 == bot1->getCoordinateXB1() || pos_x1 == top2->getCoordinateXT2() || pos_x1 == bot2->getCoordinateXB2() || pos_x1 == top3->getCoordinateXT3() || pos_x1 == bot3->getCoordinateXB3() || pos_x1 == top4->getCoordinateXT4() || pos_x1 == bot4->getCoordinateXB4() || pos_x1 == top5->getCoordinateXT5() || pos_x1 == bot5->getCoordinateXB5() && collision == false) {		//if it has successfully passed the pipes
				player1_score++;
			}
		}
		else {		//NORMAL
			if (pos_x1 == top1->getCoordinateXT1() || pos_x1 == bot1->getCoordinateXB1() || pos_x1 == top2->getCoordinateXT2() || pos_x1 == bot2->getCoordinateXB2() || pos_x1 == top3->getCoordinateXT3() || pos_x1 == bot3->getCoordinateXB3() && collision == false) {
				player1_score++;
			}
		}
	}
	if (player2_initialized) {
		float pos_x2 = player2->getposX();
		if (difficulty == HARD) {		//HARD
			if (pos_x2 == top1->getCoordinateXT1() || pos_x2 == bot1->getCoordinateXB1() || pos_x2 == top2->getCoordinateXT2() || pos_x2 == bot2->getCoordinateXB2() || pos_x2 == top3->getCoordinateXT3() || pos_x2 == bot3->getCoordinateXB3() || pos_x2 == top4->getCoordinateXT4() || pos_x2 == bot4->getCoordinateXB4() || pos_x2 == top5->getCoordinateXT5() || pos_x2 == bot5->getCoordinateXB5() && collision == false) {		//if it has successfully passed the pipes
				player2_score++;
			}
		}
		else {		//NORMAL
			if (pos_x2 == top1->getCoordinateXT1() || pos_x2 == bot1->getCoordinateXB1() || pos_x2 == top2->getCoordinateXT2() || pos_x2 == bot2->getCoordinateXB2() || pos_x2 == top3->getCoordinateXT3() || pos_x2 == bot3->getCoordinateXB3() && collision == false) {
				player2_score++;
			}
		}
	}

}
void Game::checkCollision1(game_difficulty difficulty) {
	if (player1_initialized) {
		float pos_x1 = player1->getposX();		//player's coordinate x
		float pos_y1 = player1->getposY();
		if (pos_y1 >= CANVAS_HEIGHT - 121) {			//collision with ground
			collision_ground1 = true;
		}
		int temp2 = head_to_head_player2;
		//collision with ground or red pipe	= DEATH	
		if (difficulty == HARD) {				//HARD				//collision with top4														//collision with b5																					//collision with b1															//collision with top2																					//collision with bot3
			if (collision_ground1 || (pos_x1 == top4->getCoordinateXT4() && pos_y1 < CANVAS_HEIGHT - top4->getHeightt4() - 100) || (pos_x1 == bot5->getCoordinateXB5() && pos_y1 > CANVAS_HEIGHT - bot5->getHeightb5() - 50) || (pos_x1 == bot1->getCoordinateXB1() && pos_y1 > (CANVAS_HEIGHT - bot1->getHeightb1()) - 100) || (pos_x1 == top2->getCoordinateXT2() && pos_y1 < (CANVAS_HEIGHT - top2->getHeightt2()) + 65) || (pos_x1 == bot3->getCoordinateXB3() && pos_y1 > (CANVAS_HEIGHT - bot3->getHeightb3()) - 100)) {		
				Player1Death();

			}				//collision with green pipe				//collision with top1									//collision with bot4																	//collision with top5																				collision with bot2																				//collision with top3
			if ((pos_x1 == top1->getCoordinateXT1() && pos_y1 < (CANVAS_HEIGHT - top1->getHeightt1()) + 50) || (pos_x1 == bot4->getCoordinateXB4() && pos_y1 > CANVAS_HEIGHT - bot4->getHeightb4() - 50) || (pos_x1 == top5->getCoordinateXT5() && pos_y1 < CANVAS_HEIGHT - top5->getHeightt5() - 100) || (pos_x1 == bot2->getCoordinateXB2() && pos_y1 > (CANVAS_HEIGHT - bot2->getHeightb2()) - 100) || (pos_x1 == top3->getCoordinateXT3() && pos_y1 < (CANVAS_HEIGHT - top3->getHeightt3()) + 20)) {

				//graphics::playSound(std::string(ASSET_PATH) + "gepap.mp3", 0.5f, false);
				graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
				drainLife1(2.5f);


				if (player1_life <= 0.0f) {
					Player1Death();

				}
			}
		}		//NORMAL
		else {
			if (collision_ground1 || (pos_x1 == bot1->getCoordinateXB1() && pos_y1 > (CANVAS_HEIGHT - bot1->getHeightb1()) - 125) || (pos_x1 == top2->getCoordinateXT2() && pos_y1 < (CANVAS_HEIGHT - top2->getHeightt2()) + 65) || (pos_x1 == bot3->getCoordinateXB3() && pos_y1 > (CANVAS_HEIGHT - bot3->getHeightb3()) - 100)) {		//if player hits the base or the pipe

				Player1Death();

			}				//collision with green pipe = Life drain
			if ((pos_x1 == top1->getCoordinateXT1() && pos_y1 < (CANVAS_HEIGHT - top1->getHeightt1()) + 50) || (pos_x1 == bot2->getCoordinateXB2() && pos_y1 > (CANVAS_HEIGHT - bot2->getHeightb2()) - 100) || (pos_x1 == top3->getCoordinateXT3() && pos_y1 < (CANVAS_HEIGHT - top3->getHeightt3()) + 20)) {
				//graphics::playSound(std::string(ASSET_PATH) + "gepap.mp3", 0.5f, false);
				graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
				drainLife1(2.5f);


				if (player1_life <= 0.0f) {
					Player1Death();

				}
			}

		}
		if (friend_initialized) {
			float friendpos_x = myfriend->getposX();
			float friendpos_y = myfriend->getposY();
			
			if (abs(pos_x1 - friendpos_x < 5) && abs(pos_y1 - friendpos_y < 5)) {				//collision with friend
				graphics::playSound(std::string(ASSET_PATH) + "point.wav", 0.5f, false);
				boostLife1(1.4f);
				delete myfriend;
				myfriend = nullptr;
				friend_initialized = false;
				
			}
		}
		if (bomb_initialized) {
			float bombpos_x = bomb->getposX();
			float bombpos_y = bomb->getposY();
			
			if (abs(pos_x1 - bombpos_x < 5) && abs(pos_y1 - bombpos_y < 5)) {				//collision with friend
				graphics::playSound(std::string(ASSET_PATH) + "bomb.wav", 0.5f, false);
				drainLife1(1.4f);
				delete bomb;
				bomb = nullptr;
				bomb_initialized = false;
				
			}

			if (player1_life <= 0.0f) {
				Player1Death();

			}


		}

	}
}
void Game::checkCollision2(game_difficulty difficulty) {
	if (player2_initialized) {
		float pos_x2 = player2->getposX();		//player's coordinate x
		float pos_y2 = player2->getposY();
		if (pos_y2 >= CANVAS_HEIGHT - 121) {
			collision_ground2 = true;
		}

		int temp1 = head_to_head_player1;

		if (difficulty == HARD) {	//HARD		
									//collision with ground or red pipe = DEATH
			if (collision_ground2 || (pos_x2 == top4->getCoordinateXT4() && pos_y2 < CANVAS_HEIGHT - top4->getHeightt4() - 100) || (pos_x2 == bot5->getCoordinateXB5() && pos_y2 > CANVAS_HEIGHT - bot5->getHeightb5() - 50) || (pos_x2 == bot1->getCoordinateXB1() && pos_y2 > (CANVAS_HEIGHT - bot1->getHeightb1()) - 100) || (pos_x2 == top2->getCoordinateXT2() && pos_y2 < (CANVAS_HEIGHT - top2->getHeightt2()) + 65) || (pos_x2 == bot3->getCoordinateXB3() && pos_y2 > (CANVAS_HEIGHT - bot3->getHeightb3()) - 100)) {		
				Player2Death();

			}				//collision with green pipe = life drain
			if ((pos_x2 == top1->getCoordinateXT1() && pos_y2 < (CANVAS_HEIGHT - top1->getHeightt1()) + 50) || (pos_x2 == bot4->getCoordinateXB4() && pos_y2 > CANVAS_HEIGHT - bot4->getHeightb4() - 50) || (pos_x2 == top5->getCoordinateXT5() && pos_y2 < CANVAS_HEIGHT - top5->getHeightt5() - 100) || (pos_x2 == bot2->getCoordinateXB2() && pos_y2 > (CANVAS_HEIGHT - bot2->getHeightb2()) - 100) || (pos_x2 == top3->getCoordinateXT3() && pos_y2 < (CANVAS_HEIGHT - top3->getHeightt3()) + 20)) {
				graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
				drainLife2(2.5f);


				if (player2_life <= 0.0f) {
					Player2Death();


				}
			}
		}
		else {				//NORMAL
			if (collision_ground2 || (pos_x2 == bot1->getCoordinateXB1() && pos_y2 > (CANVAS_HEIGHT - bot1->getHeightb1()) - 125) || (pos_x2 == top2->getCoordinateXT2() && pos_y2 < (CANVAS_HEIGHT - top2->getHeightt2()) + 65) || (pos_x2 == bot3->getCoordinateXB3() && pos_y2 > (CANVAS_HEIGHT - bot3->getHeightb3()) - 100)) {		//if player hits the base or the pipe
				Player2Death();

			}				//collision with green pipe
			if ((pos_x2 == top1->getCoordinateXT1() && pos_y2 < (CANVAS_HEIGHT - top1->getHeightt1()) + 50) || (pos_x2 == bot2->getCoordinateXB2() && pos_y2 > (CANVAS_HEIGHT - bot2->getHeightb2()) - 100) || (pos_x2 == top3->getCoordinateXT3() && pos_y2 < (CANVAS_HEIGHT - top3->getHeightt3()) + 20)) {
				graphics::playSound(std::string(ASSET_PATH) + "hit.wav", 0.5f, false);		//play (only once) the 'hit base' sound effect
				drainLife2(2.5f);


				if (player2_life <= 0.0f) {
					Player2Death();

				}
			}

		}
		if (friend_initialized) {
			float friendpos_x = myfriend->getposX();
			float friendpos_y = myfriend->getposY();
			if (abs(pos_x2 - friendpos_x < 5) && abs(pos_y2 - friendpos_y < 5)) {				//collision with friend
				graphics::playSound(std::string(ASSET_PATH) + "point.wav", 0.5f, false);
				boostLife2(1.4f);
				delete myfriend;
				myfriend = nullptr;
				friend_initialized = false;
			}

		}
		if (bomb_initialized) {
			float bombpos_x = bomb->getposX();
			float bombpos_y = bomb->getposY();
			if (abs(pos_x2 - bombpos_x < 5) && abs(pos_y2 - bombpos_y < 5)) {				//collision with friend
				graphics::playSound(std::string(ASSET_PATH) + "bomb.wav", 0.5f, false);
				drainLife2(1.4f);
			}
			if (player2_life <= 0.0f) {
				Player2Death();
				delete bomb;
				bomb = nullptr;
				bomb_initialized = false;

			}
		}
	}
}

void Game::checkCollision() {

	if (player1_initialized) {
		checkCollision1(difficulty);
	}
	if (player2_initialized) {
		checkCollision2(difficulty);
	}

	checkScore(difficulty);
}

void Game::resetPipes() {

	if (top1 != nullptr) top1->init();		//Reset the pipes when starting again
	if (top4 != nullptr) top4->init();
	if (top2 != nullptr) top2->init();
	if (top5 != nullptr) top5->init();
	if (top3 != nullptr) top3->init();
	if (bot1 != nullptr) bot1->init();
	if (bot4 != nullptr) bot4->init();
	if (bot2 != nullptr) bot2->init();
	if (bot5 != nullptr) bot5->init();
	if (bot3 != nullptr) bot3->init();

}


void Game::spawnPipe(game_difficulty difficulty)
{

	if (!top1) {
		top1 = new Pipe(*this);
	}

	if (!top2) {
		top2 = new Pipe(*this);
	}

	if (!top3) {
		top3 = new Pipe(*this);
	}

	if (!bot1) {
		bot1 = new Pipe(*this);
	}

	if (!bot2) {
		bot2 = new Pipe(*this);
	}

	if (!bot3) {
		bot3 = new Pipe(*this);
	}

	if (difficulty == HARD) {
		if (!top4) {
			top4 = new Pipe(*this);
		}
		if (!top5) {
			top5 = new Pipe(*this);
		}
		if (!bot4) {
			bot4 = new Pipe(*this);
		}
		if (!bot5) {
			bot5 = new Pipe(*this);
		}

	}

	//AddPipes();									//Χρησιμεύει στο να εντάξουμε τα αντικείμενα pipes στο vector
}
/*
void Game::AddPipes() {								//Προσθήκη στοιχείων τύπου Enemy στο vector pipes
	pipes.push_back(top1);
	pipes.push_back(top2);
	pipes.push_back(top3);
	pipes.push_back(top4);
	pipes.push_back(top5);
	pipes.push_back(bot1);
	pipes.push_back(bot2);
	pipes.push_back(bot3);
	pipes.push_back(bot4);
	pipes.push_back(bot5);
}
*/
void Game::deletePipe()
{
	/*
	for (auto iter : pipes) {
															// Διαγραφή στοιχείων τύπου Enemy από το vector pipes με iterator.Χρησίμευε σε περίπτωση που θέλαμε να αποθηκεύσουμε τα pipes σε ένα vector.
		pipes.erase(pipes.cbegin(),pipes.cend());
	}
	*/

	if (top1) {
		delete top1;
		top1 = nullptr;
	}
	if (top4) {
		delete top4;
		top4 = nullptr;
	}

	if (top2) {
		delete top2;
		top2 = nullptr;
	}
	if (top5) {
		delete top5;
		top5 = nullptr;
	}

	if (top3) {
		delete top3;
		top3 = nullptr;
	}

	if (bot1) {
		delete bot1;
		bot1 = nullptr;
	}
	if (bot4) {
		delete bot4;
		bot4 = nullptr;
	}
	if (bot2) {
		delete bot2;
		bot2 = nullptr;
	}
	if (bot5) {
		delete bot5;
		bot5 = nullptr;
	}
	if (bot3) {
		delete bot3;
		bot3 = nullptr;
	}

}

void Game::updateStartScreen()
{
	
	head_to_head_player1 = 0;
	head_to_head_player2 = 0;

	player1_score = 0;		//reseting player's score
	player2_score = 0;
	collision = false;


	collision_ground1 = false;
	collision_ground2 = false;
	Life1Reset();
	Life2Reset();

	round_winner1 = false;
	round_winner2 = false;

	resetPipes();

	graphics::MouseState mouse;
	getMouseState(mouse);
	if (mouse.button_left_pressed) {
		status = STATUS_DIFFICULTY;
	}


	if (graphics::getKeyState(graphics::SCANCODE_Q)) {
		exit(0);
	}
}

void Game::updateDifficultyScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_N)) {
		difficulty = NORMAL;
		status = STATUS_MODECHOICE;
	}
	if (graphics::getKeyState(graphics::SCANCODE_H)) {
		difficulty = HARD;
		status = STATUS_MODECHOICE;
	}
	if (graphics::getKeyState(graphics::SCANCODE_M)) {
		status = STATUS_START;
	}
	if (graphics::getKeyState(graphics::SCANCODE_L)) {
		status = STATUS_HELP;
	}
}
void Game::updateChoiceScreen() {

	if (graphics::getKeyState(graphics::SCANCODE_M)) {
		status = STATUS_START;
	}

	if (graphics::getKeyState(graphics::SCANCODE_1)) {
		status = STATUS_PLAYING1;

	}
	if (graphics::getKeyState(graphics::SCANCODE_2)) {
		status = STATUS_PLAYING2;

	}
	if (graphics::getKeyState(graphics::SCANCODE_L)) {
		status = STATUS_HELP;
	}

}


void Game::updateHelpScreen() {

	if (graphics::getKeyState(graphics::SCANCODE_M)) {
		status = STATUS_START;
	}

}

void Game::updateLevelScreen1(game_difficulty difficulty) {
	graphics::setFont(std::string(ASSET_PATH) + "Salty Ocean.ttf");


	if (!player1_initialized && graphics::getGlobalTime() > 500) {
		player1 = new Player(*this);		//create new player instance
		player1_initialized = true;
	}
	if (!friend_initialized && graphics::getGlobalTime() > 500) {
		myfriend = new Friend(*this);		//create new player instance
		friend_initialized = true;
	}

	if (!bomb_initialized && graphics::getGlobalTime() > 500) {
		bomb = new Bomb(*this);
		bomb_initialized = true;
	}

	spawnPipe(difficulty);


	if (difficulty == NORMAL) {

		if (player1) {
			player1->update();
		}


		if (myfriend) {
			myfriend->update();
		}

		if (bomb) {
			bomb->update();
		}

		if (top1) {
			top1->update();
		}
		if (top2) {
			top2->update();
		}
		if (top3) {
			top3->update();
		}
		if (bot1) {
			bot1->update();
		}
		if (bot2) {
			bot2->update();
		}
		if (bot3) {
			bot3->update();
		}

	}
	else if (difficulty == HARD) {

		if (player1) {
			player1->update_hard();
		}


		if (myfriend) {
			myfriend->update_hard();
		}
		if (bomb) {
			bomb->update_hard();
		}

		/*
		for (auto iter : pipes) {				//Συντομότερη λύση που προσπάθησα με iterator σε vector. Προέκυψαν περίεργα αποτελέσματα,για αυτό και δεν την χρησιμοποίησα τελικά..
			if (iter) {
				(*iter).update_hard();
			}
		}*/
		if (top1) {
			top1->update_hard();
		}
		if (top4) {
			top4->update_hard();
		}
		if (top2) {
			top2->update_hard();
		}
		if (top5) {
			top5->update_hard();
		}
		if (top3) {
			top3->update_hard();
		}
		if (bot1) {
			bot1->update_hard();
		}
		if (bot4) {
			bot4->update_hard();
		}

		if (bot2) {
			bot2->update_hard();
		}
		if (bot5) {
			bot5->update_hard();
		}
		if (bot3) {
			bot3->update_hard();
		}

	}

	checkCollision();

}

void Game::updateLevelScreen2(game_difficulty difficulty)
{

	updateLevelScreen1(difficulty);

	if (!player2_initialized && graphics::getGlobalTime() > 500) {
		player2 = new Player2(*this);		//create new player instance
		player2_initialized = true;
	}
	if (difficulty == NORMAL) {
		if (player2) {
			player2->update();
		}
	}
	else {
		player2->update_hard();
	}
}


void Game::updateEndScreen1() {

	deletePipe();
	updateHighScore();
	delete(player1);
	player1 = nullptr;
	player1_initialized = false;
	if (graphics::getKeyState(graphics::SCANCODE_K)) {			//Start the game
		status = STATUS_START;
	}
	if (graphics::getKeyState(graphics::SCANCODE_Q)) {			//Terminate program
		exit(0);
	}
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		
		player1_score = 0;
		Life1Reset();
		collision_ground1 = false;

		resetPipes();
		status = STATUS_PLAYING1;
	}


}
void Game::updateEndScreen2() {

	deletePipe();
	delete(player2);
	player2 = nullptr;
	player2_initialized = false;
	if (graphics::getKeyState(graphics::SCANCODE_K)) {			//Start the game
		status = STATUS_START;
	}
	if (graphics::getKeyState(graphics::SCANCODE_Q)) {			//Terminate program
		exit(0);
	}
	if (graphics::getKeyState(graphics::SCANCODE_A)) {

		player1_score = 0;
		Life1Reset();
		collision_ground1 = false;
		resetPipes();
		player2_score = 0;
		Life2Reset();
		collision_ground2 = false;
		round_winner1 = false;
		round_winner2 = false;
		status = STATUS_PLAYING2;

	}
}

void Game::drawStartScreen()
{
	graphics::setFont(std::string(ASSET_PATH) + "orange juice 2.0.ttf");
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "flappybird.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 1.2, br);

	char info1[40];
	sprintf_s(info1, "Welcome  to");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 470, 30, info1, br);

	char info2[100];
	sprintf_s(info2, "Press  left  click  to  continue, Q  to  quit");
	graphics::drawText(CANVAS_WIDTH / 2 - 250, CANVAS_HEIGHT - 10, 30, info2, br);

}
void Game::drawDifficultyScreen() {

	graphics::setFont(std::string(ASSET_PATH) + "Happy Dreamer.ttf");

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "flappybirdbluebackground.png";

	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);


	char info[40];
	sprintf_s(info, "Welcome  to  FlappyBird ++ !");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 470, 30, info, br);

	char info4[50];
	sprintf_s(info4, "Let's  get  started !");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 400, 30, info4, br);

	char info3[40];
	sprintf_s(info3, "First,  choose  a  difficulty  level :");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 330, 30, info3, br);

	graphics::drawLine(310, 175, 710, 175, br);						//Underliner

	char info5[50];
	sprintf_s(info5, "Press  N  for  normal  mode");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 260, 30, info5, br);

	char info2[50];
	sprintf_s(info2, "Press  H  for  hard  mode");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 210, 30, info2, br);

	char info6[50];
	sprintf_s(info6, "Press  M  to  go  to  the  start  menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 70, 30, info6, br);

	char info7[50];
	sprintf_s(info7, "Press  L  for  help");
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 30, 30, info7, br);

}
void Game::drawChoiceScreen() {

	graphics::setFont(std::string(ASSET_PATH) + "Happy Dreamer.ttf");

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background-night.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char info4[50];
	sprintf_s(info4, "Now , select  a  game  mode !");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 400, 30, info4, br);

	graphics::drawLine(310, 105, 690, 105, br);						//Underliner

	char info2[50];
	sprintf_s(info2, "Press  one  for  Single - Player");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 350, 30, info2, br);

	char info3[50];
	sprintf_s(info3, "Press  two  for  a  two - player  match");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT - 300, 30, info3, br);

	char info6[50];
	sprintf_s(info6, "Press  M  to  go  to  the  start  menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 70, 30, info6, br);

	char info7[50];
	sprintf_s(info7, "Press  L  for  help");
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 30, 30, info7, br);

}

void Game::drawHelpScreen() {

	graphics::setFont(std::string(ASSET_PATH) + "Happy Dreamer.ttf");

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "space2.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char info2[100];
	sprintf_s(info2, "FlappyBird ++  is  a  game  where  you  tap  the  screen  to  make  the  bird  fly.");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 470, 30, info2, br);

	char info3[100];
	sprintf_s(info3, "Watch out! If  you  hit  a  red  pipe,  your  bird  falls  and  you  restart  the  game.");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 420, 30, info3, br);

	char info8[100];
	sprintf_s(info8, " If  you  hit  a  green  pipe,  your life drains.");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 370, 30, info8, br);

	char info9[100];
	sprintf_s(info9, "Beware  for  hearts! Sometimes  they  can  give  you  a  significant  life  boost.");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 320, 30, info9, br);

	char info11[110];
	sprintf_s(info11, "Also,  make  sure  you  don't  reach  the  horizontal  level  of  a  bomb. Its  affected  area  is  vast. ");
	graphics::drawText(CANVAS_WIDTH / 2 - 470, CANVAS_HEIGHT - 270, 30, info11, br);

	char info4[30];
	sprintf_s(info4, "Controls :");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 200, 30, info4, br);

	char info5[50];
	sprintf_s(info5, "W: make  the  bird  fly");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 160, 30, info5, br);

	char info10[100];
	sprintf_s(info10, "UP:  make  the  bird  fly  ( only  for  two - player  mode )");
	graphics::drawText(CANVAS_WIDTH / 2 - 400, CANVAS_HEIGHT - 110, 30, info10, br);

	char info6[50];
	sprintf_s(info6, "Press  M  to  go  to  the  start menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 40, 30, info6, br);

}
void Game::drawPlayer1Life() {

	float center_y = 20.0f;

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player1_life) + player1_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2 * (1.0f - player1_life) + player1_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 870 - ((1.0f - player1_life) * 30 / 2), center_y, player1_life * 30, 20, br);

}
void Game::drawPlayer2Life() {

	drawPlayer1Life();

	float center_y = 65.0f;

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player2_life) + player2_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2 * (1.0f - player2_life) + player2_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 870 - ((1.0f - player2_life) * 30 / 2), center_y, player2_life * 30, 20, br);
}

void Game::drawLevelScreen1(game_difficulty difficulty) {
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background-day.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);		//draw background

	br.texture = std::string(ASSET_PATH) + "base.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, CANVAS_WIDTH, CANVAS_HEIGHT - 400, br);		//draw base

	if (difficulty == NORMAL) {
		if (player1) {
			player1->draw();
		}
		if (myfriend) {
			myfriend->draw();
		}

		if (bomb) {
			bomb->draw();
		}
		if (top1) {
			top1->draw();
		}

		if (top2) {
			top2->draw();
		}

		if (top3) {
			top3->draw();
		}
		if (bot1) {
			bot1->draw();
		}

		if (bot2) {
			bot2->draw();
		}

		if (bot3) {
			bot3->draw();
		}

	}
	else if (difficulty == HARD) {
		if (player1) {
			player1->draw_hard();
		}
		if (myfriend) {
			myfriend->draw_hard();
		}
		if (bomb) {
			bomb->draw_hard();
		}
		/*
	   for (auto iter : pipes) {					//Συντομότερη λύση που προσπάθησα με iterator σε vector. Προέκυψαν περίεργα αποτελέσματα,για αυτό και δεν την χρησιμοποίησα τελικά..
		   if (iter) {
			   (*iter).draw_hard();

		   }
	   }
	   */

		if (top1) {
			top1->draw_hard();
		}
		if (top4) {
			top4->draw_hard();
		}
		if (top2) {
			top2->draw_hard();
		}
		if (top5) {
			top5->draw_hard();
		}
		if (top3) {
			top3->draw_hard();
		}
		if (bot1) {
			bot1->draw_hard();
		}
		if (bot4) {
			bot4->draw_hard();
		}
		if (bot2) {
			bot2->draw_hard();
		}
		if (bot5) {
			bot5->draw_hard();
		}
		if (bot3) {
			bot3->draw_hard();
		}

	}

	if (player1) {
		char info[40];
		sprintf_s(info, "Score:%i", player1_score);
		graphics::drawText(40, 70, 30, info, br);

		char info2[40];
		sprintf_s(info2, "Life:");
		graphics::drawText(40, 30, 30, info2, br);


	}
	drawPlayer1Life();

}
void Game::drawLevelScreen2(game_difficulty difficulty)
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background-day.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);		//draw background

	br.texture = std::string(ASSET_PATH) + "base.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, CANVAS_WIDTH, CANVAS_HEIGHT - 400, br);		//draw base
	if (difficulty == NORMAL) {
		if (player1) {
			player1->draw();
		}
		if (player2) {
			player2->draw();
		}
		if (myfriend) {
			myfriend->draw();
		}
		if (bomb) {
			bomb->draw();
		}

		if (top1) {
			top1->draw();
		}

		if (top2) {
			top2->draw();
		}

		if (top3) {
			top3->draw();
		}
		if (bot1) {
			bot1->draw();
		}

		if (bot2) {
			bot2->draw();
		}

		if (bot3) {
			bot3->draw();
		}
	}
	else if (difficulty == HARD) {
		if (player1) {
			player1->draw_hard();
		}
		if (player2) {
			player2->draw_hard();
		}
		if (myfriend) {
			myfriend->draw_hard();
		}
		if (bomb) {
			bomb->draw_hard();
		}
		/*
	   for (auto iter : pipes) {					//Συντομότερη λύση που προσπάθησα με iterator σε vector. Προέκυψαν περίεργα αποτελέσματα,για αυτό και δεν την χρησιμοποίησα τελικά..
		   if (iter) {
			   (*iter).draw_hard();

		   }
	   }
	   */


		if (top1) {
			top1->draw_hard();
		}
		if (top4) {
			top4->draw_hard();
		}
		if (top2) {
			top2->draw_hard();
		}
		if (top5) {
			top5->draw_hard();
		}
		if (top3) {
			top3->draw_hard();
		}
		if (bot1) {
			bot1->draw_hard();
		}

		if (bot2) {
			bot2->draw_hard();
		}

		if (bot3) {
			bot3->draw_hard();
		}
	}
	if (player1) {
		char info2[40];
		sprintf_s(info2, "Life1:");
		graphics::drawText(40, 30, 30, info2, br);
	}
	if (player2) {
		char info2[40];
		sprintf_s(info2, "Life2:");
		graphics::drawText(40, 70, 30, info2, br);
	}

	drawPlayer2Life();
}
void Game::drawEndScreen1() {

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "gameover2.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::setFont(std::string(ASSET_PATH) + "CaptainOfAmerica.ttf");		//change font

	char info1[40];
	sprintf_s(info1, "You  scored :  %i", player1_score);
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 470, 30, info1, br);

	drawHighScore();

	char info2[40];
	sprintf_s(info2, "Press K for the start menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 50, 30, info2, br);

	char info3[40];
	sprintf_s(info3, "Press Q to quit");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 10, 30, info3, br);

	char info4[40];
	sprintf_s(info4, "Press  A  to  play  again ");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 90, 30, info4, br);

}
void Game::drawEndScreen2()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "gameover2.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::setFont(std::string(ASSET_PATH) + "CaptainOfAmerica.ttf");		//change font

	if (round_winner1) {
		char info5[40];
		sprintf_s(info5, "Round  winner :  Player  1");
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 470, 30, info5, br);

	}
	else if (round_winner2) {
		char info6[40];
		sprintf_s(info6, "Round  winner :  Player  2");
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 470, 30, info6, br);

	}

	char info7[60];
	sprintf_s(info7, " Player  1 :    %i", head_to_head_player1);
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 420, 30, info7, br);

	char info8[60];
	sprintf_s(info8, " Player  2 :   %i", head_to_head_player2);
	graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT - 380, 30, info8, br);

	char info2[60];
	sprintf_s(info2, "Press K  for  the  start  menu");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 50, 30, info2, br);

	char info3[40];
	sprintf_s(info3, "Press  Q  to  quit");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 10, 30, info3, br);

	char info4[40];
	sprintf_s(info4, "Press  A  to  play  again ");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT - 90, 30, info4, br);
}

void Game::update() {

	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_DIFFICULTY) {
		updateDifficultyScreen();
	}
	else if (status == STATUS_MODECHOICE) {
		updateChoiceScreen();
	}

	else if (status == STATUS_HELP) {
		updateHelpScreen();
	}
	else if (status == STATUS_PLAYING1) {
		updateLevelScreen1(difficulty);
	}
	else if (status == STATUS_PLAYING2) {
		updateLevelScreen2(difficulty);
	}
	else if (status == STATUS_END1) {
		updateEndScreen1();
	}
	else {
		updateEndScreen2();
	}
}

void Game::update_hard() {
	update();
}

void Game::init() {
	graphics::setFont(std::string(ASSET_PATH) + "orange juice 2.0.ttf");									//font
	graphics::playMusic(std::string(ASSET_PATH) + "flappybird.mp3", 0.5f, true, 4000);						//music

}

void Game::draw() {

	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_MODECHOICE) {
		drawChoiceScreen();
	}
	else if (status == STATUS_DIFFICULTY) {
		drawDifficultyScreen();
	}
	else if (status == STATUS_HELP) {
		drawHelpScreen();
	}
	else if (status == STATUS_PLAYING1) {
		drawLevelScreen1(difficulty);
	}
	else if (status == STATUS_PLAYING2) {
		drawLevelScreen2(difficulty);
	}
	else if (status == STATUS_END1) {
		drawEndScreen1();
	}
	else {
		drawEndScreen2();
	}

}

void Game::draw_hard() {
	draw();
}
Game::Game() {				//Constructor

}
Game::~Game() {				//Destructor
	if (player1) {
		delete (player1);
		player1 = nullptr;
	}
	if (player2) {
		delete (player2);
		player2 = nullptr;
	}
	if (myfriend) {
		delete (myfriend);
		myfriend = nullptr;
	}
	if (bomb) {
		delete (bomb);
		bomb = nullptr;
	}

}