#include "Player2.h"



Player2::Player2(const Game& game) :GameObject(game) {
	init();
}



void Player2::update() {

	
	//PLAYER2
	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		player2_pos_y -= speed2 * graphics::getDeltaTime() / 10.0f;
	}
	else if (!graphics::getKeyState(graphics::SCANCODE_UP)) {		//while you are not pressing,player go to the opposite direction
		player2_pos_y += speed2 * graphics::getDeltaTime() / 20.0f;
	}

	if (player2_pos_x < 0) {				//Stay in the window bounds
		player2_pos_x = 0;
	}
	if (player2_pos_x > CANVAS_WIDTH) {
		player2_pos_x = CANVAS_WIDTH;
	}
	if (player2_pos_y < 0) {
		player2_pos_y = 0;
	}
	if (player2_pos_y > CANVAS_HEIGHT) {
		player2_pos_y = CANVAS_HEIGHT;
	}

}


void Player2::update_hard() {
	//PLAYER2
	update();

}
void Player2::draw() {


	//PLAYER2
	graphics::setScale(height2, height2);
	br.texture = std::string(ASSET_PATH) + "redbird-upflap.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(player2_pos_x, player2_pos_y, width, size, br);
	graphics::resetPose();

}


void Player2::draw_hard() {
	//PLAYER2
	draw();
}
void Player2::init() {

}


