#ifndef FRIEND_H
#define FRIEND_H
#include "Gameobject.h"
#include "graphics.h"
#include "my_config.h"
#include "util.h"
class Friend :public GameObject {
	float pos_x, pos_y;
	
	float height = 60.0f;		
	
	float width = 70.0f;
	graphics::Brush br;
public:
	void update() override;
	
	void update_hard()override;
	void draw() override;
	
	void draw_hard()override;
	void init() override;
	
	float getposX() { return pos_x; }
	float getposY() { return pos_y; }






Friend(const class Game& game);
~Friend();
};

#endif