#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const
{return MyCurrentTry;}

int32 FBullCowGame::Hiddenwordlength() const
{
	return MyhiddenWord.length();
}

FString FBullCowGame::Choosehiddenword(int32 hiddenlen)
{
	TMap <int32, FString> Hiddenword = { { 3, "cat" },{ 4, "dogs" },{ 5, "plane" },{ 6,"soccer" },{ 7,"alright" } };
	MyhiddenWord = Hiddenword[hiddenlen];
	return MyhiddenWord;
}

bool FBullCowGame::IsGameWon() const
{return IsTheGameWon;}


int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> MaxTries = { {3,4}, {4,7},{ 5,10},{ 6,15},{7,20} };
	return MaxTries[MyhiddenWord.length()];
}

EResetStatus FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	IsTheGameWon = false;
	return EResetStatus::OK;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //If guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	
	else if (!IsLowercase(Guess)) //If guess isnt lower case
	{
		return EGuessStatus::Not_lowercase;
	}

	else if (Guess.length() != MyhiddenWord.length())
	{
		return EGuessStatus::Invalid_length;
	}
	
	else
	{
		return EGuessStatus::OK;
	}
}

//recieves a valid guess, increments try#, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment try#
	MyCurrentTry++;

	//setup return variable
	FBullCowCount BullCowCount;	

	//compare FString input to check letters against hidden word
	int32 WordLength = Hiddenwordlength();

	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j= 0; j < WordLength; j++) //compare letters against the guess
		{
			if (MyhiddenWord[i] == Guess[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		IsTheGameWon = true;
	}
	else
	{
		IsTheGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	//setup map
	TMap<char, bool> LetterSeen;
	//loop through letters
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
		//if letter is in the map no iso
		if (LetterSeen[Letter]) {
			return false; // We do not have an iso
		}
		else
		{
			//otherwise
				//add letter to map as seen
			LetterSeen[Letter] = true; //add letter to map
		}
	}return true; //for /0 cases
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	// setup map
	TMap<char, bool> Lowercase;
	//loop through letters
	for (auto Letter : Word) //for all letters of the word
	{
		if (Letter == tolower(Letter))
		{
			Lowercase[Letter] = true;
		}
		else
		{
			return false;
		}
	}return true;
}
