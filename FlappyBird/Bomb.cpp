#include "Bomb.h"

void Bomb::update() {
	pos_x -= 5;



	if (pos_x + width <= 0) {			//check if the friend (heart) is off-screen

		pos_x = CANVAS_WIDTH + 200;
		pos_y = rand150to300();
	}
}

void Bomb::update_hard() {
	update();
}

void Bomb::draw() {


	br.texture = std::string(ASSET_PATH) + "bomb3.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(pos_x, pos_y, width, height, br);


}


void Bomb::draw_hard() {
	draw();

}

void Bomb::init() {
	pos_x = CANVAS_WIDTH + 400;
	pos_y = rand150to300();
}



Bomb::Bomb(const Game& game) :GameObject(game) {
	init();
}
Bomb::~Bomb() {
}

