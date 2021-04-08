#include "Friend.h"



void Friend::update() {
	pos_x -= 5;
	


	if (pos_x + width <= 0) {			//check if the friend (heart) is off-screen
		
		pos_x = CANVAS_WIDTH + 200;
		pos_y = rand150to300();
	}
}

void Friend::update_hard() {
	update();
}

void Friend::draw() {

	
	br.texture = std::string(ASSET_PATH) + "heart.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(pos_x, pos_y, width, height, br);

	
}


void Friend::draw_hard() {
	draw();

}

void Friend::init() {
	pos_x = CANVAS_WIDTH + 200;
	pos_y = rand150to300();
}



Friend::Friend(const Game& game) :GameObject(game) {
	init();
}
Friend::~Friend() {
}

