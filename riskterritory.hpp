#include <iostream>
#include <vector>
#include <string>
#include "riskplayer.hpp"
using namespace std;

class Player;

#ifndef RISKTERRITORY_HPP
#define RISKTERRITORY_HPP

class Territory {
public:
	Territory(string, string, vector<string>); // constructor
	void change_owner(Player&);
	void num_troops(signed int);              
	string color, name, continent, owner;  // members
	signed int troops;
	static int num_territories;
	static vector<string> all_territories;
	vector<string> borders;
};

#endif