#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Invalid_status,
	Not_Isogram,
	Invalid_length,
	Not_lowercase
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:

	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 Hiddenwordlength() const;
	FString Choosehiddenword(int32);
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	EResetStatus  Reset();
	FBullCowCount SubmitGuess(FString);

private:

	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyhiddenWord;
	bool IsTheGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};