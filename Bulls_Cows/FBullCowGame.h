#pragma once
#include <string>
using int32 = int;

using FString = std::string;
struct FBullCowCount
{
	int32 bull = 0;
	int32 cow = 0;

};
enum class EGuessStatus {
	 Invalid_Status,
     OK,
	 Not_Isogram,
	 Wrong_Length,
	 Not_Lowercase
};
class FBullCowGame {
public:
	FBullCowGame();// constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const; //better return value required
	
	
	void Reset(); //better return value required
    //another method for counting the number of bulls and cows and increase try 
	FBullCowCount SubmitValidGuess(FString);

//try not to work on private right now
private:
	//look in the constructor for values
	int32 MyCurrentTry;
	
	FString MyHiddenWord;
	bool BGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};

