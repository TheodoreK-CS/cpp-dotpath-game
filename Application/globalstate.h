#pragma once
#include "button.h"
#include "player.h"
#include <vector>

class GlobalState {
public:

    //level and button information
    int current_level = 1;
    int total_levels = 3;
    int buttons_activated = 1;
    int total_buttons = 50; //5x10 starting grid

    //declare player pointer
    Player* player = nullptr;

    //create button pointer
    Button* grid[5][10];

    //position structure
    struct Pos {
        int x;
        int y;
    };


    bool isLevelComplete();

    bool nextLevel();

    void resetCounter();

    Button* get_button(int i, int j);

    void set_button_active(int i, int j, bool set);

    void delete_button(int i, int j);

    void create_player();

    Player* get_player();

    void delete_player();

    void set_player_pos(float x, float y);

    Pos update();

    void spawn_map();

    void draw(std::vector<Button*> m_trail);

    void draw_start();

    void draw_end();

    GlobalState();

    ~GlobalState();
};