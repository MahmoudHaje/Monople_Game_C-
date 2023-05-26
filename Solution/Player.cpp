#include "Board.h"
#include "Slot.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;


Player::Player(string name, Board* board, int balance)
{
	static int index = 1;
	m_serial = index++;
	m_name = name;
	m_board = board;
	m_balance = balance;
	if_jail = false;
	m_place = 1;
	m_assetSize = 0;
}

void Player::update_jail(bool jail)  //set if player in jail or not
{
	if_jail = jail;
}

void Player::set_balance(int balance)  //set the player balance
{
	m_balance = balance;
}

void Player::set_place(int place)  //set player place
{
	m_place = place;
}

void Player::set_name(string name)  //set player name
{
	m_name = name;
}

bool Player::if_in_jail() const  //return if player in jail or not
{
	return if_jail;
}

int Player::get_balance() const  //return the balance a player has
{
	return m_balance;
}

int Player::get_place() const  //return the player place
{
	return m_place;
}

int Player::get_player_serial() const  //return the player serial num in game
{
	return m_serial;
}

bool Player::draw_dice()  //draw the dice
{
	//print player stats
	put_player_stats(get_player_serial(), m_balance, if_jail);
	int y;
	if (if_jail)// if in jail
	{
		cout << "But you are in Jail now, you cant play this turn, must wait to next turn." << endl;
		if_jail = false;
		return true;
	}
	else //not in jail
	{
		cout << "Your place now: " << m_place << endl;
		cout << "Please press 0 to draw your dice" << endl;
		cin >> y;
		while (y != 0)
		{
			cout << "You entered wrong number, please press 0 to draw your dice." << endl;
			cin >> y;
		}
		int x = rand() % 6 + 1; 
		cout << "Your dice draw: " << x << endl;
		if (m_place + x > Slot_num)  //if the player will pass the slot number(in monopoly 18)
		{
			m_place = m_place + x - Slot_num;  //new place will reduced by 18
			m_balance += 350;  //finished round so we add 350 to balance
			cout << "You cross the start line, you won 350, you have these asset: " << endl;
			for (int i = 0; i < m_assetSize;i++)
			{
				cout << m_arr_asset[i]->get_name() << " in ";
				cout << m_arr_asset[i]->get_name_city() << endl;
			}
		}
		else
			m_place = m_place + x;  //normal add if lower than 18
		cout << "Now you are in place number: " << m_place << endl;
		m_board->get_mArray()[m_place - 1]->play(this);
		cout << "You have this amount of money now: " << m_balance << endl;
		
	}

}
void Player::put_player_stats(int player_serial,int balance, bool if_jail) //print stats
{
	int x;
	cout << "Player " << get_player_serial() << ", its your turn now";
	cout << ", you have this amount of money: " << m_balance << endl;
	cout << " If you want to continue the game please press 1, if want to leave please press 0." << endl;
	cin >> x;
	while (x != 0 && x != 1)
	{
		cout << "You entered wrong number, if you want to continue the game please press 1, if want to leave please press 0." << endl;
		cin >> x;
	}
	if (x == 0)
	{
		cout << "GAME OVER, PLAYER " << get_player_serial() << " LOST" << endl;
		cout << "/////////////////////////////" << endl;
		cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
		exit(1);
	}
}

bool Player::add_asset(Asset* a)  // add asset
{
	if (m_balance > (a->get_buying_price()))  //checking if the player balance enough to buy new asset
	{
		m_balance = m_balance - a->get_buying_price();  //updating the balance after buying
		m_assetSize++;  //adding new asset so need to increase the size
		a->set_if_bought(true);  //update the asset as bought
		a->set_player_number(this->get_player_serial());
		m_arr_asset[m_assetSize - 1] = a;

		return true;
	}
	return false;
}

bool Player::pay_rent(int amount)  //pay rent
{
	cout << "You must pay this amount of money: " << amount;
	cout << ", and you have this amount of balance: " << m_balance << endl;
	if (m_balance > amount)  //checking if the player has enough balance to pay rent
	{
		m_balance = m_balance - amount;  //updating the balance after pay rent
		return true;
	}
	return false;
}