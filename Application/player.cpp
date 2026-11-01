#include "player.h"
#include "graphics.h"

void Player::set_pos(float x, float y)
{
	pos_x = x;
	pos_y = y;
}

void Player::update()
{
	//flags so player only moves once per key pressed
	static bool a_was_pressed = false;
	static bool d_was_pressed = false;
	static bool w_was_pressed = false;
	static bool s_was_pressed = false;

	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		if (!a_was_pressed) {
			pos_x -= 100.0f;
			a_was_pressed = true;
		}
	}
	else {
		a_was_pressed = false;
	}

	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		if (!d_was_pressed) {
			pos_x += 100.0f;
			d_was_pressed = true;
		}
	}
	else {
		d_was_pressed = false;
	}

	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		if (!w_was_pressed) {
			pos_y -= 100.0f;
			w_was_pressed = true;
		}
	}
	else {
		w_was_pressed = false;
	}

	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		if (!s_was_pressed) {
			pos_y += 100.0f;
			s_was_pressed = true;
		}
	}
	else {
		s_was_pressed = false;
	}


	if (pos_x < 50) {
		pos_x = 50;
	}
	if (pos_x > 950) {
		pos_x = 950;
	}
	if (pos_y < 50) {
		pos_y = 50;
	}
	if (pos_y > 450) {
		pos_y = 450;
	}
}

void Player::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, size, br);
}

void Player::init()
{
}

int Player::getCol()
{
	return (int)((pos_x - 50) / 100);
}

int Player::getRow()
{
	return (int)((pos_y - 50) / 100);
}

Player::Player()
{
	pos_x = 50, pos_y = 50;
}

Player::~Player()
{
}
