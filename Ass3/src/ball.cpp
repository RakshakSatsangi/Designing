/*
 * ball.cpp
 *
 *  Created on: 23-Apr-2015
 *      Author: rakshak
 */

#include "ball.h"
#include "player.h"
#include "Goal.h"
extern vector<Player> players_vec;
extern sf::RenderWindow window;
extern Goal goal;
ball::ball() {
	srand ( time(NULL));
	center_x = 600;
	center_y = 300;
	radius = 20;
	//int theta = rand();
	int theta = 5;
	speed_x = 15 * sin(theta);
	speed_y = 15 * cos(theta);
	gravity = 0.1;
	circle.setRadius(radius);
	circle.setFillColor(sf::Color(100, 250, 50));
	circle.setOutlineThickness(5);
	circle.setPosition(center_x, center_y);
	ball_mode = 'f';
}

void ball::ball_collision_with_wall() {
	if (center_x + 2 * radius > window_width) {
		speed_x = -speed_x;
		center_x = prev_c_x;
	} else if (center_x < 0) {
		speed_x = -speed_x;
		center_x = prev_c_x;
	}
	if (center_y + 2 * radius > window_height) {
		speed_y = -speed_y;
		center_y = prev_c_y;
	} else if (center_y < 0) {
		speed_y = -speed_y;
		center_y = prev_c_y;
	}
}
void ball::move_ball() {
	prev_c_x = center_x;
	prev_c_y = center_y;
	switch (ball_mode) {
	case 'f':

		speed_y += gravity;
		center_x += speed_x;
		center_y += speed_y;

		// check for goal
		check_goal();

		if (ball_mode == 'f') {
			// handle collision with walls
			ball_collision_with_wall();

			// check_handling by other players
			check_handling_by_players();
		}
		break;
	case 'h':
		if (players_vec[handled_by].orientation) {
			center_x = players_vec[handled_by].x_left;
			center_y = players_vec[handled_by].y_up + 30; // 10 is to set the pos of ball in the frame of player
		} else {
			center_x = players_vec[handled_by].x_left
					+ players_vec[handled_by].pl_width - 2 * radius;
			center_y = players_vec[handled_by].y_up + 30;
		}
		if (last_thrown == 'a' && players_vec[handled_by].team == 0
				&& last_player != handled_by)
			teamAscore++;
		if (last_thrown == 'b' && players_vec[handled_by].team == 1
				&& last_player != handled_by)
			teamBscore++;
		last_thrown = 'x';
		// ball_mode will be changed from 'h' to 't' by player key handle
		break;
	case 't': {
		players_vec[handled_by].bound_box
				= players_vec[handled_by].rectangle.getGlobalBounds();
		// mouse pointer must not be inside the rectangle of the player as it would lead to infinite loop below
		if (players_vec[handled_by].bound_box.contains(
				sf::Vector2f(players_vec[handled_by].mouse_pos_x,
						players_vec[handled_by].mouse_pos_y))) {
			ball_mode = 'h';
			players_vec[handled_by].player_mode = 'h';
			return;
		}
		float tan_theta = (players_vec[handled_by].mouse_pos_y - center_y)
				/ (players_vec[handled_by].mouse_pos_x - center_x);

		if ((players_vec[handled_by].mouse_pos_x - center_x) < 0) {
			speed_x = -15 * cos(atan(tan_theta));
			speed_y = -15 * sin(atan(tan_theta));
		} else {
			speed_x = 15 * cos(atan(tan_theta));
			speed_y = 15 * sin(atan(tan_theta));
		}
		last_player = handled_by;
		if (players_vec[handled_by].team == 0)
			last_thrown = 'a';
		if (players_vec[handled_by].team == 1)
			last_thrown = 'b';
		do {

			bound_box = circle.getGlobalBounds();
			center_x += speed_x;
			center_y += speed_y;
			ball_collision_with_wall();
			circle.setPosition(center_x, center_y);
		} while (players_vec[handled_by].bound_box.intersects(bound_box));
		players_vec[handled_by].player_mode = 'f';
		ball_mode = 'f';
		// may be better if coll with wall, player and goal is checked again here now		
		// check_handling by other players
		check_handling_by_players();

		break;
	}
	case 'g':
		// center_x += speed_x;
		// center_y += speed_y;

		if (last_thrown == 'a')
			teamAscore += 2;
		if (last_thrown == 'b')
			teamBscore += 2;
		last_thrown = 'x';

		center_x = 0;
		center_y = 0;
		prev_c_x = 0;
		prev_c_y = 0;
		speed_x = 0;
		ball_mode = 'f';
		cout << "goal" << endl;

		//when goal occurs,display an image for sometime and send a ball to an empty corner
		sf::Texture goal;
		goal.loadFromFile("after_goal.png");
		sf::Sprite sprite_goal;
		sprite_goal.setTexture(goal);
		sprite_goal.setScale(sf::Vector2f(0.7f, 0.5f));
		int x = 0;
		int y = 0;
		sf::Texture image_bkg;
		image_bkg.loadFromFile("background.png");
		sf::Sprite sprite_bkg;
		sprite_bkg.setTexture(image_bkg);
		sprite_bkg.setScale(sf::Vector2f(1.0f, 1.2f));

		sf::Clock clock1;
		double t1 = clock1.getElapsedTime().asSeconds();
		while (t1 < 0.5) { // keep it less so that non-host does not skip the recv from
			window.clear();
			window.draw(sprite_bkg);
			sprite_goal.setPosition(x, y);
			t1 = clock1.getElapsedTime().asSeconds();
			window.draw(sprite_goal);
			window.display();
			x = x + 5;

		}
		clock1.restart();
		break;

	}

}

void ball::draw_ball() {
	circle.setPosition(center_x, center_y);
	window.draw(circle);
}
bool ball::check_goal() {
	if ((center_x + 2 * radius > goal.x_cor) && center_y > goal.y_cor
			&& (center_y + 2 * radius < goal.y_cor + goal.height)) {
		ball_mode = 'g';
		return true;
	}
	return false;

}

void ball::check_handling_by_players() {
	bound_box = circle.getGlobalBounds();
	for (int i = 0; i < num_total_players; i++) {
		players_vec[i].bound_box = players_vec[i].rectangle.getGlobalBounds();
		if (players_vec[i].bound_box.intersects(bound_box)) {
			// here ith player is expected to be in free mode, in fact all players.
			ball_mode = 'h';
			if (center_x + 2 * radius < players_vec[i].x_left
					+ (players_vec[i].pl_width) / 2) {
				players_vec[i].orientation = true;
			} else {
				players_vec[i].orientation = false;
			}
			handled_by = i;
			players_vec[i].player_mode = 'h';
			players_vec[i].handle_ball_by = handled_by;
			handle_ball_counter = 0;
		}
	}
}
