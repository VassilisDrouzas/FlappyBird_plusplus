#ifndef PIPE_H
#define PIPE_H
#include "Gameobject.h"
#include "my_config.h"
#include "graphics.h"


class Pipe :public GameObject {

	float xt1, yt1, xb1, yb1, xt2, yt2, xb2, yb2, xt3, yt3, xb3, yb3, xt4, yt4, xb4, yb4, xt5, yt5, xb5, yb5,xt6,yt6;		//coordinates of pipes
	
	const float pipe_width = 50.0f;
	float heightt1, heightb1, heightt2, heightb2, heightt3, heightb3,heightt4,heightb4,heightt5,heightb5;
	
	
	
	graphics::Brush brush;
	
					
	
	

	bool pipes_initialized = false;
	int score = 0;
	const int space = 150;
	graphics::Brush br;

public:
	void update() override;
	
	void update_hard()override;
	void draw() override;
	
	void draw_hard()override;
	void init() override;


	float getCoordinateXT1() { return xt1; }
	float getCoordinateXB1() { return xb1; }
	float getCoordinateXT2() { return xt2; }
	float getCoordinateXB2() { return xb2; }
	float getCoordinateXT3() { return xt3; }
	float getCoordinateXB3() { return xb3; }
	float getCoordinateXT4() { return xt4; }
	float getCoordinateXB4() { return xb4; }
	float getCoordinateXT5() { return xt5; }
	float getCoordinateXB5() { return xb5; }
	
	
	
	
	float getCoordinateYT1() { return yt1; }
	float getCoordinateYB1() { return yb1; }
	float getCoordinateYT2() { return yt2; }
	float getCoordinateYB2() { return yb2; }
	float getCoordinateYT3() { return yt3; }
	float getCoordinateYB3() { return yb3; }
	float getCoordinateYT4() { return yt4; }
	float getCoordinateYB4() { return yb4; }
	float getCoordinateYT5() { return yt5; }
	float getCoordinateYB5() { return yb5; }
	
	
	
	
	float getHeightt1() { return heightt1; }
	float getHeightb1() { return heightb1; }
	float getHeightt2() { return heightt2; }
	float getHeightb2() { return heightb2; }
	float getHeightt3() { return heightt3; }
	float getHeightb3() { return heightb3; }
	float getHeightt4() { return heightt4; }
	float getHeightb4() { return heightb4; }
	float getHeightt5() { return heightt5; }
	float getHeightb5() { return heightb5; }
	
	

	float getPipeWidth() { return pipe_width; }
	
	
	
	Pipe(const class Game& game);
	~Pipe();
};

#endif