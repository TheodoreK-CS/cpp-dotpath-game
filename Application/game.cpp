#include "game.h"
#include "graphics.h"
#include "config.h"
#include "globalstate.h"


void Game::update()
{
	if (game_started) {

		//spawning all buttons and player if player hasnt been initialized
		if (!player_initialized) {

			//spawn map depending on the level
			state->spawn_map();

			//spawn player
			if (!state->get_player()) {
				state->create_player();
			}

			//initialize player
			player_initialized = true;

			//set starting button active
			state->set_button_active(0, 0, true);
		}

		//if player has been initialized
		if (player_initialized) {

			//if player exists
			if (state->get_player()) {

				//update player and buttons and return player position
				GlobalState::Pos updated = state->update();

				//get updated player position
				int col = updated.x;
				int row = updated.y;

				//if player isnt still on same position
				if (row != last_row || col != last_col) {

					//if button exists
					if (state->get_button(row, col) != nullptr) {

						//if button already active(fail condition)
						if (state->get_button(row, col)->is_active) {
							resetLevel();
						}

						//else if button inactive
						else {

							//activates new button
							state->set_button_active(row, col, true);

							//+1 buttons activated
							state->buttons_activated++;

							//play pop sound
							graphics::playSound(std::string(ASSET_PATH) + "pop.mp3", 0.8f, false);

							//adds button to trail path
							m_trail.push_back(state->get_button(row, col));

							//updates current location so that the level doesn't reset when still
							last_row = row;
							last_col = col;

						}

					}

					//if obstacle
					else {

						//take the player back to their last position
						state->set_player_pos(last_col * 100.0f + 50.0f, last_row * 100.0f + 50.0f);
					}
				}
			}
		}

		//if won level
		if (state->isLevelComplete()) {

			//clean up old map
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 10; j++) {
					if (state->get_button(i, j)) {
						state->delete_button(i, j);
					}
				}
			}


			//delete player
			if (state->get_player()) {
				state->delete_player();
			}

			//if next level exists
			if (state->nextLevel()) {

				//force re initialization
				player_initialized = false;
				state->total_buttons = 50;
				state->buttons_activated = 1;
				graphics::playSound(std::string(ASSET_PATH) + "nextLevel.mp3", 0.5f, false);

			}

			//else if won the game
			else {

				if (win_sound_flag) {
					graphics::playSound(std::string(ASSET_PATH) + "victory.mp3", 0.5f, false);
					win_sound_flag = false;
				}

				//space input to quit
				if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
					graphics::stopMessageLoop();
				}
				return;
			}
		}
	}
	else {

		//space input to start
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			game_started = true;
		}
	}
	
}

void Game::draw()
{
	//draw player map and trail
	state->draw(m_trail);

	//draw starting screen
	if (!game_started) {
		state->draw_start();
	}

	//draw winning screen
	if (state->isLevelComplete()) {

		if (state->nextLevel() == false) {
			m_trail.clear();
			state->draw_end();
		}
	}
}

void Game::init()
{
}

void Game::resetLevel()
{
	//reset player position
	if (state->get_player()) {
		state->set_player_pos(50.0f, 50.0f);
	}

	//reset grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			state->set_button_active(i, j, false);
		}
	}

	state->set_button_active(0, 0, true);
	state->resetCounter();

	//reset trail
	m_trail.clear();

	//add first button to trail
	if (state->get_button(0, 0)) {
		m_trail.push_back(state->get_button(0, 0));
	}

	last_row = 0;
	last_col = 0;
}

//creator
Game::Game()
{
	state = new GlobalState();
}

//destructor
Game::~Game()
{

	//delete game state
	if (state) {
		delete state;
		state = nullptr;
	}

}
