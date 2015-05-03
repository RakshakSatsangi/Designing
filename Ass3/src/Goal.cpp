/*
 * Goal.cpp
 *
 *  Created on: 23-Apr-2015
 *      Author: rakshak
 */

#include "Goal.h"

Goal::Goal(float x, float y, float w, float h) {
	x_cor = x;
	y_cor = y;
	width = w;
	height = h;
	line.setSize(sf::Vector2f(w, h));
	line.setFillColor(sf::Color::White);
	line.setPosition(x, y);
	// TODO Auto-generated constructor stub

}

void Goal::refresh_goal() {
}

