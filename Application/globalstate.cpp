#include "globalstate.h"
#include "graphics.h"


bool GlobalState::isLevelComplete()
{
    return buttons_activated == total_buttons;
}

bool GlobalState::nextLevel()
{
    if (current_level < total_levels) {
        current_level++;

		//reset counter for new level
        buttons_activated = 1;
        return true;
    }
    else {
        return false;
    }
}

void GlobalState::resetCounter()
{
    buttons_activated = 1;
}

Button* GlobalState::get_button(int i,int j)
{
	//return button from array
	return grid[i][j];
}

//sets button state to active/inactive
void GlobalState::set_button_active(int i, int j, bool set)
{
	if (grid[i][j]) {
		grid[i][j]->set_active(set);
	}
}

//delete button from array
void GlobalState::delete_button(int i, int j)
{
	delete grid[i][j];
	grid[i][j] = nullptr;
}

//create player pointer
void GlobalState::create_player()
{
	player = new Player();
}

//player getter
Player* GlobalState::get_player()
{
	return player;
}

void GlobalState::delete_player()
{
	delete player;
	player = nullptr;
}

//calls player postition setter
void GlobalState::set_player_pos(float x, float y)
{
	player->set_pos(x, y);
}


//updates player and buttons
GlobalState::Pos GlobalState::update()
{
    //update player
    player->update();

    //update all buttons
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j]) {
                grid[i][j]->update();
            }
        }
    }

    //return new player position as a structure
    Pos p;
    p.x = player->getCol();;
    p.y = player->getRow();;
    return p;


}


void GlobalState::spawn_map()
{

	//spawn basic grid(which is the level 1 layout)
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {

			grid[i][j] = new Button();

			grid[i][j]->pos_x = j * 100.0f + 50.0f;
			grid[i][j]->pos_y = i * 100.0f + 50.0f;
		}
	}

	//set obstacles for level 2
	if (current_level == 2) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {

				if (i == 1 && j > 1 && j < 9) {
					grid[i][j] = nullptr;
					total_buttons--;
				}
				if (i == 3 && j > 0 && j < 9) {
					grid[i][j] = nullptr;
					total_buttons--;
				}

			}
		}
	}

	//set obstacles for level 3
	if (current_level == 3) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {

				if (i == 1 && j == 1) {
					grid[i][j] = nullptr;
					total_buttons--;
				}
				if (i == 3 && j == 8) {
					grid[i][j] = nullptr;
					total_buttons--;
				}
				if (i == 2 && (j == 4 || j == 5)) {
					grid[i][j] = nullptr;
					total_buttons--;
				}

			}
		}
	}
}

//draws everything
void GlobalState::draw(std::vector<Button*> m_trail)
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "Background.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw button grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j]) {
				grid[i][j]->draw();
			}
		}
	}

	//draw player
	if (player) {
		player->draw();
	}

	//draw line
	if (m_trail.size() > 1) {
		graphics::Brush br;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
		br.outline_opacity = 0.0f;

		//line thickness
		float thickness = 10.0f;

		for (size_t i = 0; i < m_trail.size() - 1; i++) {
			float x1 = m_trail[i]->pos_x;
			float y1 = m_trail[i]->pos_y;
			float x2 = m_trail[i + 1]->pos_x;
			float y2 = m_trail[i + 1]->pos_y;

			//joint for smooth line turns
			graphics::drawDisk(x1, y1, thickness / 2.0f, br);

			//calculate horizontal and vertical distance
			float dx = x2 - x1;
			float dy = y2 - y1;

			//calculate total distance
			float length = sqrt(dx * dx + dy * dy);

			//find angle and convert to degrees
			float angle = atan2(dy, dx) * 180.0f / 3.14159f;

			//draw line
			graphics::setOrientation(angle);
			graphics::drawRect(x1 + dx / 2.0f, y1 + dy / 2.0f, length, thickness, br);
			graphics::setOrientation(0.0f);

		}
	}


}

void GlobalState::draw_start()
{
	graphics::Brush br;
	std::string text = "Controls: w,a,s,d";

	//add shade
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 0.4f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//set the font
	graphics::setFont(std::string(ASSET_PATH) + "LuckiestGuy-Regular.ttf");

	//set up text dimensions
	float x = CANVAS_WIDTH / 2 - 360;
	float y = CANVAS_HEIGHT / 2 - 25;
	float size = 80;

	//black outline
	br.fill_opacity = 1.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;

	//draw shadow
	graphics::drawText(x - 4, y - 4, size, text, br);
	graphics::drawText(x + 4, y - 4, size, text, br);
	graphics::drawText(x - 4, y + 4, size, text, br);
	graphics::drawText(x + 4, y + 4, size, text, br);

	//red text
	br.fill_color[0] = 0.1f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(x, y, size, text, br);

	//change color to opaque white
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 0.7f;

	//reduce text size
	float br_size = 35.0f;
	text = "Press SPACE to Start";

	//draw text
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2 + 50, br_size, text, br);
}

void GlobalState::draw_end()
{
	graphics::Brush br;
	std::string text = "VICTORY!!!";

	//add shade
	br.texture = "";
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 0.4f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//set the font
	graphics::setFont(std::string(ASSET_PATH) + "LuckiestGuy-Regular.ttf");

	//set up text dimensions
	float x = CANVAS_WIDTH / 2 - 280;
	float y = CANVAS_HEIGHT / 2 + 25;
	float size = 110;

	//black outline
	br.fill_opacity = 1.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;

	//draw shadow
	graphics::drawText(x - 4, y - 4, size, text, br);
	graphics::drawText(x + 4, y - 4, size, text, br);
	graphics::drawText(x - 4, y + 4, size, text, br);
	graphics::drawText(x + 4, y + 4, size, text, br);

	//red text
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(x, y, size, text, br);

	//change color to opaque white
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 0.7f;

	//reduce text size
	float br_size = 35.0f;
	text = "Press SPACE to Quit";

	//draw text
	graphics::drawText(CANVAS_WIDTH / 2 - 180, CANVAS_HEIGHT / 2 + 100, br_size, text, br);
}

GlobalState::GlobalState()
{
	current_level = 1;
	buttons_activated = 1;
	total_buttons = 50;
}

GlobalState::~GlobalState()
{

	//delete grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j]) {
				delete grid[i][j];
				grid[i][j] = nullptr;
			}
		}
	}

	//deletes player
	if (player) {
		delete player;
		player = nullptr;
	}
}
