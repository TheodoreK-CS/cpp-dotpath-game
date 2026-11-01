#include "button.h"
#include "graphics.h"

void Button::set_active(bool set)
{
    is_active = set;
}

void Button::update()
{

}

void Button::draw()
{
	graphics::Brush br;
    if (is_active) {
        //Yellow for activated
        br.fill_color[0] = 1.0f;
        br.fill_color[2] = 0.0f;
        br.fill_opacity = 1.0f;
    }
    else {
        //Transparent white for not activated
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 1.0f;
        br.fill_color[2] = 1.0f;
        br.fill_opacity = 0.4f;
    }
	graphics::drawDisk(pos_x, pos_y, size, br);

}

void Button::init()
{
}

Button::Button()
{
    pos_x = 50, pos_y = 50;
    is_active = false;
}

Button::~Button()
{
}
