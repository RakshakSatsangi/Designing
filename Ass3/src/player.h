/*
 * player.h
 *
 *  Created on: 20-Apr-2015
 *      Author: rakshak
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "headers.h"
#include "globals.h"

class Player {
public:
	Player(float x_l,
			float y_u, float x_r, float y_d, bool t);
	int player_id;
	char player_mode;
	float prev_x_l;
	float prev_y_u;
	float x_left;
	float y_up;
	float pl_width;
	float pl_height;
	bool orientation;
	float speed_x; // constant throughout
	float speed_y;
	int mouse_pos_x;
	int mouse_pos_y;
	sf::Sprite rectangle;// managed by function draw_player
	sf::Texture image_l; // constant throughout
	sf::Texture image_r;
	bool ai_mode;
	float offset_x;
	bool team;
	sf::FloatRect bound_box;
	bool move_left;
	bool move_right;
	bool move_up;
	bool move_down;
	bool throw_call;
	void action();
	void draw_player();
	void cal_my_nextstate();
	void do_ai();
	bool check_collision_two_players(Player a);
	void move_player();
	void move_prev_pos();
	int handle_ball_by;


};

#endif /* PLAYER_H_ */
