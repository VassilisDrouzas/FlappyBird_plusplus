#include "Player.h"


Player::Player(const Game& game) :GameObject(game) {
	init();
}




void Player::update(){
	
	
	//PLAYER 1
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		player1_pos_y -= speed1 * graphics::getDeltaTime() / 10.0f;
	}
	else if (!graphics::getKeyState(graphics::SCANCODE_W)) {		//while you are not pressing,player go to the opposite direction
		player1_pos_y += speed1 * graphics::getDeltaTime() / 20.0f;
	}
	
	if (player1_pos_x < 0) {				//Stay in the window bounds
		player1_pos_x = 0;
	}
	if (player1_pos_x > CANVAS_WIDTH) {
		player1_pos_x = CANVAS_WIDTH;
	}
	if (player1_pos_y < 0) {
		player1_pos_y = 0;
	}
	if (player1_pos_y > CANVAS_HEIGHT) {
		player1_pos_y = CANVAS_HEIGHT;
	}
	
	
	
}

void Player::update_hard() {

	//PLAYER 1
	update();
}

void Player::draw() {

	//PLAYER1
	graphics::setScale(height1, height1);
	//br.texture = std::string(ASSET_PATH) + "gepap.png";
	br.texture = std::string(ASSET_PATH) + "bluebird-upflap.png";
	br.outline_opacity = 0.0f;

	

	graphics::drawRect(player1_pos_x, player1_pos_y, width,size , br);
	graphics::resetPose();

}
void Player::draw_hard() {
	//PLAYER1
	draw();
}
void Player::init() {
	
}







