#include "Pipe.h"

void Pipe::update()
{


	xt1 -= 5;
	xb1 -= 5;

	xt2 -= 5;
	xb2 -= 5;

	xt3 -= 5;
	xb3 -= 5;

	

	if (xt1 + pipe_width <= 0 || xb1 + pipe_width <= 0) {			//check if the pipe is off-screen
		
		xt1 = CANVAS_WIDTH;
		yt1 = 0;
		heightt1 = CANVAS_HEIGHT - 150;
		xb1 = CANVAS_WIDTH;
		yb1 = CANVAS_HEIGHT - 150;		//340
		heightb1 = CANVAS_HEIGHT - yb1-50;

	}
	if (xt2 + pipe_width <= 0 || xb2 + pipe_width <= 0) {			//check if the pipe is off-screen
		
		xt2 = xt1 + 300;		//to have some space between t1 and t2
		yt2 = 0;
		heightt2 = CANVAS_HEIGHT - 140;
		xb2 = xb1 + 300;			//to have some space between b1 and b2
		yb2 = CANVAS_HEIGHT - 160;
		heightb2 = CANVAS_HEIGHT - yb2;

	}
	if (xt3 + pipe_width <= 0 || xb3 + pipe_width <= 0) {			//check if the pipe is off-screen
		
		xt3 = xt2 + 300;		//to have some space between t1 and t2
		yt3 = 0;
		heightt3 = CANVAS_HEIGHT - 160;
		xb3 = xb2 + 300;
		yb3 = CANVAS_HEIGHT - 140;
		heightb3 = CANVAS_HEIGHT - yb3;

	}


}



void Pipe::update_hard()
{
	update();

	xt4 -= 5;
	xb4 -= 5;

	xt5 -= 5;
	xb5 -= 5;

	

	if (xt4 + pipe_width <= 0 || xb4 + pipe_width <= 0) {			//check if the pipe is off-screen
		
		xt4 = xt1 + 150;
		yt4 = 0;
		heightt4 = CANVAS_HEIGHT - 250;
		xb4 = xb1 + 150;
		yb4 = CANVAS_HEIGHT - 150;		//340
		heightb4 = CANVAS_HEIGHT - yb4 + 100;

	}
	
	if (xt5 + pipe_width <= 0 || xb5 + pipe_width <= 0) {			//check if the pipe is off-screen
		
		xt5 = xt2 + 150;
		yt5 = 0;
		heightt5 = CANVAS_HEIGHT - 250;
		xb5 = xb2 + 150;
		yb5 = CANVAS_HEIGHT - 150;		//340
		heightb5 = CANVAS_HEIGHT - yb5 + 100;

	}
	
}

void Pipe::draw()
{

	br.texture = std::string(ASSET_PATH) + "pipe-green.png";
	br.outline_opacity = 0.0f;



	graphics::setOrientation(-180.0f);
	graphics::drawRect(xt1, yt1, pipe_width, heightt1, br);
	graphics::drawRect(xt3, yt3, pipe_width, heightt3, br);

	graphics::resetPose();
	graphics::drawRect(xb2, yb2, pipe_width, heightb2, br);




	br.texture = std::string(ASSET_PATH) + "pipe-red.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(xb1, yb1, pipe_width, heightb1, br);
	graphics::drawRect(xb3, yb3, pipe_width, heightb3, br);
	

	graphics::setOrientation(-180.0f);
	graphics::drawRect(xt2, yt2, pipe_width, heightt2, br);
	
	graphics::resetPose();

	
}



void Pipe::draw_hard() {

	draw();
	
	br.texture = std::string(ASSET_PATH) + "pipe-green.png";
	br.outline_opacity = 0.0f;


	graphics::setOrientation(-180.0f);							//Oriented greens
	graphics::drawRect(xt5, yt5, pipe_width, heightt5, br);
	graphics::resetPose();

	graphics::drawRect(xb4, yb4, pipe_width, heightb4, br);			//Non oriented greens
	




	br.texture = std::string(ASSET_PATH) + "pipe-red.png";
	br.outline_opacity = 0.0f;

	
	graphics::drawRect(xb5, yb5, pipe_width, heightb5, br);
	

	graphics::setOrientation(-180.0f);								//Oriented reds
	graphics::drawRect(xt4, yt4, pipe_width, heightt4, br);
	
	graphics::resetPose();

}
void Pipe::init()
{
	
	xt1 = CANVAS_WIDTH;
	yt1 = 0;
	heightt1 = CANVAS_HEIGHT - 150;
	xb1 = CANVAS_WIDTH;
	yb1 = CANVAS_HEIGHT - 150;
	heightb1 = CANVAS_HEIGHT - yb1-50;									// CANVAS_HEIGHT - yb1;


	xt4 = xt1 + 150;
	yt4 = 0;
	heightt4 = CANVAS_HEIGHT - 250;
	xb4 = xb1 + 150;
	yb4 = CANVAS_HEIGHT - 150;		//340
	heightb4 = CANVAS_HEIGHT - yb4 + 100;



	xt2 = xt1 + 300;		//to have some space between t1 and t2
	yt2 = 0;
	heightt2 = CANVAS_HEIGHT - 140;
	xb2 = xb1 + 300;
	yb2 = CANVAS_HEIGHT - 160;
	heightb2 = CANVAS_HEIGHT - yb2;											//CANVAS_HEIGHT-yb2;

	xt5 = xt2 + 150;
	yt5 = 0;
	heightt5 = CANVAS_HEIGHT - 250;
	xb5 = xb2 + 150;
	yb5 = CANVAS_HEIGHT - 150;		//340
	heightb5 = CANVAS_HEIGHT - yb5 + 100;

	xt3 = xt2 + 300;		//to have some space between t1 and t2
	yt3 = 0;
	heightt3 = CANVAS_HEIGHT - 160;
	xb3 = xb2 + 300;
	yb3 = CANVAS_HEIGHT - 140;
	heightb3 = CANVAS_HEIGHT - yb3;	


}

Pipe::Pipe(const Game& game) :GameObject(game) {
	init();
}

Pipe::~Pipe() {
}
