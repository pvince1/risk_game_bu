#include "riskplayer.hpp"
#include "riskterritory.hpp"

int Player::num_players = 0;
string Player::all_players[8];

Player::Player(string nym, int color_num, vector<string> terr) {
	name = nym;
	ter_controlled = terr;
	color = colors[color_num];
	con_controlled = {};
	troops = 10;
	alive = true;
	Player::all_players[num_players] = name;
	Player::num_players++;
}
Player::Player(string nym, int color_num) {     // constructor implementation
	name = nym;
	color = colors[color_num];
	con_controlled = {};
	troops = 5;
	alive = true;
	Player::all_players[num_players] = name;
	Player::num_players++;
}
void Player::change_troops(signed int dec) {
	troops += dec;
	if (troops < 0) {
		troops = 0;
	}
}

void Player::lose_control(string terr) {
	vector<string>::iterator it = find(ter_controlled.begin(), ter_controlled.end(), terr);
	ter_controlled.erase(it);
}

void Player::gain_control(string terr) {
	ter_controlled.push_back(terr);
}

int Player::number_ter_controlled() {
	return ter_controlled.size();
}

int Player::number_con_controlled() {
	return con_controlled.size();
}

void Player::cavalry() {
	change_troops(ter_controlled.size());
	change_troops(con_controlled.size() * 3);
}