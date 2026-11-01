#pragma once
#include "gameobject.h"
#include "config.h"

class Player : public GameObject {

	float pos_x = 50, pos_y = 50;

public:

	float size = 40;

	void set_pos(float x, float y);

	void update() override;
	void draw() override;
	void init() override;


	int getCol();
	int getRow();

	Player();

	~Player();

};