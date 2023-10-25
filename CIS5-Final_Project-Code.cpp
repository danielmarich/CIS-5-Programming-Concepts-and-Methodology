// CIS-5 Final Project
// Spring 2016
// May 31, 2016
// Hero Slayer
// Created by Myles Janik, Ivan Hernandez, Zachary Brown, and Daniel Marich

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <time.h>

using namespace std;

// global variables go here
int startChoice;
int firstAttack;
string heroName;
int heroHp;
int heroAtk;
string playerName = "";
string playerRace = "";
int healthPoints = 0;
int attackPower = 0;
int specialAttack = 0;
int playerLevel = 0;
int playerXP = 0;
int menuChoice;
int maxHealth;
int randHeroDamage;
int heroSpecialAtk;
ofstream outputFile;
// structs go here


//function prototypes go here
void displayTitleScreen();
void displayIntro();
int introMenu();
bool isIntroChoiceValid(int num);
bool gameExists();

int startGame(int choice);
int newGame();
bool isRaceChoiceValid(string sNum);
void createChar(string pChoice, string &raceChoice, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP);
string raceMenu();
void loadSave(string &playerRace, string &playerName, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP);
void levelUp(string &playerRace, string &playerName, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP);
void beginStory(string playerName, string playerRace, int playerXP, int playerLevel);

// combat functions prototypes
void getAiChoice(int &heroSpecialAtk, int &heroAtk, int &heroHp, string &name);
void afterBattleMessage(int &playerHp, int heroHp, string heroName);
int beforeBattle(string name);
int combatMenu(int playerAtk, int specialAttack);
bool isBattleChoiceValid(int numChoice);
void playerAttackFirst(int heroSpecialAtk, int &heroHp, int heroAtk, int &playerHp, int playerChoice, int playerAtk, int specialAttack, string name);
void heroAttackFirst(int playerHp, int &heroHp, int playerChoice, int playerAtk, int specialAttack, string name);
bool runAway(int menuChoice);
void runAwayMessage();


int main()
{
	bool isMenuChoice;
	int tempXp;

	displayTitleScreen();

	system("pause");

	system("CLS");

	displayIntro();
	startChoice = introMenu();
	while (!isIntroChoiceValid(startChoice))
	{
		cout << "Invalid entry.  Please choose the number 1, 2 or 0." << endl;
		startChoice = introMenu();
	}
	startGame(startChoice);
	loadSave(playerRace, playerName, healthPoints, attackPower, specialAttack, playerLevel, playerXP);
	beginStory(playerName, playerRace, playerXP, playerLevel);
	// Combat Code Begins
	do
	{
		system("pause");

		system("CLS");
		maxHealth = healthPoints;
		getAiChoice(heroSpecialAtk, heroAtk, heroHp, heroName);


		cout << "==============================================================" << endl;
		cout << "A " << heroName << " appears! Prepare for battle!" << endl;
		cout << "==============================================================" << endl;
		cout << "The hero's attack is: " << heroAtk << endl 
			 << "The hero's special attack is: " << heroSpecialAtk << endl
			 << "The hero's health is:  " << heroHp << endl;
		cout << "---------------------------------" << endl;

		tempXp = playerXP;

		while (heroHp > 0 && healthPoints > 0)
		{
			firstAttack = beforeBattle(heroName);

			if (firstAttack == 0)
			{
				menuChoice = combatMenu(attackPower, specialAttack);

				isMenuChoice = runAway(menuChoice);

				if (isMenuChoice == false)
				{
					playerAttackFirst(heroSpecialAtk, heroHp, heroAtk, healthPoints, menuChoice, attackPower, specialAttack, heroName);

					afterBattleMessage(healthPoints, heroHp, heroName);
				}

				else if (isMenuChoice == true)
				{
					heroHp = 0;

					runAwayMessage();
				}
			}

			else if (firstAttack == 1)
			{
				srand(time(0));
				
				int randChoice = rand() % 4;
				int randAttack = rand() % 2;

				if (randAttack == 1)
				{

					cout << "The hero decides to attack you with their basic attack!" << endl;

					// This is the random chance of hitting basic attack for the hero
					if (randChoice == 0 || randChoice == 1 || randChoice == 2)
					{
						healthPoints = healthPoints - heroAtk;

						cout << "The " << heroName << " hits you for " << heroAtk << " damage!" << endl;
					}
					else if (randChoice == 3)
					{
						cout << "The " << heroName << " missed it's attack!" << endl;
						cout << "================================================" << endl;
					}
				}
				else if (randAttack == 0)
				{
					cout << "The hero decides to attack you with their basic attack!" << endl;

					// This is the random chance of hitting special attack for the hero
					if (randChoice == 0 || randChoice == 1)
					{
						healthPoints = healthPoints - heroSpecialAtk;

						cout << "The " << heroName << " hits you for " << heroSpecialAtk << " damage!" << endl;
					}
					else if (randChoice == 3 || randChoice == 2)
					{
						randHeroDamage = 0;

						cout << "The " << heroName << " missed it's attack!" << endl;
						cout << "================================================" << endl;
					}
				}
				//-----------------------------------------
				//-----------------------------------------
				//-----------------------------------------

				afterBattleMessage(healthPoints, heroHp, heroName);


				if (healthPoints > 0)
				{
					menuChoice = combatMenu(attackPower, specialAttack);

					isMenuChoice = runAway(menuChoice);

					if (isMenuChoice == false)
					{
						heroAttackFirst(healthPoints, heroHp, menuChoice, attackPower, specialAttack, heroName);

						afterBattleMessage(healthPoints, heroHp, heroName);
					}

					else if (isMenuChoice == true)
					{
						heroHp = 0;
						healthPoints = 0;
						runAwayMessage();
					}
				}

			}


		}

		healthPoints = maxHealth;
		outputFile.open("PlayerData.txt"); // Save File Path
		outputFile << playerName << endl;
		outputFile << playerRace << endl;
		outputFile << healthPoints << endl;
		outputFile << attackPower << endl;
		outputFile << specialAttack << endl;
		outputFile << playerLevel << endl;
		outputFile << playerXP << endl;
		outputFile.close();
		loadSave(playerRace, playerName, healthPoints, attackPower, specialAttack, playerLevel, playerXP);
	} while (healthPoints > 0);

	cout << endl;

	return 0;
}

// Program functions go here
void displayTitleScreen()
{
	cout << endl << endl << endl << endl << endl;

	cout << "		 " << " __  __     ______     ______     ______     " << endl;
	cout << "		 " << "/\\ \\_\\ \\   /\\  ___\\   /\\  == \\   /\\  __ \\    " << endl;
	cout << "		 " << "\\ \\  __ \\  \\ \\  __\\   \\ \\  __<   \\ \\ \\/\\ \\   " << endl;
	cout << "		 " << " \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  " << endl;
	cout << "		 " << "  \\/_/\\/_/   \\/_____/   \\/_/ /_/   \\/_____/  " << endl << endl << endl;

	cout << "      " << "   ______     __         ______     __  __     ______     ______    " << endl;
	cout << "      " << "  /\\  ___\\   /\\ \\       /\\  __ \\   /\\ \\_\\ \\   /\\  ___\\   /\\  == \\   " << endl;
	cout << "      " << "  \\ \\___  \\  \\ \\ \\____  \\ \\  __ \\  \\ \\____ \\  \\ \\  __\\   \\ \\  __<   " << endl;
	cout << "      " << "   \\/\\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\/\\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\ " << endl;
	cout << "      " << "    \\/_____/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_/ /_/ " << endl;

	cout << endl << endl << endl << endl << endl << endl << endl;

}
void displayIntro()
{
	cout << "------------------------------------------------" << endl;
	cout << "|          WELCOME TO HERO SLAYER!             |" << endl;
	cout << "|          -----------------------             |" << endl;
	cout << "|     Where you can put those unrealistic,     |" << endl;
	cout << "|  goody-two shoes characters in their place!  |" << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
}

int introMenu()
{
	cout << "------------------------------------------------" << endl;
	cout << "|                HERO SLAYER                   |" << endl;
	cout << "|          -----------------------             |" << endl;
	cout << "|                Start Menu                    |" << endl;
	cout << "| Select 1 to start a new game.                |" << endl;
	if (gameExists())
	{
		cout << "| Select 2 to continue your most recent game.  |" << endl;
	}

	cout << "| Select 0 to exit the game.                   |" << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
	cout << "Please make your selection: ";
	cin >> startChoice;

	return startChoice;
}

void beginStory(string playerName, string playerRace, int playerXP, int playerLevel)
{
	if (playerXP > 0 || playerLevel > 0)
	{
		cout << endl;
		cout << "The " << playerName << "'s journey for \n";
		cout << "world domination continues!\n";
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << "------------------------------------------------" << endl;
		cout << "|               The Story Begins                |" << endl;
		cout << "|          -----------------------              |" << endl;
		cout << " The " << playerRace << ", " << playerName << setw(30) << endl;
		cout << " enters a forest that is on the outskirts      " << endl;
		cout << " of a nearby kingdom.                          " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	}
}

bool isIntroChoiceValid(int num)
{
	if (num == 1 || num == 0 || num == 2)
		return true;
	else
		return false;
}

int startGame(int choice)
{
	if (startChoice == 1)
	{
		cout << endl;
		cout << "Start New Game!" << endl;
		newGame();
		return 1;
	}
	else if (startChoice == 2)
	{
		cout << endl;
		cout << "Continue Recent Game!" << endl;

		return 2;
	}
	else if (startChoice == 0)
	{
		cout << endl;
		cout << "You don't know what you're missing!" << endl;
		cout << "End Game." << endl;

		exit(0);
		return 0;
	}
	else
	{
		cout << "Invalid input!" << endl;
		return 0;
	}
}


//*******************************************
// function newGame, by Zachary
//-------------------------------------------
// This module is booted up when the player
// selects "New Game" on the main menu. It
// prompts the user to select a class & name.
// Info is saved in a .txt file
//*******************************************

int newGame()
{
	string raceChoice,
		playerName,
		playerRace;

	int healthPoints,
		attackPower,
		specialAttack,
		playerLevel,
		playerXP;

	ofstream outputFile;

	cout << "------------------------------------------------" << endl;
	cout << "|             What is thy name?                |" << endl;
	cout << "|          -----------------------             |" << endl;
	cin.ignore();
	cout << "            ";
	getline(cin, playerName);
	cout << "------------------------------------------------" << endl;
	cout << endl;
	cout << "Please make your selection: " << endl;

	raceChoice = raceMenu();
	while (!isRaceChoiceValid(raceChoice))
	{
		cout << "Invalid entry.  Please choose the number 1, 2 or 0." << endl;
		raceChoice = raceMenu();
	}

	createChar(raceChoice, playerRace, healthPoints, attackPower, specialAttack, playerLevel, playerXP);

	outputFile.open("PlayerData.txt"); // Save File Path
	outputFile << playerName << endl;
	outputFile << playerRace << endl;
	outputFile << healthPoints << endl;
	outputFile << attackPower << endl;
	outputFile << specialAttack << endl;
	outputFile << playerLevel << endl;
	outputFile << playerXP << endl;
	outputFile.close();

	cout << endl;

	return 0;
}


//*******************************************
// function raceMenu, by Zachary
//-------------------------------------------
// Player select race here. Input returned to
// the 'newGame' function
//*******************************************

string raceMenu()
{
	string raceChoice;

	cout << "------------------------------------------------" << endl;
	cout << "|              SELECT A MONSTER                |" << endl;
	cout << "|          -----------------------             |" << endl;
	cout << "|            What beast art thou?              |" << endl;
	cout << "| Select 1 to play as an Orc                   |" << endl;
	cout << "| Select 2 to play as a Goblin                 |" << endl;
	cout << "| Select 3 to play as a Giant                  |" << endl;
	cout << "| Select 0 to go back to main menu.            |" << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;
	cout << "Please make your selection: ";
	cin >> raceChoice;

	return raceChoice;
}


//*******************************************
// function isRaceChoiceValid, by Zachary
//*******************************************

bool isRaceChoiceValid(string sNum)
{
	if (sNum == "1" || sNum == "2" || sNum == "3" || sNum == "0")
		return true;
	else
		return false;
}


//*******************************************
// function reviewRace, by Zachary
//-------------------------------------------
// Confirms to the player their race choice
//*******************************************

void createChar(string pChoice, string &raceChoice, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP)
{
	if (pChoice == "1")
	{
		cout << endl;
		raceChoice = "Orc";
		healthPoints = 15;
		attackPower = 4;
		specialAttack = 6;
		playerLevel = 1;
		playerXP = 0;
	}
	else if (pChoice == "2")
	{
		cout << endl;
		raceChoice = "Goblin";
		healthPoints = 10;
		attackPower = 5;
		specialAttack = 10;
		playerLevel = 1;
		playerXP = 0;
	}
	else if (pChoice == "3")
	{
		cout << endl;
		raceChoice = "Giant";
		healthPoints = 100;
		attackPower = 50;
		specialAttack = 100;
		playerLevel = 1;
		playerXP = 0;
	}
	else if (pChoice == "0")
	{
		cout << endl;
		cout << "Returning to main menu." << endl;
	}
	else
	{
		cout << "Invalid input!" << endl;
	}
}


//*******************************************
// function loadSave, by Zachary updated by Myles and Daniel
//-------------------------------------------
// loads save data from .txt file
//*******************************************

void loadSave(string &playerRace, string &playerName, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP)
{
	ifstream inputFile;

	inputFile.open("PlayerData.txt"); // replace "zachary" with your name
	getline(inputFile, playerName);
	inputFile >> playerRace;
	inputFile >> healthPoints;
	inputFile >> attackPower;
	inputFile >> specialAttack;
	inputFile >> playerLevel;
	inputFile >> playerXP;
	inputFile.close();

	cout << "------------------------------------------------" << endl;
	cout << "|                PLAYER DATA                   |" << endl;
	cout << "|          -----------------------             |" << endl;
	cout << "Thy name is " << playerName << endl;
	cout << "Thou art a " << playerRace << endl;
	cout << "Thy health is " << healthPoints << endl;
	cout << "Thy attack power is " << attackPower << endl;
	cout << "Thy special attack power is " << specialAttack << endl;
	cout << "Thy level is " << playerLevel << endl;
	cout << "Thy XP be " << playerXP << endl;
	cout << "------------------------------------------------" << endl;

}

// Combat Funtions Being *************************************************************************************
int combatMenu(int playerAtk, int specialAttack)
{
	srand(time(0));

	int battleChoice;
	int menuChoice;
	int randChance = rand() % 4;

	cout << "-------------------------------------------------" << endl;
	cout << "                 Combat Menu" << endl;
	cout << "   1.Basic Attack '" << playerAtk << " damage'" << endl;
	cout << "   2.Special Attack '" << specialAttack << " damage'" << endl;
	cout << "   3.Run away" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Enter combat choice: ";
	cin >> battleChoice;

	while (!isBattleChoiceValid(battleChoice))
	{
		cout << "Invalid entry.  Please choose the number 1, 2, or 3" << endl;
		cin >> battleChoice;
	}

	if (battleChoice == 1)
	{
		if (randChance == 3)
		{
			cout << "================================" << endl;
			cout << "OH NO!!! You missed your attack!" << endl;
			cout << "================================" << endl;

			menuChoice = 7;
		}
		else if (randChance == 1 || randChance == 2 || randChance == 0)
		{
			menuChoice = 1;
		}
	}

	else if (battleChoice == 2)
	{
		if (randChance == 0 || randChance == 1)
		{
			cout << "================================" << endl;
			cout << "OH NO!!! You missed your attack!" << endl;
			cout << "================================" << endl;

			menuChoice = 7;
		}
		else if (randChance == 2 || randChance == 3)
		{
			menuChoice = 2;
		}
	}

	else if (battleChoice == 3)
	{
		menuChoice = 3;
	}

	return menuChoice;
}

bool isBattleChoiceValid(int numChoice)
{
	if (numChoice == 1 || numChoice == 2 || numChoice == 3)
		return true;
	else
		return false;
}

// This function returns the AI's attack, health, and name and it also does the math for hitting the player
void getAiChoice(int &heroSpecialAtk, int &heroAtk, int &heroHp, string &name)
{
	srand(time(0));

	int typeHero = rand() % 3;

	if (typeHero == 0)
	{
		// Wandering Traveller hero
		heroAtk = 3;
		heroSpecialAtk = 5;
		heroHp = 10;
		name = "Wandering Traveller";
	}
	else if (typeHero == 1)
	{
		// Swordsman hero
		heroAtk = 44;
		heroSpecialAtk = 46;
		heroHp = 43;
		name = "Swordsman";
	}
	else if (typeHero == 2)
	{
		// Blacksmith hero
		heroAtk = 2;
		heroSpecialAtk = 4;
		heroHp = 2;
		name = "Blacksmith";
	}
}

int beforeBattle(string name)
{
	int firstAttack = rand() % 2;

	if (firstAttack == 0)
	{
		cout << "You get to attack first!" << endl;
	}

	else if (firstAttack == 1)
	{
		cout << "The " << name << " attacks you first!" << endl;
	}

	return firstAttack;
}

void afterBattleMessage(int &playerHp, int heroHp, string heroName)
{
	ofstream outputFile;

	if (playerHp > 0 && heroHp > 0)
	{
		cout << "Your health is at " << playerHp << endl;
		cout << "The " << heroName << "'s health is at " << heroHp << endl;
	}
	else if (heroHp <= 0)
	{
		playerHp = maxHealth;

		cout << "You've beaten the " << heroName << ", CONGRATULATIONS!" << endl;
		cout << "You have earned 10 experience points!" << endl;
		cout << "And you've been healed completely!" << endl;
		cout << endl;

		playerXP = playerXP + 10;
			
		levelUp(playerRace, playerName, healthPoints, attackPower, specialAttack, playerLevel, playerXP);
		
		outputFile.open("PlayerData.txt"); // Save File Path
		
		outputFile << playerName << endl;
		outputFile << playerRace << endl;
		outputFile << healthPoints << endl;
		outputFile << attackPower << endl;
		outputFile << specialAttack << endl;
		outputFile << playerLevel << endl;
		outputFile << playerXP << endl;
		outputFile.close();
		system("pause");

		system("CLS");


	}
	else if (playerHp <= 0)
	{
		cout << "********************************************" << endl;
		cout << "You lost the battle, and now lose 10 XP" << endl
			<< "Try again, if you think you're brave enough." << endl;
		cout << "********************************************" << endl;

		playerXP = playerXP - 10;
		outputFile.open("PlayerData.txt"); // Save File Path

		outputFile << playerName << endl;
		outputFile << playerRace << endl;
		outputFile << healthPoints << endl;
		outputFile << attackPower << endl;
		outputFile << specialAttack << endl;
		outputFile << playerLevel << endl;
		outputFile << playerXP << endl;
		outputFile.close();
		system("pause");

		system("CLS");

	}

}

void playerAttackFirst(int heroSpecialAtk, int &heroHp, int heroAtk, int &playerHp, int playerChoice, int playerAtk, int specialAttack, string name)
{
	srand(time(0));

	int attackStrength;
	int randChoice = rand() % 4;
	int randAttack = rand() % 2;

	if (playerChoice == 1 || playerChoice == 2)
	{
		if (playerChoice == 1)
		{
			attackStrength = playerAtk;
		}
		else if (playerChoice == 2)
		{
			attackStrength = specialAttack;
		}

		heroHp = heroHp - attackStrength;

		if (heroHp > 0)
		{

			cout << "==========================================" << endl;
			cout << "You hit the " << name << " for " << attackStrength << " damage!" << endl;
			cout << "==========================================" << endl;

			if (randAttack == 1)
			{
				cout << "The hero decides to attack you with their basic attack!" << endl;

				// This is the random chance of hitting basic attack for the hero
				if (randChoice == 0 || randChoice == 1 || randChoice == 2)
				{
					playerHp = playerHp - heroAtk;

					cout << "The " << heroName << " hits you for " << heroAtk << " damage!" << endl;
				}
				else if (randChoice == 3)
				{
					randHeroDamage = 0;

					cout << "The " << heroName << " missed it's attack!" << endl;
					cout << "================================================" << endl;
				}
			}
			else if (randAttack == 0)
			{
				cout << "The hero decides to attack you with their special attack!" << endl;

				// This is the random chance of hitting special attack for the hero
				if (randChoice == 0 || randChoice == 1)
				{
					playerHp = playerHp - heroSpecialAtk;

					cout << "The " << heroName << " hits you for " << heroSpecialAtk << " damage!" << endl;
				}
				else if (randChoice == 3 || randChoice == 2)
				{
					cout << "The " << heroName << " missed it's attack!" << endl;
					cout << "================================================" << endl;
				}
			}
		}

		else if (heroHp <= 0)
		{
			cout << "==========================================" << endl;
			cout << "You hit the " << name << " for " << attackStrength << " damage!" << endl;
			cout << "==========================================" << endl;
		}
	}
	else if (playerChoice == 7)
	{
		if (randAttack == 1)
		{
			cout << "The hero decides to attack you with their basic attack!" << endl;

			// This is the random chance of hitting basic attack for the hero
			if (randChoice == 0 || randChoice == 1 || randChoice == 2)
			{
				playerHp = playerHp - heroAtk;

				cout << "The " << heroName << " hits you for " << heroAtk << " damage!" << endl;
			}
			else if (randChoice == 3)
			{
				cout << "The " << heroName << " missed it's attack!" << endl;
				cout << "================================================" << endl;
			}
		}
		else if (randAttack == 0)
		{
			cout << "The hero decides to attack you with their special attack!" << endl;

			// This is the random chance of hitting special attack for the hero
			if (randChoice == 0 || randChoice == 1)
			{
				playerHp = playerHp - heroSpecialAtk;

				cout << "The " << heroName << " hits you for " << heroSpecialAtk << " damage!" << endl;
			}
			else if (randChoice == 3 || randChoice == 2)
			{
				cout << "The " << heroName << " missed it's attack!" << endl;
				cout << "================================================" << endl;
			}
		}
	}
}

void heroAttackFirst(int playerHp, int &heroHp, int playerChoice, int playerAtk, int specialAttack, string name)
{
	int attackStrength;

	if (playerChoice == 1 || playerChoice == 2)
	{
		if (playerChoice == 1)
		{
			attackStrength = playerAtk;
		}
		else if (playerChoice == 2)
		{
			attackStrength = specialAttack;
		}

		if (playerHp > 0)
		{
			cout << "==========================================" << endl;
			cout << "You hit the " << name << " for " << attackStrength << " damage!" << endl;
			cout << "==========================================" << endl;

			heroHp = heroHp - attackStrength;
		}
	}
}

void levelUp(string &playerRace, string &playerName, int &healthPoints, int &attackPower, int &specialAttack, int &playerLevel, int &playerXP)
{
	if (playerXP == 80)
	{
		cout << "You have reached level 5!" << endl;
		cout << "===================================================" << endl;
		cout << " You decided to raid the kingdom with those who  " << endl;
		cout << " followed you. After you raided the kingdom and  " << endl;
		cout << " took hold of the castle, you became the new     " << endl;
		cout << " ruler of the kingdom. THE END!                           " << endl;
		cout << "===================================================" << endl;
		cout << endl;
		cout << "Long Live " << playerName << ", The " << playerRace << " King!" << endl;
		cout << endl;
		remove("PlayerData.txt");
		exit(0);
	}

	else if (playerXP == 60)
	{
		cout << "You have reached level 4!" << endl;
		system("pause");
		system("CLS");
		cout << "======================================================" << endl;
		cout << " After defeating everyone that came to defeat you, " << endl;
		cout << " the monsters and evil beings living all around the " << endl;
		cout << " kingdom began to flock to you wanting to follow    " << endl;
		cout << " you after hearing of your achievement against the " << endl;
		cout << " the heroes you defeated.                          " << endl;
		cout << "======================================================" << endl;

		maxHealth = maxHealth + 10;
		healthPoints = maxHealth;
		attackPower = attackPower + 2;
		specialAttack = specialAttack + 4;
		playerLevel = 4;
	}

	else if (playerXP == 40)
	{
		cout << "You have reached level 3!" << endl;
		system("pause");
		system("CLS");
		cout << "=================================================== " << endl;
		cout << " The king set out a reward to any one who can" << endl;
		cout << " defeat the " << playerRace << " that reside in the " << endl;
		cout << " forest at outskirt of the kingdom. Many heroes and" << endl;
		cout << " others begin gear up to be ready enter the forest" << endl;
		cout << " to defeat the " << playerRace << "." << endl;
		cout << "====================================================" << endl;

		maxHealth = maxHealth + 10;
		healthPoints = maxHealth;
		attackPower = attackPower + 2;
		specialAttack = specialAttack + 4;
		playerLevel = 3;
	}

	else if (playerXP == 20)
	{
		cout << "You have reached level 2!" << endl;
		system("pause");
		system("CLS");

		cout << "===================================================" << endl;
		cout << " The people of the towns and villages that lives  " << endl;
		cout << " at the outskirts of the kingdom begin to whisper " << endl;
		cout << " and talking to others about something defeating  " << endl;
		cout << " heroes in the forest nearby.                     " << endl;
		cout << "===================================================" << endl;

		maxHealth = maxHealth + 10;
		healthPoints = maxHealth;
		attackPower = attackPower + 2;
		specialAttack = specialAttack + 4;
		playerLevel = 2;
	}
}

bool gameExists()
{
	ifstream saveFile("playerData.txt");

	return static_cast<bool>(saveFile);
}

bool runAway(int menuChoice)
{
	bool isMenuTrue;

	if (menuChoice == 3)
	{
		isMenuTrue = true;
	}

	else
	{
		isMenuTrue = false;
	}

	return isMenuTrue;
}

void runAwayMessage()
{
	system("CLS");

	cout << "You've ran away... Well done. The townsfolk will definitely NOT" << endl
		 << "see you as a giant scaredy-cat." << endl;

	cout << "=================================================" << endl;
	cout << "You earned no XP, but you did earn some shame." << endl;
	cout << "...Aaaaand, you lost a bit of dignity." << endl;
}