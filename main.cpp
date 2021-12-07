#include "graphics.h"
#include "my_config.h"
#include "Game.h"
#include "Player.h"
#include "Player2.h"
#include "Friend.h"
#include "Pipe.h"
#include "Bomb.h"

void update(float ms) {
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->update();
}

void draw() {
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->draw();
}

void update_hard(float ms) {
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->update_hard();
}

void draw_hard() {
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->draw_hard();
}



int main() {

	Game game;

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "FlappyBird++");
	graphics::setFullScreen(true);



	graphics::setUserData(&game);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	game.init();
	
	graphics::startMessageLoop();
	graphics::destroyWindow();

	return 0;


}
