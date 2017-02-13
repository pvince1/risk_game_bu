#include <iostream>
#include <algorithm>
#include <random>
#include "riskplayer.hpp"
#include "riskterritory.hpp"
#include <string>
#include <array>
using namespace std;


Player Dan("Daniel", 0);
Player Cole("Cole", 1);             // initialize everything
Player Powell("Powell", 2);
Player players[3] = { Dan,Cole,Powell };
Territory West_Campus("West_Campus", "West", { "FitRec", "Stuvi","CGS" });
Territory FitRec("FitRec", "West", { "West_Campus", "Stuvi","CGS" });
Territory Stuvi("Stuvi", "West", { "FitRec", "West_Campus","CGS","GSU" });
Territory CGS("CGS", "West", { "FitRec", "Stuvi","West_Campus","Warren" });
Territory GSU("GSU", "Central", { "CAS","Comm","Warren","Stuvi" });
Territory CAS("CAS", "Central", { "GSU","Comm","Warren","Bay_State" });
Territory Comm("Comm", "Central", { "CAS","GSU","Warren","Questrom" });
Territory Warren("Warren", "Central", { "CAS","GSU","Comm","CGS" });
Territory Questrom("Questrom", "East", { "Bay_State","Kilachand", "Bookstore","Comm" });
Territory Bay_State("Bay_State", "East", { "Questrom","Kilachand", "Bookstore","CAS" });
Territory Kilachand("Kilachand", "East", { "Questrom","Bay_State", "Bookstore" });
Territory Bookstore("Bookstore", "East", { "Questrom","Bay_State","Kilachand" });
Territory territories[12] = { West_Campus,FitRec,Stuvi,CGS,GSU,CAS,Comm,Warren,Questrom,Bay_State,Kilachand,Bookstore };


bool is_dominated(Territory territories[12]) {

	string dom_name = territories[0].owner;
	string check_name;
	int terrs_checked = 0;

	for (int i = 1; i < 12; i++) {
		check_name = territories[i].owner;        // check for a game win
		if (check_name == dom_name) {
			terrs_checked++;
		}
		else {
			return false;
		}
	}

	if (terrs_checked == 11) {
		return true;
	}

	return false;
}
bool attackable(Territory& attacking, Territory& defending) {
	if (attacking.owner == defending.owner) {
		return false;
	}
	vector<string> borders = attacking.borders;
	for (unsigned int i = 0; i<borders.size(); i++) {      // check if the territory
		if (defending.name == borders[i]) {                   // can be attacked
			return true; //borders
		}
	}
	return false; // doesn't border
}
void bonus_troops(Player& player) {	//gives troop bonus for owning continents
	int west_count = 0; 
	int central_count = 0; 
	int east_count = 0;    
	for (auto ter : player.ter_controlled) {
		for (int j = 0; j < 12; j++) {
			if (ter == territories[j].name) {
				if (territories[j].continent == "West") {       // give troops for campus control
					west_count++;
				}
				if (territories[j].continent == "Central") {
					central_count++;
				}
				if (territories[j].continent == "East") {
					east_count++;
				}
			}
		}
	}
	if (west_count == 4) {
		player.troops += 3;
		cout << player.name << " controls West Campus!" << endl;
	}
	if (east_count == 4) {
		player.troops += 3;
		cout << player.name << " controls East Campus!" << endl;
	}
	if (central_count == 4) {
		player.troops += 3;
		cout << player.name << " controls Central Campus!" << endl;
	}
}
void allocate_troops(Player& player) {
	cout << player.name << "'s Troop Allocation" << endl;
	cout << "Select a territory to allocate troops to:" << endl;
	int counter = 0;
	int allocate_to;
	for (int p = 0; p < 12; p++) {
		for (auto ter : player.ter_controlled) {
			if (ter == territories[p].name)
				cout << counter << ".) " << ter << endl;    
		}
		counter++;                // sets a player's troops on the chosen territory
	}
	cin >> allocate_to;
	if (allocate_to > 11) {
		cout << "Please enter a number between 0 and 11" << endl;
	}
	else {
		territories[allocate_to].troops += player.troops;
		cout << "Allocated " << player.troops << " troops to " << territories[allocate_to].name << endl;
		player.troops = 0;
	}
}
void print_gameboard(Territory territories[12]) {
	for (int i = 0; i < 12; i++) {
		cout << territories[i].name << ": " << territories[i].owner << " " << territories[i].troops << endl;
	}                                      // print out the gameboard
}

void attack(Territory& attacking, Territory& defending) {
	cout << endl;
	if (attackable(attacking,defending)==false) {
		cout << "Invalid attack" << endl;
	}
	else {
		cout << attacking.name << " --> " << defending.name << endl;
		int attacker[3];
		int defender[2];
		bool keep_attacking = true;
		char answer;
		string winner, loser;
		while (keep_attacking == true) {      // the attack function (explained in Risk.md)
			random_device rd;
			mt19937 dice(rd());
			uniform_int_distribution<> dis(1, 6);
			for (int i = 0; i < 2; i++) {
				attacker[i] = dis(dice);
				defender[i] = dis(dice);
			}
			attacker[2] = dis(dice);
			sort(attacker, attacker + 3);
			sort(defender, defender + 2);
			cout << attacking.owner << " rolled:";
			for (int i = 3; i > 0; i--) {
				cout << " " << attacker[i - 1];
			}
			cout << endl;
			cout << defending.owner << " rolled:";
			for (int i = 2; i > 0; i--) {
				cout << " " << defender[i - 1];
			}
			cout << endl;
			cout << endl;
			if (attacker[2] > defender[1])
				--defending.troops;
			else
				--attacking.troops;
			if (attacker[1] > defender[0] && attacking.troops > 1 && defending.troops > 0)
				--defending.troops;
			else if (attacking.troops > 1 && defending.troops > 0)
				--attacking.troops;
			cout << attacking.owner << " has " << attacking.troops << " troops left." << endl;
			cout << defending.owner << " has " << defending.troops << " troops left." << endl;
			if (attacking.troops < 2 || defending.troops < 1) {
				keep_attacking = false;
				break;
			}
			cout << "Continue Attacking? Y/N" << endl;
			cin >> answer;
			if (answer == 'y' || answer == 'Y') {
				keep_attacking = true;
			}
			else
				keep_attacking = false;
		}
		if (defending.troops == 0) {
			defending.troops = attacking.troops - 1;
			attacking.troops = 1;
			for (int i = 0; i < 3; i++) {	
				if (defending.owner == players[i].name) { 
					players[i].lose_control(defending.name); //first remove territory from defender's control
					for (int j = 0; j < 3; j++){
						if (attacking.owner == players[j].name) {
							players[j].gain_control(defending.name);  //then give it to the attacker
							defending.change_owner(players[j]);			//and change the owner of the territory object
							break;
						}
					}
				}
				cout << endl;
				
			}
			cout << attacking.owner << " has taken over "<<defending.name<<"!" << endl;
			cout << endl;
		}
		else if (defending.troops > attacking.troops) {
			attacking.troops = 1;
			cout << defending.owner << " has defended successfully!" << endl;
			cout << endl;
		}
	}
}
void attack_setup(Player& player) {
		cout << player.name << "'s Attack" << endl;
		cout << "Select a territory to attack from:" << endl;
		int counter = 0;
		int attack_from;
		for (int p = 0; p < 12; p++) {
			for (auto ter : player.ter_controlled) {
				if (ter == territories[p].name)
					cout << counter << ".) " << ter << endl;   // choose attack to and from
			}                                                    // territories
			counter++;
		}
		cin >> attack_from;
		if (attack_from > 11) {
			cout << "Please enter a number between 0 and 11" << endl;
		}
		cout << "What would you like to attack?" << endl;
		int count = 0;
		signed int attack_to;
		for (int p = 0; p < 12; p++) {
			for (auto ter: territories[attack_from].borders) { //these are all the borders
				if(ter == territories[p].name)
					if(attackable(territories[attack_from],territories[p]))
						cout << count << ".) " << ter << endl;
			}
			count++;
		}
		cin >> attack_to;
		if (attack_to > 11) {
			cout << "Please enter a number between 0 and 11" << endl;
		}
		else {
			attack(territories[attack_from], territories[attack_to]);
		}
}

int main() {
	for (int i = 0; i < 12;i++) {	//assigns initial territories to player class
		for (int j = 0; j < 3; j++) {
			if (territories[i].owner == players[j].name) { 
				players[j].gain_control(territories[i].name); 
			}
		}
	}
	print_gameboard(territories);
	cout << endl;
	bool dominated = false;
	int turn = 0;
	bool more_attacks = true;
	while (dominated == false) {
		for (int i = 0; i < 3; i++) {
			if (is_dominated(territories)) {
			cout << territories[0].owner << " has taken over Boston University!"<<endl;
			dominated = true;
			break;
			}
			cout <<players[i].name<< "'s Turn" << endl;
			more_attacks = true;
			if (players[i].number_ter_controlled() != 0) {       // the main game loop
				players[i].cavalry();					  
				bonus_troops(players[i]);
				allocate_troops(players[i]);
				while (more_attacks) {
					attack_setup(players[i]);
					cout << "Keep attacking? Y/N" << endl;
					char y_n;
					cin >> y_n;
					if (y_n == 'y' || y_n == 'Y') {
						more_attacks = true;
					}
					else {
						more_attacks = false;
					}
					turn++;
				}
			}
		}

	}
	return 0;
}