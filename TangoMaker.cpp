#include <iostream>
#include <fstream>
#include <locale>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;

void run();
void printInstructions();
void displayMenu();
void addVocab();
ofstream kanjiWriter;
ofstream pronunciationWriter;
ofstream hiraganaWriter;
ofstream meaningWriter;

int main()
{	
    setlocale(LC_ALL, "");
	kanjiWriter.open("Text/kanji.txt", fstream::app);
	pronunciationWriter.open("Text/pronunciation.txt", fstream::app);
	hiraganaWriter.open("Text/hiragana.txt", fstream::app);
	meaningWriter.open("Text/meaning.txt", fstream::app);
	run();
	kanjiWriter.close();
	pronunciationWriter.close();
	hiraganaWriter.close();
	meaningWriter.close();
}

void run()
{
	printInstructions();
	displayMenu();
}

void printInstructions()
{
	cout << "Welcome to Tango Maker!" << endl << endl;
	cout << "With this tool you can add new vocab words to the main Kanji Game program." << endl;
}

void displayMenu()
{
	int input;
	cout << "1. Add new vocab" << endl;
	cout << "2. Exit" << endl << endl;
	cout << "Type in the number of the option you would like and hit the 'Enter' key." << endl;
	cin >> input;
	while(input != 1 && input != 2)
	{
		cout << "INVALID. Please enter again." << endl;
		cin.clear();
		cin.ignore(80, '\n');
		cin >> input;
	}	
	if(input == 1)
	{
		ifstream fileChecker;
		int length;
		fileChecker.open("Text/kanji.txt", fstream::app);
		fileChecker.seekg(0, ios::end); // put the "cursor" at the end of the file
		length = fileChecker.tellg(); // find the position of the cursor
		fileChecker.close(); // close your file
		if(length != 0)
		{
			kanjiWriter << endl;
			pronunciationWriter << endl;
			hiraganaWriter << endl;
			meaningWriter << endl;
		}	
		addVocab();
	}
}

void addVocab()
{
	char verified;
	string kanji;
	string pronunciation;
	string hiragana;
	string meaning;
	int choice = 2;
	do
	{
		choice = 2;
		cout << "Enter in the vocab (with kanji) that you would like to add and hit 'Enter'" << endl;
		cin >> kanji;
		cout << "Enter in the romaji reading of the kanji you entered and hit 'Enter'" << endl;
		cin >> pronunciation;
		cout << "Enter in the hiragana of the kanji you entered and hit 'Enter'" << endl;
		cin >> hiragana;
		cout << "Enter in the meaning you would like to associate with this vocab." << endl;
		cin.clear();
		cin.sync();
		getline(cin, meaning);
		cout << "Is this alright?" << endl;
		cout << "y/n" << endl;
		cin >> verified;
		while(verified != 'y' && verified != 'Y' && verified != 'N' && verified != 'n')
		{
			cout << "INVALID. Please enter again" << endl;
			cin.clear();
			cin.ignore(80, '\n');
			cin >> verified;
		}
		if(verified == 'y' || verified == 'Y')
		{
			kanjiWriter << kanji;
			pronunciationWriter << pronunciation;
			hiraganaWriter << hiragana;
			meaningWriter << meaning;
			cout << "Your vocab has been added!" << endl;
			cout << "1. Add a new word." << endl;
			cout << "2. Exit" << endl;
			cin >> choice;
			while(choice!= 1 && choice != 2)
			{
				cout << "INVALID. Please enter again" << endl;
				cin.clear();
				cin.ignore(80, '\n');
				cin >> choice;
			}
			if(choice == 1)
			{
				kanjiWriter << endl;
				pronunciationWriter << endl;
				hiraganaWriter << endl;
				meaningWriter << endl;
			}	
		}
		else
		{
			choice = 1;
		}	
	}
	while(choice == 1);
}