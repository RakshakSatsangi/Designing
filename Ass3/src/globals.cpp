/*
 * globals.cpp
 *
 *  Created on: 19-Apr-2015
 *      Author: rakshak
 */

#include "globals.h"
#include "player.h"
float cal_dist(float x1, float y1, float x2, float y2) {
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int teamAscore = 0;
int teamBscore = 0;
char last_thrown = 'x';
int last_player = -1;
int port_no;
bool isHost;
int handle_ball_counter;
int num_total_players;
int num_players;
int num_ai_players;
int player_id = 0;
int sock, n;
unsigned int length;
socklen_t fromlen;
struct sockaddr_in server, from;
vector<struct sockaddr_in> from_vec;
char buf_s[1024];
char buf_r[1024];
char arr_buf_s[PARAMS][1024];
float window_width = 1024;
float window_height = 768;
bool goal_done = 0;
extern int x11, y11;
const char* host_name;
int count_team_a;
int count_team_b;
vector<bool> team_vec;

void error(const char *msg) {
	perror(msg);
	exit(0);
}

void run_server_udp() {
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("Opening socket");
	length = sizeof(server);
	bzero(&server, length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port_no);
	if (bind(sock, (struct sockaddr *) &server, length) < 0) {
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);
}

void run_client_udp(const char* host_name) {
	struct hostent *hp;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("socket");
	server.sin_family = AF_INET;
	hp = gethostbyname(host_name);
	if (hp == 0)
		error("Unknown host");

	bcopy((char *) hp->h_addr, (char *) &server.sin_addr, hp->h_length);
	server.sin_port = htons(port_no);
	length = sizeof(struct sockaddr_in);
}

void run_host() {

	num_total_players = x11;
	num_players = y11;
	bool team;
	bool myteam;
	cout << "Select Team: 0 or 1: ";
	cin >> myteam;
	if (myteam) {
		count_team_b++;
	} else {
		count_team_a++;
	}
	cout << "================= Host begins ================" << endl;
	run_server_udp();
	for (int i = 0; i < num_players - 1; i++) {
		bzero(buf_s, 1024);
		n = recvfrom(sock, buf_s, 1024, 0, (struct sockaddr *) &from, &fromlen);
		memcpy(&team, buf_s, sizeof(bool));
		
		if(count_team_b == num_total_players/2) {
			team = 0;
		} else if(count_team_a == num_total_players/2){
			team = 1;
		} 
		if(team) {
			count_team_b++;
		} else {
			count_team_a++;
		}

		team_vec.push_back(team);
		from_vec.push_back(from);
	}
	team_vec.push_back(myteam);
	from_vec.push_back(server);

	for (int i = 0; i < num_players - 1; i++) {
		// sending count_team_a
		bzero(buf_s, 1024);
		memcpy(buf_s, &count_team_a, sizeof(int));
		sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], fromlen);

		// sending count_team_b
		bzero(buf_s, 1024);
		memcpy(buf_s, &count_team_b, sizeof(int));
		sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], fromlen);

		// sending num_players
		bzero(buf_s, 1024);
		memcpy(buf_s, &num_players, sizeof(int));
		sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], fromlen);
		// sending num_total_players
		bzero(buf_s, 1024);
		memcpy(buf_s, &num_total_players, sizeof(int));
		sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], fromlen);
		// sending player_id
		bzero(buf_s, 1024);
		memcpy(buf_s, &player_id, sizeof(int));
		sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i], fromlen);
		player_id++;

		for (int j = 0; j < num_players; j++) {
			bzero(buf_s, 1024);
			memcpy(buf_s, &from_vec[j], 1024);
			sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i],
					fromlen);
			// sending team_vec
			bzero(buf_s, 1024);
			team = team_vec[j];
			memcpy(buf_s, &team, 1024);
			sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &from_vec[i],
					fromlen);
		}
	}
	cout << "PLAYER ID: " << player_id << endl;
	cout << "TEAM: " << team_vec[player_id] <<endl;

}

void run_non_host() {
	cout << "================= Non-Host begins ==================" << endl;
	bool team;
	cout << "Select Your Preferred Team: 0 or 1: ";
	cin >> team;
	run_client_udp(host_name);
	bzero(buf_s, 1024);
	memcpy(buf_s, &team, sizeof(bool));
	n = sendto(sock, buf_s, 1024, 0, (struct sockaddr *) &server, length);
	if (n < 0)
		error("Sendto");
	// receiving count_team_a
	bzero(buf_s, 1024);
	recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
	memcpy(&count_team_a, buf_s, sizeof(int));
	// receiving count_team_b
	bzero(buf_s, 1024);
	recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
	memcpy(&count_team_b, buf_s, sizeof(int));
	// receiving num_players
	bzero(buf_s, 1024);
	recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
	memcpy(&num_players, buf_s, sizeof(int));
	// receiving num_total_players
	bzero(buf_s, 1024);
	recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
	memcpy(&num_total_players, buf_s, sizeof(int));
	// receiving player_id
	bzero(buf_s, 1024);
	recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
	memcpy(&player_id, buf_s, sizeof(int));
	cout << "PLAYER ID: " << player_id << endl;

	for (int i = 0; i < num_players; i++) {
		bzero(buf_s, 1024);
		recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
		struct sockaddr_in temp;
		memcpy(&temp, buf_s, sizeof(struct sockaddr_in));
		from_vec.push_back(temp);

		bzero(buf_s, 1024);
		recvfrom(sock, buf_s, 256, 0, (struct sockaddr *) &from, &length);
		memcpy(&team, buf_s, sizeof(bool));
		team_vec.push_back(team);

	}
	from_vec[num_players - 1] = server;
}
