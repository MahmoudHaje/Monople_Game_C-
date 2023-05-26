#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;
#define Slot_num 18

class Slot;

class Player {
public:
	Player(string, Board*, int);
	~Player() {};
	bool add_asset(Asset* a);// add the asset to the player Properties
	bool pay_rent(int amount); // pay rent
	bool draw_dice(); // draw dice and move the player to the next position
	void update_jail(bool); // update  if the player in the jail
	void set_balance(int balance); // set new balance
	void set_place(int place); // set new place after draw the dice
	void set_name(string name); // set name
	bool if_in_jail() const; // if the player in jail
	int get_balance() const; // get the amount of money the player have
	int get_place() const; // get the place player is in now
	int get_player_serial() const; // get serial number of the player
	void put_player_stats(int player_serial,int balance, bool if_jail); //print player stats
	Board* get_Board() { return m_board; }

private:
	int m_serial; //serial number
	string m_name; //set player name
	int m_balance; // blance
	bool if_jail; // if in jail
	int m_place; //which place you are
	Board* m_board;
	Asset* m_arr_asset[Slot_num]; // array of the asset
	int m_assetSize; // number of asset you have
};

#endif