#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;
class Slot;
class Player;

class Board {
private:
	int m_size; // number of slots we have (18)
	Slot** m_arr;
	string m_board_image[6][5];
	int m_slot_width;
	void init_board_image();

public:
	Board(); // constructor
	~Board() {}; // desctructor
	int size() const { return m_size; };
	void play(Player* players); // draw dice and start playing
	void add_chance_slot(string, int); // add chance slot to board
	void add_jail_slot(string); // add jail slot to board
	void add_go_slot(string); // add go slot to board
	void add_asset_slot(string, string); // add asset slot to board
	Slot** get_mArray() { return m_arr; } // return the array of the slot (size 18)
	friend ostream& operator<<(ostream& os, const Board& b);
};

Slot** bigger_arr(int new_size, Slot** old_arr, int old_size);

#endif