#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject {
protected:
		const class Game& game;
public:
	
	GameObject(const class Game& game);
	
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void update_hard() = 0;
	virtual void draw_hard() = 0;
};

#endif