#include "Menu.h"
#include "globals.h"
#include "player.h"
#include "headers.h"
#include "ball.h"
#include "Goal.h"
#include <sstream>

#define MAX_NUMBER_OF_ITEMS 9

using namespace std;

vector<Player> players_vec;
ball q_ball;
Goal goal(1020, 250, 4, 250);
sf::RenderWindow window;
int count_inter = 0;

void drawscore(int teamscore, char team) {
	//create a font
	sf::Font font;

	// Load it from a file
	if (!font.loadFromFile("arial.ttf"))
	//find this file in the "pong" example in the SFML examples folder
	{
		std::cout << "Error loading font\n";
	}
	sf::Text atext;
	atext.setFont(font);
	atext.setCharacterSize(20);
	atext.setStyle(sf::Text::Bold);
	atext.setColor(sf::Color::White);
	if (team == 'a')
		atext.setPosition(0, 0);
	else if (team == 'b')
		atext.setPosition(0, 30);
	stringstream ss; //string buffer to convert numbers to string
	ss << "TEAM  " << team << " :" << teamscore;
	atext.setString(ss.str());

	//draw the string
	window.draw(atext);

}

bool check_collision_all_players() {
	for (int i = 0; i < num_total_players; i++) {
		players_vec[i].move_player();
		for (int j = 0; j < num_total_players; j++) {
			if (i != j && players_vec[i].check_collision_two_players(
					players_vec[j])) {
				players_vec[i].move_prev_pos();
				break;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(0);
	}
	port_no = atoi(argv[1]);
	host_name = argv[2];
	Menu::init_window();
	if (isHost) {
		run_host();
	} else {
		run_non_host();
	}

	// creating num_players no. of players
	for (int i = 0; i < num_players; i++) {
		Player pl(100 * (i + 1), 200 * (i + 1),
				230, 100, team_vec[i]);
		pl.player_id = i;
		players_vec.push_back(pl);
	}
	// creating AI Players
	num_ai_players = num_total_players - num_players;
	for (int i = num_players; i < num_total_players; i++) {
		bool ai_team;
		if(count_team_a < num_total_players/2){
			ai_team = 0;
			count_team_a++;
			team_vec.push_back(0);
		}
		else {
			ai_team = 1;
			count_team_b++;
			team_vec.push_back(1);
		}
		Player pl(100 * (i + 1), 200 * (i + 1),
				230, 100, ai_team);
		pl.ai_mode = true;
		pl.player_id = i;
		players_vec.push_back(pl);
	}

	// new window
	window.create(sf::VideoMode(window_width, window_height),
			"QUIDDITCH: PLAY IT MY WAY", sf::Style::Default);

	sf::Music music;

	if (!music.openFromFile("cat.ogg")) {
		error("Failed to open music file. The file may have been removed.");
	}

	music.play();
	music.setPlayingOffset(sf::seconds(10));
	music.setVolume(75);

	// strategic time out
	struct timeval timeout;
	timeout.tv_sec = (time_t) 1;
	timeout.tv_usec = 1;

	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
			sizeof(timeout)) < 0)
		error("setsockopt failed\n");
	// st timeout ends

	// background image sprite
	sf::Texture image_bkg;
	image_bkg.loadFromFile("background.png");
	sf::Sprite sprite_bkg;
	sprite_bkg.setTexture(image_bkg);
	sprite_bkg.setScale(sf::Vector2f(1.0f, 1.2f));

	// creating a array which decides the order in which info is send/received
	char ord_send_rcv[num_players];
	for (int i = 0; i < num_players; i++) {
		ord_send_rcv[i] = 'r';
	}
	ord_send_rcv[player_id] = 's';
	int index_calculator_ball_state = 1;
	sf::Clock clock;
	double time_elapsed = 0;
	bool break_off = false;
	bool break_off_oth = false;
	int katta_wala = -1;
	int id_error_check_init;
	int id_error_check_end;
	while (window.isOpen()) {

		handle_ball_counter++;
		players_vec[player_id].action(); // includes instructions like keyboard,etc too

		// Sending and receiving player information...

		if (!isHost) {
			if (player_id > 0) {
				timeout.tv_sec = (time_t) 0;
				timeout.tv_usec = 100000*player_id;

				if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
						sizeof(timeout)) < 0)
					error("setsockopt failed\n");

				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					cout << "Exiting...Connection Failure!!!...in Non Host: " << endl;
					//	exit(0);

				}
			}
			
			bzero(arr_buf_s[0], 1024);
			memcpy(arr_buf_s[0], &player_id, sizeof(int));

			bzero(arr_buf_s[1], 1024);
			memcpy(arr_buf_s[1], &players_vec[player_id].move_left,
					sizeof(bool));

			bzero(arr_buf_s[2], 1024);
			memcpy(arr_buf_s[2], &players_vec[player_id].move_right,
					sizeof(bool));

			bzero(arr_buf_s[3], 1024);
			memcpy(arr_buf_s[3], &players_vec[player_id].move_up, sizeof(bool));

			bzero(arr_buf_s[4], 1024);
			memcpy(arr_buf_s[4], &players_vec[player_id].move_down,
					sizeof(bool));

			bzero(arr_buf_s[5], 1024);
			memcpy(arr_buf_s[5], &players_vec[player_id].throw_call,
					sizeof(bool));

			bzero(arr_buf_s[6], 1024);
			memcpy(arr_buf_s[6], &players_vec[player_id].mouse_pos_x,
					sizeof(int));

			bzero(arr_buf_s[7], 1024);
			memcpy(arr_buf_s[7], &players_vec[player_id].mouse_pos_y,
					sizeof(int));

			for (int j = 0; j < PARAMS; j++) {

				sendto(sock, arr_buf_s[j], 1024, 0,
						(struct sockaddr *) &server, length);

			}
			sendto(sock, arr_buf_s[0], 1024, 0,
						(struct sockaddr *) &server, length);

			if (player_id < num_players - 2) {
				sendto(sock, "Go on Bitch", strlen("Go on Bitch"), 0,
						(struct sockaddr *) &from_vec[player_id + 1], length);
			}
			while (1) {
				time_elapsed = clock.getElapsedTime().asMilliseconds();
				if (time_elapsed > 1) {
					clock.restart();
					break;
				}
			}

		} else {
			timeout.tv_sec = (time_t) 1;
			timeout.tv_usec = 1;

			if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
					sizeof(timeout)) < 0)
				error("setsockopt failed\n");

			for (int rs = 0; rs < num_players - 1; rs++) {
				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					
					if(!break_off_oth){
						katta_wala = rs;
					}
					break_off = true;
					break;
					//	exit(0);	
					
					

				}
				memcpy(&id_error_check_init, buf_r, sizeof(int));
				if(id_error_check_init!=rs){
					if(!break_off_oth){
						katta_wala = rs;
						break_off = true;
						break_off_oth = true;
						
					}
					
				}

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&players_vec[rs].move_left, buf_r, sizeof(bool));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&players_vec[rs].move_right, buf_r, sizeof(bool));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&players_vec[rs].move_up, buf_r, sizeof(bool));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&players_vec[rs].move_down, buf_r, sizeof(bool));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&players_vec[rs].throw_call, buf_r, sizeof(bool));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);
				}
				memcpy(&players_vec[rs].mouse_pos_x, buf_r, sizeof(int));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);
				}
				memcpy(&players_vec[rs].mouse_pos_y, buf_r, sizeof(int));
				
				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					break_off = true;
					break;
					//	exit(0);

				}
				memcpy(&id_error_check_end, buf_r, sizeof(int));
				if(id_error_check_init!=id_error_check_end){
					if(!break_off_oth){
						katta_wala = id_error_check_init;
						break_off = true;
						break_off_oth = true;	
					}
					
					
				}
			}
			while (1) {
				time_elapsed = clock.getElapsedTime().asMilliseconds();
				if (time_elapsed > 1) {
					clock.restart();
					break;
				}
			}
			if(break_off){
				break_off = false;
				cout << "Network Disconnected For: "<<katta_wala<<endl;
				for(int i=0; i<num_players-1; i++){
					sendto(sock, "wait", strlen("wait"), 0, (struct sockaddr *) &from_vec[i], length);
					bzero(arr_buf_s[0], 1024);
					memcpy(arr_buf_s[0], &katta_wala, sizeof(int));
					sendto(sock, arr_buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], length);
				}
				while (1) {
					time_elapsed = clock.getElapsedTime().asMilliseconds();
					if (time_elapsed > 1000) {
						clock.restart();
						break;
					}
				}
			//vector<Player> players_vec_tmp;
					players_vec[katta_wala].ai_mode = true;
				from_vec.push_back(from_vec[katta_wala]);
				players_vec.push_back(players_vec[katta_wala]);
				for(int i = katta_wala+1; i <num_players+1; i++){
					// struct sockaddr_in temp = from_vec[i];
					{
						from_vec[i - 1] = from_vec[i];
						players_vec[i-1]=players_vec[i];
						//players_vec_tmp.push_back(players_vec[i]);
					}

				}
				from_vec.pop_back();
				players_vec.pop_back();
				if(player_id > katta_wala){
					player_id--;
				}
				num_players--;
				continue;
			}
		}
		
		if (isHost) {
			for (int i = 0; i < num_total_players; i++) {
				players_vec[i].cal_my_nextstate();
			}

			// check collision for all players
			check_collision_all_players();

			// now all players are validly placed...now we move the ball since we also know now the instruction given to ball like throw, etc.
			for (int i = 0; i < num_total_players; i++) {
				players_vec[i].draw_player(); // this step needs to be done as the rectangle must be set positioned before calling move_ball
			}

			q_ball.move_ball();
			// now we are done away with positioning the ball at valid spot...we can draw the ball now

			// send each player calculated params of all players
			for (int i = 0; i < num_players - 1; i++) {
				for (int j = 0; j < num_total_players; j++) {

					bzero(arr_buf_s[0], 1024);
					memcpy(arr_buf_s[0], &players_vec[j].x_left, sizeof(float));

					bzero(arr_buf_s[1], 1024);
					memcpy(arr_buf_s[1], &players_vec[j].y_up, sizeof(float));

					bzero(arr_buf_s[2], 1024);
					memcpy(arr_buf_s[2], &players_vec[j].orientation,
							sizeof(bool));

					for (int k = 0; k < 3; k++) {
						sendto(sock, arr_buf_s[k], 1024, 0,
								(struct sockaddr *) &from_vec[i], length);

					}

				}
			}

			// send each player params_ball
			for (int i = 0; i < num_players - 1; i++) {
				bzero(arr_buf_s[0], 1024);
				memcpy(arr_buf_s[0], &q_ball.center_x, sizeof(float));

				bzero(arr_buf_s[1], 1024);
				memcpy(arr_buf_s[1], &q_ball.center_y, sizeof(float));

				// sending socres of team_a and team_b
				bzero(arr_buf_s[2], 1024);
				memcpy(arr_buf_s[2], &teamAscore, sizeof(int));


				bzero(arr_buf_s[3], 1024);
				memcpy(arr_buf_s[3], &teamBscore, sizeof(int));

				for (int j = 0; j < 4; j++) {
					sendto(sock, arr_buf_s[j], 1024, 0,
							(struct sockaddr *) &from_vec[i], length);

				}
			}

		} else {
			timeout.tv_sec = (time_t) 2;
			timeout.tv_usec = 1;

			if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
					sizeof(timeout)) < 0)
				error("setsockopt failed\n");

			// receive params of all players
			for (int i = 0; i < num_total_players; i++) {
				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
					break_off = true;
					break;
					// exit(0);

				}
				string s = buf_r;
				if(s == "wait")	{
					break_off = true;
					cout << "Waiting as it is not a host error but someone else's network Connection error."<<endl;

					bzero(buf_r, 1024);
					recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length);
					memcpy(&katta_wala, buf_r, sizeof(int));
					cout << "Network Disconnected for: " << katta_wala <<endl;
					break;
				}
				else{
					memcpy(&players_vec[i].x_left, buf_r, sizeof(float));	
				}
				

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
					break_off = true;
					break;
					// exit(0);
				}
				memcpy(&players_vec[i].y_up, buf_r, sizeof(float));

				bzero(buf_r, 1024);
				if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
						&length) < 0) {
					cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
					break_off = true;
					break;
					// exit(0);

				}
				memcpy(&players_vec[i].orientation, buf_r, sizeof(bool));

				// call draw player function to position player's rectangle
				players_vec[i].draw_player();
			}
			if(break_off){
				break_off = false;
				players_vec[katta_wala].ai_mode = true;
				from_vec.push_back(from_vec[katta_wala]);
				players_vec.push_back(players_vec[katta_wala]);
				for(int i = katta_wala+1; i <num_players+1; i++){
					{
						from_vec[i - 1] = from_vec[i];
						players_vec[i-1]=players_vec[i];
					}

				}
				from_vec.pop_back();
				players_vec.pop_back();
				if(player_id > katta_wala){
					player_id--;
				}
				num_players--;
				continue;
			}

			// recieve params_ball
			bzero(buf_r, 1024);
			if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
					&length) < 0) {
				cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
				exit(0);

			}
			memcpy(&q_ball.center_x, buf_r, sizeof(float));

			bzero(buf_r, 1024);
			if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
					&length) < 0) {
				cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
				exit(0);

			}
			memcpy(&q_ball.center_y, buf_r, sizeof(float));

			// receiving scores
			bzero(buf_r, 1024);
			if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
					&length) < 0) {
				cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
				exit(0);

			}
			memcpy(&teamAscore, buf_r, sizeof(int));

			bzero(buf_r, 1024);
			if (recvfrom(sock, buf_r, 1024, 0, (struct sockaddr *) &from,
					&length) < 0) {
				cout << "Exiting...Connection Failure!!!...Error in Host..." << endl;
				exit(0);

			}
			memcpy(&teamBscore, buf_r, sizeof(int));





		}

		// To display various objects on window...
		window.clear();
		window.draw(sprite_bkg);
		//window.draw(q_ball.circle);
		q_ball.draw_ball();
		window.draw(goal.line);
		for (int i = 0; i < num_total_players; i++) {
			//			players_vec[i].draw_player();
			window.draw(players_vec[i].rectangle);
		}
		drawscore(teamBscore, 'b');
		drawscore(teamAscore, 'a');

		window.display();

		while (1) {
			time_elapsed = clock.getElapsedTime().asMilliseconds();
			//						cout << time_elapsed << endl;
			if (time_elapsed > 25) {
				clock.restart();
				break;
			}
		}

	}

}
/*
 * 	a menu for asking no. of players to play and showing his ip etc.
 * 	ask ip in case of join game
 * 	show status of joining in this window
 *
 *  player-ball handling, ball-throwing, ball-keeping
 *  goal-post-player collision, goal-post ball collision, goal(scoring, fresh start)
 *  player-player collision: key wala kam roko,
 *
 *	AI Player: AI Mode variable
 *
 */

/*
 * exchange player co-or: may be invalid state(players overlap)
 * move a player in following manner
 * check coll among players: check coll of ith with 0 to 'i-1'th players: if on moving ith player, anyone of i-1 players are unhappy then don't move ith player
 *
 * ball modes
 * free: move ball. check coll with walls. check for goal or handled by someone
 * handled: keep a record of handled by, handle_ball_counter
 * thrown: if(handled) then make ball free. and then apply func of case free.
 * goaled: start a fresh scenario
 *
 * Draw players: valid scene
 *
 */

