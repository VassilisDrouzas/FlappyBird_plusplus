#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "graphics.h"
#include "my_config.h"
#include "Gameobject.h"


class Player : public GameObject {
private:
	
	
	float speed1 = 4.0f;
	float height1 = 1.0f;
	float player1_life = 10.0f;
	float player1_pos_x=CANVAS_WIDTH/2 , player1_pos_y=CANVAS_HEIGHT/2 -80;
	float width = 50.0f;
	float rotation;
	float size = 50.0f;		//htan 50
	graphics::Brush br;
	bool active = true;
	

public:
	
	Player(const class Game& game);  // constructor
	
	void update() override;
	
	void update_hard() override;
	void draw() override;
	
	void draw_hard()override;
	void init() override;
	bool isActive() { return active; }
	
	float getposX() { return player1_pos_x; }
	float getposY() {return player1_pos_y; }
	float getHeight() { return height1; }
	float getWidth() { return width; }
	
	
	
	
	
};

#endif