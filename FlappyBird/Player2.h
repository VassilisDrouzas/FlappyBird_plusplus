#ifndef PLAYER2_H
#define PLAYER2_H
#include <iostream>
#include "graphics.h"
#include "my_config.h"
#include "Gameobject.h"


class Player2 : public GameObject{
private:


	
	float speed2 = 3.5f;
	float height2 = 1.0f;
	float player2_life = 10.0f;
	float player2_pos_x = CANVAS_WIDTH / 2 - 100, player2_pos_y = CANVAS_HEIGHT / 2 - 80;
	float width = 50.0f;
	float rotation;
	float size=50.0f;
	graphics::Brush br;
	bool active = true;


public:

	Player2(const class Game& game);  // constructor

	void update() override;
	
	void update_hard()override;
	void draw() override;
	
	void draw_hard()override;
	void init() override;
	bool isActive() { return active; }
	
	
	
	float getposX() { return player2_pos_x; }
	float getposY() { return player2_pos_y; }
	float getHeight() { return height2; }
	

};

#endif