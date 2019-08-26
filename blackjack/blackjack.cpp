// blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This program will read from a file named 'data.txt' and play blackjack for you

#include "pch.h"
#include <iostream>
#include <fstream>
#define in_file "data.txt"
#define out_file "results.txt"
using namespace std;
void input(char[],int,ifstream&);
int value_of_card(char);
int calculation(char[], int);
int main()
{
	ifstream ins;
	ofstream outs;
	ins.open(in_file);
	outs.open(out_file);
	char card_values[5];
	char option;
	int number_of_cards;
	int score;

	while (1)
	{

		ins >> number_of_cards;
		if (number_of_cards == -99)
		{
			outs << "Finished!";
			break;
		}
		input(card_values, number_of_cards, ins);
		score = calculation(card_values, number_of_cards);
		if (score >= 50)
			outs << "wrong input data" << endl;
		if (score == 21)
			outs << "Blackjack 21!" << endl;
		if (score > 21 && score < 50)
			outs << "busted" << endl;
		else if (score <= 21)
			outs << "Score is: " << score << endl;
	}
	ins.close();
	outs.close();
}
void input(char card_values[], int number_of_cards, ifstream &ins)
{
	for (int i = 0; i < number_of_cards; i++) ins >> card_values[i];
}
int value_of_card(char card_value)
{
	if (card_value >= '2'&&card_value <= '9') 
		return (card_value - '0');
	if (card_value == 't' || card_value == 'j' || card_value == 'q' || card_value == 'k')//assigns face cards to the value of 10
		return 10;
	if (card_value == 'a')
		return 1;
	else if (!(card_value >= '2' && card_value <= '9') && (card_value == 't' || card_value == 'j' || card_value == 'q' || card_value == 'k') && (card_value == 'a'))
	{
		return 99; //error checking for values that have nothing assigned
	}
}
int calculation(char card_value[], int number_of_cards)
{
	int value;
	int sum = 0;
	int ace_count = 0;
	for (int i = 0; i < number_of_cards; i++)
	{
		value = value_of_card(card_value[i]);
		if (value == 1) //if there is an ace card
			ace_count++;
		sum += value;
	}
	while (ace_count && sum + 10 <= 21) //value will not go over 21 if there is an ace
	{
		sum += 10;
		ace_count--;
	}
	return sum;
}
