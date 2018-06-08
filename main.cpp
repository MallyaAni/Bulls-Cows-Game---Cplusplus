/* This is the console executable that makes use of the BullCow class
Acts as a view in the MVC pattern and is responsible for all
use interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
void GetHiddenword();
void PlayGame();
void PlayGameSummary();
Ftext GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

//main entry point
int main()
{
	bool playagain;
	do
	{
		PrintIntro();
		PlayGame();
		playagain = AskToPlayAgain();
	} while (playagain);
	return 0; //exit application
}

void PrintIntro()
{
	//Introduce game
	
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "What hidden letter size do you want to guess?" << std::endl;
	GetHiddenword();
	std::cout << "Can you guess the " << BCGame.Hiddenwordlength();
	std::cout << " letter isogram i'm thinking of?" << std::endl;
	return;
}

void GetHiddenword()
{
	int32 hiddenlen;
	std::cin >> hiddenlen;
	BCGame.Choosehiddenword(hiddenlen); //Choose hidden word given the length
	return;
}

void PlayGame()
{	
	int32 MaxTries = BCGame.GetMaxTries();
	BCGame.Reset();

	//loop over all tries to get the guess and print it while game isnt won
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		//Repeat back the guess
		Ftext Guess = GetValidGuess();

		//submit valid guess to game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		//print number of bulls and cows
		std::cout << "	\nBulls =" << BullCowCount.Bulls << " ";
		std::cout << "Cows =" << BullCowCount.Cows << std::endl;
	}
	//Summarize game
	PlayGameSummary();
	return;
}

void PlayGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "\nGreat job, you win! :)" << std::endl;
	}
	else
	{
		std::cout << "\n:( Well, better luck next time!" << std::endl;
	}
}

Ftext GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_status;
	do{
		int32 trynumber = BCGame.GetCurrentTry();
		//Obtain user inputs <= Guesses
		
		std::cout << "\nTry " << trynumber << " of " << BCGame.GetMaxTries() << ". Enter your guess: "<< std::endl;
		Ftext user_input = "";
		std::cin >> user_input;

		Status = BCGame.CheckGuessValidity(user_input);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
		{
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		}
		case EGuessStatus::Invalid_length:
		{
			std::cout << "Please enter a " << BCGame.Hiddenwordlength() << "letter word\n\n";
			break;
		}
		case EGuessStatus::Not_lowercase:
		{
			std::cout << "Please enter lower case letters\n\n";
			break;
		}
		default:
			return user_input;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
}

bool AskToPlayAgain()
{
	//Ask user if he wants to play the game again
	Ftext playagain ="";
	std::cout << "\nDo you want to play again? (y/n)" << std::endl;
	std::cin >> playagain;
	return (playagain[0] == 'y') || (playagain[0] == 'Y');
}