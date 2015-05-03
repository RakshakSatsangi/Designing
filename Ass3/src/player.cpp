/*
 * player.cpp
 *
 *  Created on: 20-Apr-2015
 *      Author: rakshak
 */
#include "player.h"
#include "ball.h"
#include "Goal.h"
#include "headers.h"
extern ball q_ball;
extern Goal goal;
extern sf::RenderWindow window;
//vector<Player> players_vec;

Player::Player(float x_l,
		float y_u, float pl_w, float pl_h, bool t) {
	team = t;
	if(team)
	{
		image_l.loadFromFile("player_l.png");
		image_r.loadFromFile("player_r.png");
	} else {
		image_l.loadFromFile("player_l1.png");
		image_r.loadFromFile("player_r1.png");
	
	};
	ai_mode = false;

	speed_x = 15;
	speed_y = 15;
	orientation = true;
	x_left = x_l;
	y_up = y_u;
	pl_width = pl_w;
	pl_height = pl_h;
	rectangle.setTexture(image_l);
	rectangle.setScale(sf::Vector2f(0.25f, 0.2f));
	rectangle.setPosition(x_left, y_up);
	player_mode = 'f';
	handle_ball_by = -1;
}

void Player::draw_player() {
	if (orientation) {
		rectangle.setTexture(image_l);
	} else {
		rectangle.setTexture(image_r);
	}
	rectangle.setPosition(x_left, y_up);
}
void Player::action() {
	move_left = 0;
	move_right = 0;
	move_up = 0;
	move_down = 0;
	throw_call = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		move_up = true;
		;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		move_down = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		move_left = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		move_right = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
		if(!ai_mode){
			mouse_pos_x = sf::Mouse::getPosition(window).x;
			mouse_pos_y = sf::Mouse::getPosition(window).y;
			throw_call = true;	
		}
		
	}
}

void Player::cal_my_nextstate() {
	prev_x_l = x_left;
	prev_y_u = y_up;
	if(ai_mode){
		move_left = 0;
		move_right = 0;
		move_up = 0;
		move_down = 0;
		throw_call = 0;
		char a;
		/*if(team)
			a = 'a';
		else
			a = 'b';
		//if(last_thrown = a){*/
			if(q_ball.center_x > x_left + 1.5*pl_width){
				move_right = true;
			}
			else if(q_ball.center_x + 2*q_ball.radius < x_left )
			{
				move_left = true;
			}
			if(q_ball.center_y > y_up + 1.5 * pl_height){
				move_down = true;
			}else if(q_ball.center_y + 2 * q_ball.radius + 0.5*pl_height < y_up){
				move_up = true;
			}
			if(player_mode == 'h'){
				if(goal.x_cor - x_left-1.5*pl_width>0){
					move_right = true;
				}
				if(goal.y_cor > y_up + 1.5*pl_height){
					move_down = true;
				}
				else if(goal.y_cor + 0.5*pl_height < y_up){
					move_up = true;
				}
			}
			if(handle_ball_counter > 20){
				throw_call = true;
				mouse_pos_x = goal.x_cor;
				mouse_pos_y = goal.y_cor + goal.height/2;
			}
		
	}
	switch (player_mode) {
	/*case 'f':
		if(handle_ball_by == player_id)
		 {
		 player_mode = 'h';
		 }
		break;*/
	case 'h':

		if (throw_call || (handle_ball_counter > 80)) {
			cout << "Throw...HBC: " << handle_ball_counter << endl;
			
//			player_mode = 't';
			q_ball.ball_mode = 't';
		}
		break;
	/*case 't':
		q_ball.ball_mode = 't';
		break;*/
	}

	move_player();
}
void Player::move_player() {
	if (move_up) {
		if (y_up > 0) {
			y_up -= speed_y;
		}
	}
	if (move_down) {
		if (y_up + pl_height < window_height) { // window bottom parameter
			y_up += speed_y;
		}
	}
	if (move_left) {
		if (x_left > 0)
			x_left -= speed_x;
		orientation = true;
	}
	if (move_right) {
		if (x_left + pl_width < window_width)
			x_left += speed_x;
		orientation = false;
	}
}

void Player::move_prev_pos() {
	x_left = prev_x_l;
	y_up = prev_y_u;
}

bool Player::check_collision_two_players(Player a) {
	return ((a.x_left - x_left < pl_width && a.x_left - x_left > -pl_width)
			&& (a.y_up - y_up < pl_height && a.y_up - y_up > -pl_height));
}

