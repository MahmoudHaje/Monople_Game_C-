#ifndef SLOT_H
#define SLOT_H

#include <string>
using namespace std;

class Slot {
public:
	Slot();
	~Slot() {};
	virtual string get_name() const = 0;
	virtual bool play(Player* p) = 0;

private:
	int m_slot_num;
};

class Asset : public Slot {
public:
	Asset(string, string, int);
	~Asset() {};
	bool play(Player* p);// buy asset/ pay rent 
	string get_name() const { return m_asset; };  //return asset name
	string get_name_city() const { return m_city; };  //return city name
	int get_buying_price() const { return m_buyPrice; };  //return buying price
	int get_rent_price() const { return m_rentPrice; };	 //return rent price
	void set_if_bought(bool ifBought) { if_bought = ifBought; };  //set bought status
	bool get_if_bought() const { return if_bought; };  //return bought status
	int get_player_number() const { return m_player; };  //get player number
	void set_player_number(int player) { m_player = player; };  //set player number

private:
	string m_city; // city name
	string m_asset; // asset name
	int m_buyPrice; // the price to buy the asset
	int m_rentPrice; // the price to rent the asset
	bool if_bought; // if asset is bought or not
	int m_player;  // serial number of the player

};

class Go : public Slot {
public:
	Go(string go) { m_go = go; };
	~Go() {};
	string get_name() const { return m_go; };  //return guidnace to player
	bool play(Player* p); //do nothing but return 1 to continue game

private:
	string m_go; // "GO!"

};

class Jail : public Slot {
public:
	Jail(string j) { m_jail = j; };
	~Jail() {};
	string get_name() const { return "Jail"; };  //return "Jail" to print on board
	string get_guide() const { return m_jail; };  //return guidnace to player
	bool play(Player* p); //put the player in jail and continue game

private:
	string m_jail; //"" You are in Jail

};

class Chance : public Slot {
public:
	Chance(string c, int num) { m_chance = c; m_num = num; };
	~Chance() {};
	string get_name() const { return "Chance"; };  //return "Chance" to print on board
	string get_guide() const { return m_chance; };  //return guidnace to player
	bool play(Player* p);// give the player a gift, and set the new money balance

private:
	string m_chance; // tell the player that you are in chance slot
	int m_num; // number of money to give the player (can be negetive)

};

#endif