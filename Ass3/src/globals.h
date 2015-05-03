/*
 * globals.h
 *
 *  Created on: 19-Apr-2015
 *      Author: rakshak
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_
#define PARAMS 8
#define PARAMS_BALL 2
#include "headers.h"

extern int teamAscore;
extern int teamBscore;
extern char last_thrown;
extern int last_player;
extern int port_no;
extern bool isHost;
extern int handle_ball_counter;
extern int num_total_players;
extern int num_players;
extern int num_ai_players;
extern int player_id;
extern int sock, n;
extern unsigned int length;
extern socklen_t fromlen;
extern struct sockaddr_in server, from;
extern vector<struct sockaddr_in> from_vec;
extern const char* host_name;

extern char buf_s[1024];
extern char buf_r[1024];
extern char arr_buf_s[PARAMS][1024];
extern float window_width;
extern float window_height;
extern int count_team_a;
extern int count_team_b;
extern vector<bool> team_vec;
extern bool goal_done;

float cal_dist(float x1, float y1, float x2, float y2);
void error(const char *msg);
void run_server_udp();
void run_client_udp(const char* host_name);
void run_host();
void run_non_host();

#endif /* GLOBALS_H_ */
