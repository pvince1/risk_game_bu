#include "riskterritory.hpp"
#include "riskplayer.hpp"
#include <random>

int Territory::num_territories = 0;     
vector<string> Territory::all_territories;
string colors[8] = { "red","green","blue","yellow","purple","orange","white","pink" };

Territory::Territory(string nym, string cont, vector<string> bounds) {
	continent = cont;
	name = nym;
	borders = bounds;      // constructor implementation
	num_territories++;
	all_territories.push_back(name);
	random_device rd;
	mt19937 random(rd());
	uniform_int_distribution<> dist(0, Player::num_players - 1);   // randomize control
	int owner_id = dist(random);
	owner = Player::all_players[owner_id];         // and number of troops
    color = colors[owner_id];
	uniform_int_distribution<> dist2(1, 10);
	troops = dist2(random);
}

void Territory::change_owner(Player& player) {
	owner = player.name;
	color = player.color;      
}

void Territory::num_troops(signed int remaining_army) {
	troops = remaining_army;
}


// Territory territories[12] = { West_Campus,FitRec,Stuvi,CGS,GSU,CAS,Comm,Warren,Questrom,Bay_State,Kilachand,Bookstore };