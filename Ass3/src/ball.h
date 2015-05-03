/*
 * ball.h
 *
 *  Created on: 23-Apr-2015
 *      Author: rakshak
 */

#ifndef BALL_H_
#define BALL_H_
#include "headers.h"

class ball {
public:
	ball();
	float radius;
	float prev_c_x;
	float prev_c_y;
	float center_x;
	float center_y;
	float speed_x;
	float speed_y;
	float gravity;
	char ball_mode;
	int handled_by;
	sf::CircleShape circle;
	sf::FloatRect bound_box;

	void ball_collision_with_wall();
	bool check_goal();
	void draw_ball();
	void move_ball();
	void check_handling_by_players();
};

#endif /* BALL_H_ */
