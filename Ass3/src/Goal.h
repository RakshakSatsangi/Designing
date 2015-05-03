/*
 * Goal.h
 *
 *  Created on: 23-Apr-2015
 *      Author: rakshak
 */

#ifndef GOAL_H_
#define GOAL_H_

#include "headers.h"
class Goal {
public:
	Goal(float x, float y, float w, float h);
	float x_cor;
	float y_cor;
	sf::RectangleShape line;
	sf::Texture image_upon_goal;
	float width;
	float height;
	void draw_goal();
	void refresh_goal();
};

#endif /* GOAL_H_ */
