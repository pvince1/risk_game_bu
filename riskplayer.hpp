#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Territory;

#ifndef RISKPLAYER_HPP
#define RISKPLAYER_HPP

class Player
{
public:
	Player(string, int, vector<string>);   // constructors
	Player(string, int);
	void change_troops(signed int);
	void lose_control(string);         // lose a territory
	void gain_control(string);         // take over a territory
	int number_ter_controlled();       // number of territories controlled
	int number_con_controlled();
	static int num_players;            // number of total players
	static string all_players[8];      
	void cavalry();                // troop bonus
	string colors[8] = { "red","green","blue","yellow","purple","orange","white","pink" };
	string name;       // name of the player
	vector<string> ter_controlled;     // territories controlled by the player
	vector<string> con_controlled;
	string color;      // player color
	int troops;        // player's troops
	bool alive;
};

#endif