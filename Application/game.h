#pragma once
#include "globalstate.h"
#include <vector>

class Game {
	int last_row = -1;
	int last_col = -1;
	//check if player exists
	bool player_initialized = false;
	//create gamestate pointer
	GlobalState * state = nullptr;
	//winning sound flag
	bool win_sound_flag = true;
	//game started flag
	bool game_started = false;
	//button pointer type vector used for drawing the lines
	std::vector<Button*> m_trail;
 
public:
	void update();
	void draw();
	void init();
	void resetLevel();
	Game();
	~Game();
};