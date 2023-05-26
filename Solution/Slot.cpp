#include "Board.h"
#include "Slot.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

Slot::Slot()
{
	m_slot_num = 18;
}

Asset::Asset(string city, string asset, int player)
{
	m_city = city;
	m_asset = asset;
	m_buyPrice = rand() % 100 + 50;
	m_rentPrice = rand() % 45 + 5;
	if_bought = false;
	m_player = player;
}

bool Asset::play(Player* p)// buy asset/ pay rent 
{
	int x;
	if (if_bought && p->get_player_serial() != m_player)  //checking if the asset bought by another player
	{
		cout << "You must pay rent to the other player, cuz you are in his asset " << endl;
		if (p->pay_rent(m_rentPrice)) // you will need to pay
			return true;
		else   // you dont have money to pay rent, game over for you
		{
			cout << "game over, player " << p->get_player_serial() << " lost, he doesnt have enough balance" << endl;
			cout << "/////////////////////////////" << endl;
			cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
			exit(1);
			return false;
		}
	}
	else if (if_bought && p->get_player_serial() == m_player)
	{
		cout << "You are in you asset, you cant buy this, cuz you already own it. " << endl;
	}
	else
	{
		while (1)
		{
			cout << "you have this amount of money " << p->get_balance() << endl;
			cout << "Do you want to buy " << m_asset << " in " << m_city << " ?";
			cout << " it costs " << m_buyPrice << endl;
			cout << " 1-to buy , 2-continue without buying" << endl;
			cin >> x;
			switch (x)
			{
			case 1:
			{
				if (p->add_asset(this))
				{
					cout << "Congrats, now you own the asset " << m_asset << " in " << m_city << endl;
					//cout << "you have this amount of money now after you bought the asset " << p->get_balance() << endl;
					return true;
				}
				else
				{
					cout << "You dont have enough balance, you have just " << p->get_balance() << endl;
					cout << "Game will continue" << endl;
					return true;
				}
				break;
			}
			case 2:
				return true;
				break;
			default:
				cout << "Please choose only 1 or 2" << endl;
			}
		}
	}
}

bool Chance::play(Player* p)// give the player a gift, and set the new money balance
{
	cout << m_chance << endl;
	int new_balance = (p->get_balance()) + m_num;
	p->set_balance(new_balance);
	cout << "You earned this amount of money: " << m_num << endl;
	if (new_balance >= 0)
		return 1;
	cout << "game over, player " << p->get_player_serial() << " lost, doesnt have enough balance" << endl;
	cout << "/////////////////////////////" << endl;
	cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
	exit(1);
	return 0;
}

bool Go::play(Player* p) //do nothing but return 1 to continue game
{
	return 1;
}

bool Jail::play(Player* p)  //put the player in jail and continue game
{
	p->update_jail(true);
	cout << "player " << p->get_player_serial() <<" ";
	cout << m_jail << ", you must wait to the next turn to play" << endl;

	return 1;
}