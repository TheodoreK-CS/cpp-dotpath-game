#pragma once
#include "gameobject.h"
#include "config.h"

class Button : public GameObject {


public:
	float pos_x = 50, pos_y = 50;
	float size = 40;
	bool is_active = false;

	void set_active(bool set);

	void update() override;
	void draw() override;
	void init() override;

	Button();

	~Button();

};