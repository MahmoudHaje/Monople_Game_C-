#include "Board.h"
#include "Slot.h"
#include "Player.h"
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

string center(int width, const string& str) {
	int len = str.length();
	if (width < len) { return str; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

void draw_edge_line(int width, const string* line)
{
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|";
	for (int col = 0; col < 5; col++)
		cout << center(width, line[col]) << "|";
	cout << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
}

void draw_inner_line(int width, const string* line, bool last)
{
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	cout << "|" << center(width, line[0]) << "|";
	cout << string(width * 3 + 2, ' ') << "|";
	cout << center(width, line[4]) << "|" << endl;
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	if (!last)
	{
		cout << "|" << string(width, '-') << "|" << string((width * 3 + 3), ' ');
		cout << string(width, '-') << "|" << endl;
	}
}


ostream& operator<<(ostream& os, const Board& b)
{
	draw_edge_line(b.m_slot_width, b.m_board_image[0]);
	for (int row = 1; row < 5; row++)
		draw_inner_line(b.m_slot_width, b.m_board_image[row], row == 4);
	draw_edge_line(b.m_slot_width, b.m_board_image[5]);
	return os;
}

void Board::init_board_image()
{
	m_board_image[0][0] = m_arr[9]->get_name();
	m_board_image[0][1] = m_arr[10]->get_name();
	m_board_image[0][2] = m_arr[11]->get_name();
	m_board_image[0][3] = m_arr[12]->get_name();
	m_board_image[0][4] = m_arr[13]->get_name();
	m_board_image[1][0] = m_arr[8]->get_name();
	m_board_image[1][1] = "";
	m_board_image[1][2] = "";
	m_board_image[1][3] = "";
	m_board_image[1][4] = m_arr[14]->get_name();
	m_board_image[2][0] = m_arr[7]->get_name();
	m_board_image[2][1] = "";
	m_board_image[2][2] = "";
	m_board_image[2][3] = "";
	m_board_image[2][4] = m_arr[15]->get_name();
	m_board_image[3][0] = m_arr[6]->get_name();
	m_board_image[3][1] = "";
	m_board_image[3][2] = "";
	m_board_image[3][3] = "";
	m_board_image[3][4] = m_arr[16]->get_name();
	m_board_image[4][0] = m_arr[5]->get_name();
	m_board_image[4][1] = "";
	m_board_image[4][2] = "";
	m_board_image[4][3] = "";
	m_board_image[4][4] = m_arr[17]->get_name();
	m_board_image[5][0] = m_arr[4]->get_name();//JAIL
	m_board_image[5][1] = m_arr[3]->get_name();//jersueal
	m_board_image[5][2] = m_arr[2]->get_name();//jersueal
	m_board_image[5][3] = m_arr[1]->get_name();// jersueal,m
	m_board_image[5][4] = m_arr[0]->get_name();// go
	m_board_image[5][4] = m_arr[0]->get_name();

	m_slot_width = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
			if (m_board_image[row][col].size() > m_slot_width)
				m_slot_width = m_board_image[row][col].size();
	}
	m_slot_width += 2;
}

Board::Board()
{
	srand(time(NULL));
	m_size = 0;
	m_arr = nullptr;

	add_go_slot("GO!");
	add_asset_slot("Jerusalem", "zoo");
	add_asset_slot("Jerusalem", "David_tower");
	add_asset_slot("Jerusalem", "Western_wall");
	add_jail_slot("JAIL! Wait 1 turn");

	add_asset_slot("Tel_Aviv", "Hilton");
	int num = rand() % 1000 + 500;
	add_chance_slot("You won the lottery", num);
	add_asset_slot("Tel_Aviv", "Azrieli");
	add_asset_slot("Tel_Aviv", "Habima");
	num = rand() % 200 + 100;
	add_chance_slot("You have to pay the IRS", -num);

	add_asset_slot("Carmiel", "Rocks_park");
	num = rand() % 70 + 30;
	add_chance_slot("Congratulations to your birthday, get a bouquet", num);
	add_asset_slot("Carmiel", "Big");
	add_asset_slot("Carmiel", "Ort_Braude");

	add_asset_slot("Eilat", "Dolpin_reef");
	add_asset_slot("Eilat", "Kings_town");
	add_asset_slot("Eilat", "Ramon_airport");
	add_asset_slot("Eilat", "Almog_beach");
	init_board_image();
}

void Board::play(Player* players)
{
	int x;
	
	players[0].draw_dice();
	cout << "Press 0 to end your turn " << endl;
	cin >> x;
	while (x != 0)
	{
		cout << "You entered wrong number, please enter 0 to end your turn." << endl;
		cin >> x;
	}
	cout << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;

	players[1].draw_dice();
	cout << "Press 0 to end your turn " << endl;
	cin >> x;
	while (x != 0)
	{
		cout << "You entered wrong number, please enter 0 to end your turn." << endl;
		cin >> x;
	}
	cout << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "///////////////////////////////////////////////////////////////////////////////////" << endl;


}

void Board::add_asset_slot(string city, string asset)
{
	m_size++;
	m_arr = bigger_arr(m_size, m_arr, m_size - 1);
	m_arr[m_size - 1] = new Asset(city, asset, 2);
}

void Board::add_chance_slot(string chance_text, int num)
{
	m_size++;
	m_arr = bigger_arr(m_size, m_arr, m_size - 1);
	m_arr[m_size - 1] = new Chance(chance_text, num);
}

void Board::add_jail_slot(string jail_text)
{
	m_size++;
	m_arr = bigger_arr(m_size, m_arr, m_size - 1);
	m_arr[m_size - 1] = new Jail(jail_text);
}

void Board::add_go_slot(string go_text)
{
	m_size++;
	m_arr = bigger_arr(m_size, m_arr, m_size - 1);
	m_arr[m_size - 1] = new Go(go_text);
}

Slot** bigger_arr(int new_size, Slot** old_arr, int old_size)
{
	Slot** new_arr = new Slot * [new_size];
	for (int i = 0; i < old_size; i++)
	{
		new_arr[i] = old_arr[i];  //copying the old array to the new array
	}
	delete[] old_arr;  //deleting old array because we're done from using it

	return new_arr;
}